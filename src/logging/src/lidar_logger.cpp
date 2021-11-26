#include <ros/ros.h>
#include <rosbag/bag.h>
#include <sensor_msgs/PointCloud2.h>


rosbag::Bag lidar_bag;


void callback(const sensor_msgs::PointCloud2& msg) {
    lidar_bag.write("simulator_lidar", ros::Time::now(), msg);
}


int main(int argc, char **argv) {
    lidar_bag.open("logs/lidar_log.bag", rosbag::bagmode::Write);

    ros::init(argc, argv, "lidar_logger");
    ros::NodeHandle nh;

    // Subscribe transition topics
    ros::Subscriber sub = nh.subscribe("/carla/ego_vehicle/lidar", 1, &callback);

    ros::spin();

    lidar_bag.close();

    return 0;
}