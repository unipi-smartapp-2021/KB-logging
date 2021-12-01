import rospy
import rostopic
import rosbag
import roslib.message
from backbone.rated_topic import RatedTopic
import argparse


class Logger():
    def __init__(self) -> None:
        super().__init__()
        self.bags = {}
        # self.bag = rosbag.Bag("logs/log.bag", 'w')


def build_parser():
    parser = argparse.ArgumentParser(description='Rated logger for simulator\'s data.')
    parser.add_argument('--topics', metavar='N', type=str, nargs='+', help='List of topics to log')
    parser.add_argument('--rates', type=int, nargs='+', help='Rate to use for each topic')
    return parser.parse_args()

logger = Logger()

def main():
    rospy.init_node("simulator_logger")
    args = build_parser() 

    assert len(args.topics) == len(args.rates)

    topic_rates = zip(args.topics, args.rates)
    
    for topic, rate in topic_rates:
        message_type = rostopic.get_topic_type(topic, blocking=True)[0]
        message_class = roslib.message.get_message_class(message_type= message_type)
        rates = []
        rates.append(rate)
        RatedTopic(topic, message_class, rates)
        logger.bags[topic] = rosbag.Bag(f"logs/{topic}_log.bag", 'w')
        rospy.Subscriber(f"{topic}Rated{rate}Hz", message_class, callback= lambda x: logger.bags[topic].write(topic, x))
        rates.clear()
    print("Allocated all the subscribers")


if __name__=="__main__":
    main()
    rospy.spin()
    for topic, bag in logger.bags.items():
        bag.close()