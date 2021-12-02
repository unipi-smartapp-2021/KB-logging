#include <ros/ros.h>
#include <rosbag/bag.h>
#include <carla_msgs/CarlaEgoVehicleStatus.h>


rosbag::Bag cevs_bag;


void callback(const carla_msgs::CarlaEgoVehicleStatus& msg) {
    cevs_bag.write("simulator_lidar", ros::Time::now(), msg);
}


int main(int argc, char **argv) {
    cevs_bag.open("logs/vehicle_status_log.bag", rosbag::bagmode::Write);

    ros::init(argc, argv, "lidar_logger");
    ros::NodeHandle nh;

    // Subscribe transition topics
    ros::Subscriber sub = nh.subscribe("/carla/ego_vehicle/vehicle_status", 1, &callback);

    ros::spin();

    cevs_bag.close();

    return 0;
}