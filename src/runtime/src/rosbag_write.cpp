#include <ros/ros.h>
#include <rosbag/bag.h>
#include <runtime/Custom_Message.h>

rosbag::Bag bag;


void callback(const runtime::Custom_Message& msg) {
    ROS_INFO("Storing a message: %d, %d", msg.version, msg.number);
    bag.write("rosbag_test", ros::Time::now(), msg);
}

int main(int argc, char **argv) {

    bag.open("logs/test.bag", rosbag::bagmode::Write);

    ros::init(argc, argv, "test_bag");
    ros::NodeHandle nh;

    // Subscribe transition topics
    ros::Subscriber sub = nh.subscribe("custom_message", 1, callback);

    ros::spin();

    bag.close();

    return 0;
}