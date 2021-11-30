#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <std_msgs/Int32.h>
#include <runtime/Custom_Message.h>

int main(int argc, char **argv) {
    rosbag::Bag bag;
    bag.open("/mnt/c/Users/DWarez/Documents/UNIPI/Second Year/Smart Applications/ROS Repository/KB-runtime/logs/test.bag");

    for (rosbag::MessageInstance const m : rosbag::View(bag)) {
        runtime::Custom_Message::ConstPtr i = m.instantiate<runtime::Custom_Message>();
        if (i != nullptr)
            std::cout << i->version << " " << i->number << std::endl;
    }

    bag.close();
}
