#include "ros/ros.h"
#include "runtime/Custom_Message.h"

int main(int argc, char **argv) {

    // Initialize using command line parameters and assigning a name to the node
    ros::init(argc, argv, "custom_message_publisher");
    
    // Create a node handler
    ros::NodeHandle custom_message_node;

    // create a ros::Publisher object using the node handler
    // In the constructor we specify the topic where to publish the messages and the maximum size of the queue
    ros::Publisher cm_pub = custom_message_node.advertise<runtime::Custom_Message>("custom_message", 100);

    // set the frequency
    ros::Rate loop_rate(10);

    /* 
        repeat until: 
            1. SIGINT is recieved (Ctrl-C)
            2. this node is kicked out of the network because another node with the same name has been launched
            3. ros::shutdown() has been called somewhere
            4. all ros::NodeHandle have been destroyed
    */
    uint16_t version = 0;
    while(ros::ok()) {
        // Create a Custom_Message object
        runtime::Custom_Message msg;

        // Set values of the message
        msg.number = 4;
        msg.version = version;
        version++;

        // is a macro for printf
        ROS_INFO("%d, %d", msg.version, msg.number);

        // Publish the message
        cm_pub.publish(msg);
        
        // Call ros::spinOnce() in order to allow the node to also check for any received message from
        // the topics the node is subscribed to
        ros::spinOnce();
        
        // Sleep to respect the frequency rate
        loop_rate.sleep();
    }

    return 0;
}