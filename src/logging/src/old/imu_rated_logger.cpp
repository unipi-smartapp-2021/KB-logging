#include <ros/ros.h>
#include <rosbag/bag.h>
#include <sensor_msgs/Imu.h>
#include <std_msgs/String.h>
#include <backbone/RateTopic.h>
#include <backbone/RateTopicRequest.h>
#include <backbone/RateTopicResponse.h>
#include "rated_topic.hpp"


rosbag::Bag imu_bag;


void callback(const sensor_msgs::Imu& msg) {
    imu_bag.write("simulator_lidar", ros::Time::now(), msg);
}


int main(int argc, char **argv) {
    ros::init(argc, argv, "lidar_rated_logger");
    std::string original_topic = "/mytopic";
    imu_bag.open("logs/imu_log.bag", rosbag::bagmode::Write);

    ros::NodeHandle nh;

    auto r_publisher = sa::kb::RatedPublisher<sensor_msgs::Imu>(nh.advertise<sensor_msgs::Imu>(original_topic+"Rated", 1), 10);

    // Get rated topic name
    auto client = nh.serviceClient<backbone::RateTopic>(original_topic + "Rated");
    auto service = backbone::RateTopic();
    service.request.rate = 10;
    if (!client.call(service)) {
        ROS_ERROR("FirstClient) Failed to call service");
        return EXIT_FAILURE;
    }

    ROS_INFO("FirstClient) Receiving on \"%s\"", service.response.topic.c_str());

    // Subscribe transition topics
    ros::Subscriber sub = nh.subscribe(service.response.topic, 1, &callback);

    ros::spin();

    imu_bag.close();

    return 0;
}