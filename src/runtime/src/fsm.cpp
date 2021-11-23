// Source for the implementation of the FSM of the ADS

#include "ros/ros.h"
#include "runtime/EBS_Status.h"
#include "runtime/ServiceBrake_Status.h"
#include "runtime/SteeringWheel_Status.h"
#include "runtime/Gear.h"
#include "runtime/TractiveSystem.h"
#include "runtime/R2D.h"
#include "runtime/FSM.h"


// Current values for each attribute of the FSM
uint8_t current_ts;     // tractive system
uint8_t current_r2d;    // ready 2 drive    
uint8_t current_sw;     // steering wheel actuator
uint8_t current_sb;     // service brake
uint8_t current_ebs;    // emergency brake system


// Callback for tractive system
void ts_callback(const runtime::TractiveSystem& msg) {
   current_ts = msg.state;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "state_machine");
    ros::NodeHandle nh;

    /// Subscribe transition topics
    ros::Subscriber ts_sub = nh.subscribe("ts_status_simulated", 1, &ts_callback);

    ROS_INFO("%huu", current_ts);
     
    ros::spin();

    return 0;
}