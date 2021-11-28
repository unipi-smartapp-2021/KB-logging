#include <ros/ros.h>
#include <rosbag/bag.h>
#include <std_msgs/Float32.h>


rosbag::Bag speed_bag;


void callback(const std_msgs::Float32& msg) {
    speed_bag.write("simulator_lidar", ros::Time::now(), msg);
}


int main(int argc, char **argv) {
    speed_bag.open("logs/speedometer_log.bag", rosbag::bagmode::Write);

    ros::init(argc, argv, "lidar_logger");
    ros::NodeHandle nh;

    // Subscribe transition topics
    ros::Subscriber sub = nh.subscribe("/carla/ego_vehicle/speedometer", 1, &callback);

    ros::spin();

    speed_bag.close();

    return 0;
}