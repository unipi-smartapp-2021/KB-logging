// Node that simulates messages for the Tractive System status

#include "ros/ros.h"
#include "runtime/R2D.h"

int main(int argc, char **argv) {
    // Initialize using command line parameters and assigning a name to the node
    ros::init(argc, argv, "r2d_publisher_simulator");
    
    // Create a node handler
    ros::NodeHandle r2d_publisher_simulator_node;

    // create a ros::Publisher object using the node handler
    // In the constructor we specify the topic where to publish the messages and the maximum size of the queue
    ros::Publisher r2d_pub = r2d_publisher_simulator_node.advertise<runtime::R2D>("r2d_status_simulated", 100);

    // set the frequency
    ros::Rate loop_rate(1);

    /* 
        repeat until: 
            1. SIGINT is recieved (Ctrl-C)
            2. this node is kicked out of the network because another node with the same name has been launched
            3. ros::shutdown() has been called somewhere
            4. all ros::NodeHandle have been destroyed
    */
    int count = 0;

    while(ros::ok()) {
        // Create a R2D object
        runtime::R2D msg;

        // Data structure to keep the possible states
        uint8_t states[2] = {runtime::R2D::OFF, runtime::R2D::ON};

        // Set values of the message
        if (count < 4) {
            msg.state = states[0];
            ++count;
        } else {
            msg.state = states[1];
        }
        
        // is a macro for printf
        ROS_INFO("%hhu", msg.state);

        // Publish the message
        r2d_pub.publish(msg);
        
        // Call ros::spinOnce() in order to allow the node to also check for any received message from
        // the topics the node is subscribed to
        ros::spinOnce();
        
        // Sleep to respect the frequency rate
        loop_rate.sleep();
    }

    return 0;
}
