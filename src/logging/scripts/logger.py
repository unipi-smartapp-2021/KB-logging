from os import write
from typing import List
import rospy
import rostopic
import rosbag
import roslib.message
from backbone.rated_topic import RatedTopic
import argparse
import datetime


# Class used to log data from RatedTopic
class Logger():
    def __init__(self,bag, log_topic,sub_topic, data_class) -> None:
        super().__init__()
        self.bag = bag
        self.topic = log_topic
        self.subscriber = rospy.Subscriber(sub_topic, data_class=data_class, callback=self.write_bag)

    def write_bag(self, msg):
        self.bag.write(self.topic, msg)


# Build parser for cli arguments
def build_parser():
    parser = argparse.ArgumentParser(description='Rated logger for simulator\'s data.')
    parser.add_argument('--topics', metavar='N', type=str, nargs='+', help='List of topics to log')
    parser.add_argument('--rates', type=int, nargs='+', help='Rate to use for each topic')
    return parser.parse_args()

bags = None
def main():
    global bags
    rospy.init_node("simulator_logger")
    args = build_parser() 
    
    # Topics and rates must have the same lenght
    assert len(args.topics) == len(args.rates)

    # Create a bag for each topic
    now = datetime.datetime.now()
    bags = {f"{topic}":rosbag.Bag(f"logs/{now.year}_{now.month}_{now.day}_{now.hour}_{now.minute}_{topic[1:]}.bag", 'w') for topic in args.topics}
    topic_rates = zip(args.topics, args.rates)

    for topic, rate in topic_rates:
        # Get message type for the topic
        message_type = rostopic.get_topic_type(topic, blocking=True)[0]
        message_class = roslib.message.get_message_class(message_type=message_type)
        # Rated topic requires a list of rates
        rates = []
        rates.append(rate)
        RatedTopic(topic, message_class, rates)
        # Allocate the loggers
        Logger(bags[topic],topic,f"{topic}Rated{rate}Hz", message_class)
        rates.clear()
    print("Allocated all the subscribers") 
        

if __name__=="__main__":
    main()
    rospy.spin()
    # Close the bags in order to save the content
    for topic, bag in bags.items():
            bag.close()
   
