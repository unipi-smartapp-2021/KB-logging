#include <ros/ros.h>
#include <rosbag/bag.h>
#include <runtime/Custom_Message.h>


class Listener {
    public:
        runtime::Custom_Message value;
        void callback(const runtime::Custom_Message& msg);
};


void Listener::callback(const runtime::Custom_Message& msg) {
    ROS_INFO("Storing a message: %d, %d", msg.version, msg.number);
    this->value = msg;
}


int main(int argc, char **argv) {
    Listener listener;

    rosbag::Bag bag;
    bag.open("logs/test.bag", rosbag::bagmode::Write);

    ros::init(argc, argv, "test_bag");
    ros::NodeHandle nh;

    // Subscribe transition topics
    ros::Subscriber sub = nh.subscribe("custom_message", 1, &Listener::callback, &listener);

    while(ros::ok()) {
        bag.write("rosbag_test", ros::Time::now(), listener.value);

        ros::spin();
    }

    bag.close();

    return 0;
}