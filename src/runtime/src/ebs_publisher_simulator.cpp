#include "ros/ros.h"
#include "runtime/EBS_Status.h"
#include <random>

int main(int argc, char **argv) {
    // Initialize using command line parameters and assigning a name to the node
    ros::init(argc, argv, "ebs_publisher_simulator");
    
    // Create a node handler
    ros::NodeHandle ebs_publisher_simulator_node;

    // create a ros::Publisher object using the node handler
    // In the constructor we specify the topic where to publish the messages and the maximum size of the queue
    ros::Publisher ebs_pub = ebs_publisher_simulator_node.advertise<runtime::EBS_Status>("ebs_status_simulated", 100);

    // set the frequency
    ros::Rate loop_rate(1);

    /* 
        repeat until: 
            1. SIGINT is recieved (Ctrl-C)
            2. this node is kicked out of the network because another node with the same name has been launched
            3. ros::shutdown() has been called somewhere
            4. all ros::NodeHandle have been destroyed
    */
    while(ros::ok()) {
        // Create a EBS_Status object
        runtime::EBS_Status msg;
        std::stringstream ss;

        // Data structure to keep the possible states
        uint8_t states[4] = {runtime::EBS_Status::UNKNOWN, runtime::EBS_Status::UNAVAILABLE, runtime::EBS_Status::ARMED, runtime::EBS_Status::ACTIVATED};

        // Extract a random number to get a random EBS State
        int ns = rand() % 5;

        // Set values of the message
        msg.state = states[ns];

        // is a macro for printf
        ROS_INFO("%hhu", msg.state);

        // Publish the message
        ebs_pub.publish(msg);
        
        // Call ros::spinOnce() in order to allow the node to also check for any received message from
        // the topics the node is subscribed to
        ros::spinOnce();
        
        // Sleep to respect the frequency rate
        loop_rate.sleep();
    }

    return 0;
}
