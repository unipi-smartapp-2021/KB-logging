#include "ros/ros.h"
#include "runtime/Custom_Message.h"
#include <sstream>

int main(int argc, char **argv) {
    ros::init(argc, argv, "assi_publisher");
    
    ros::NodeHandle custom_message_node;

    ros::Publisher cm_pub = custom_message_node.advertise<runtime::Custom_Message>("custom_message", 100);

    ros::Rate loop_rate(10);

    int count = 0;

    while(ros::ok()) {
        runtime::Custom_Message msg;
        std::stringstream ss;
        msg.number = 42;
        msg.check = true;
        ss << msg.number + " " + msg.check;
        ROS_INFO("%d, %d", msg.number, msg.check);
        cm_pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}