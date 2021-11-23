#include <ros/ros.h>
#include <rosbag/bag.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/String.h>
#include <runtime/Custom_Message.h>


class Listener {
    public:
        std_msgs::UInt8 current_status;
        void callback(const runtime::Custom_Message& msg);
};


void Listener::callback(const runtime::Custom_Message& msg) {
    this->current_status = msg.number;
}


int main(int argc, char **argv) {
    Listener listener;

    rosbag::Bag bag;
    bag.open("test.bag", rosbag::bagmode::Write);

    ros::init(argc, argv, "test_bag");
    ros::NodeHandle nh;

    // Subscribe transition topics
    ros::Subscriber sub = nh.subscribe("custom_message_status_simulated", 1, &Listener::callback, &listener);

    bag.write("ebs_log", ros::Time::now(), listener.current_status);

    ros::spin();

    bag.close();

    return 0;
}