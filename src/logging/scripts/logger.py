import rospy
import rostopic
import rosbag
import roslib.message
from backbone.rated_topic import RatedTopic
import argparse


class Logger():
    def __init__(self) -> None:
        super().__init__()
        self.bag = rosbag.Bag("logs/log.bag", 'w')
        self.current_topic = ""

    def callback(self, message):
        self.bag.write(self.current_topic, message)


def build_parser():
    parser = argparse.ArgumentParser(description='Rated logger for simulator\'s data.')
    parser.add_argument('--topics', metavar='N', type=list, nargs='+', help='List of topics to log')
    parser.add_argument('--rates', type=list, help='Rate to use for each topic')
    return parser.parse_args()



def main():
    rospy.init_node("simulator_logger")
    args = build_parser() 

    logger = Logger()

    assert len(args.topics) == len(args.rates)

    topic_rates = zip(args.topics, args.rates)
    subscribers = []

    for topic, rate in topic_rates:
        topic = ''.join(topic)
        logger.current_topic = topic
        message_type = rostopic.get_topic_type(topic, blocking=True)[0]
        message_class = roslib.message.get_message_class(message_type= message_type)
        rates = []
        rates.append(int(rate))
        RatedTopic(topic, message_class, rates)
        subscribers.append(rospy.Subscriber(f"{topic}Rated{rate}Hz", message_class, callback= lambda x: logger.bag.write(topic, x)))
        rates.clear()
    print("Allocated all the subscribers")


if __name__=="__main__":
    main()
    rospy.spin()