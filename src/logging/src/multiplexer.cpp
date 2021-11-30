// Node used to publish on the rated topics at a certain rate.
// All parameters 

#include <std_msgs/String.h>

#include "config.hpp"
#include "rated_topic.hpp"

auto main(int argc, char* argv[]) -> int {
  if(argc != 4) {
    ROS_FATAL("Usage: %s node_name topic_name rate", argv[0]);
    return -1;
  }
  
  ros::init(argc, argv, argv[1]);

  unsigned rate = std::stoul(argv[3]);
  auto multiplexer = sa::kb::RatedTopic<std_msgs::String>(argv[2], std::vector<unsigned>({rate}));
  multiplexer.Run();

  return EXIT_SUCCESS;
}