#include <ros/ros.h>
#include <rosbag/bag.h>
#include <sensor_msgs/PointCloud2.h>


class Listener {
    public:
        sensor_msgs::PointCloud2 value;
        void callback(const sensor_msgs::PointCloud2& msg);
};


void Listener::callback(const sensor_msgs::PointCloud2& msg) {
    this->value = msg;
}


int main(int argc, char **argv) {
    Listener listener;

    rosbag::Bag bag;
    bag.open("logs/lidar_log.bag", rosbag::bagmode::Write);

    ros::init(argc, argv, "lidar_logger");
    ros::NodeHandle nh;

    // Subscribe transition topics
    ros::Subscriber sub = nh.subscribe("/carla/ego_vehicle/lidar", 1, &Listener::callback, &listener);

    bag.write("ebs_log", ros::Time::now(), listener.value);

    ros::spin();

    bag.close();

    return 0;
}