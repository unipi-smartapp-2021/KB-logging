#include <ros/ros.h>
#include <rosbag/bag.h>
#include <carla_msgs/CarlaEgoVehicleInfo.h>


rosbag::Bag cevi_bag;


void callback(const carla_msgs::CarlaEgoVehicleInfo& msg) {
    cevi_bag.write("simulator_lidar", ros::Time::now(), msg);
}


int main(int argc, char **argv) {
    cevi_bag.open("logs/vehicle_info_log.bag", rosbag::bagmode::Write);

    ros::init(argc, argv, "lidar_logger");
    ros::NodeHandle nh;

    // Subscribe transition topics
    ros::Subscriber sub = nh.subscribe("/carla/ego_vehicle/vehicle_info", 1, &callback);

    ros::spin();

    cevi_bag.close();

    return 0;
}