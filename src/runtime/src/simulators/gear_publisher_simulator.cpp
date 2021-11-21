// Node that simulates messages for the gear status

#include "ros/ros.h"
#include "runtime/Gear.h"
#include <random>

int main(int argc, char **argv) {
    // Initialize using command line parameters and assigning a name to the node
    ros::init(argc, argv, "gear_publisher_simulator");
    
    // Create a node handler
    ros::NodeHandle gear_publisher_simulator_node;

    // create a ros::Publisher object using the node handler
    // In the constructor we specify the topic where to publish the messages and the maximum size of the queue
    ros::Publisher gear_pub = gear_publisher_simulator_node.advertise<runtime::Gear>("gear_status_simulated", 100);

    // set the frequency
    ros::Rate loop_rate(1);

    int count = 0;
    uint8_t current_state = 0;
    /* 
        repeat until: 
            1. SIGINT is recieved (Ctrl-C)
            2. this node is kicked out of the network because another node with the same name has been launched
            3. ros::shutdown() has been called somewhere
            4. all ros::NodeHandle have been destroyed
    */
    while(ros::ok()) {
        // Create a ServiceBrake_Status object
        runtime::Gear msg;

        // Data structure to keep the possible states
        uint8_t states[5] = {runtime::Gear::GEAR_N, runtime::Gear::GEAR_1, runtime::Gear::GEAR_2, runtime::Gear::GEAR_3, runtime::Gear::GEAR_4};
        
        // Shift gear after 3 loops
        if(count < 3) {
            ++count;
        }
        else {
            current_state = states[current_state+1];
            count = 0;
        }

        // Set values of the message
        msg.gear = current_state;

        // is a macro for printf
        ROS_INFO("%hhu", msg.gear);

        // Publish the message
        gear_pub.publish(msg);
        
        // Call ros::spinOnce() in order to allow the node to also check for any received message from
        // the topics the node is subscribed to
        ros::spinOnce();
        
        // Sleep to respect the frequency rate
        loop_rate.sleep();
    }

    return 0;
}
