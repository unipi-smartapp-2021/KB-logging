#include <ros/ros.h>
#include <rosbag/bag.h>
#include <sensor_msgs/Imu.h>


rosbag::Bag imu_bag;


void callback(const sensor_msgs::Imu& msg) {
    imu_bag.write("simulator_lidar", ros::Time::now(), msg);
}


int main(int argc, char **argv) {
    imu_bag.open("logs/imu_log.bag", rosbag::bagmode::Write);

    ros::init(argc, argv, "lidar_logger");
    ros::NodeHandle nh;

    // Subscribe transition topics
    ros::Subscriber sub = nh.subscribe("/carla/ego_vehicle/imu", 1, &callback);

    ros::spin();

    imu_bag.close();

    return 0;
}