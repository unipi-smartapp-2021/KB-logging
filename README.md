# Knowledge Base Runtime

Remember to git clone with the submodule
```
git clone --recurse-submodules -j8 https://github.com/unipi-smartapp-2021/KB-runtime.git
```

### Dependencies
ROS required tools: 
```sudo apt install python3-rosdep python3-rosinstall python3-rosinstall-generator python3-wstool build-essential```

also run:
```sudo rosdep init; rosdep update```

MongoDB dependencies
```
sudo apt-get install python3-pymongo mongodb mongodb-dev
sudo pip install pymongo
```

### MongoDB setup
Scripts contained in ```/src/mongobd_store/mongodb_store``` use ```#!/usr/bin/env python``` you probably want to change that to ```#!/usr/bin/env python3```

Run ```./mongodb_setup.sh``` in order to correctly setup your environment for mongodb.

### Useful commands
Run the mongodb_server
```
rosparam set mongodb_port 62345
rosparam set mongodb_host bob # note that if using multiple machines, 'localhost' is no good
rosrun mongodb_store mongodb_server.py
```

Rosbag commands
```
rostopic list -v

rosbag record <topics>
rosbag record -a

./ros_readbagfile.py <file.bag> <topics>
```

### ToDo
- record images
- record videso 1fps
- send all data to the fan service group
- each topic need to be logged? persisted? what is its frequency?
- retrieve based on the frequency hierarchy 
- tool for video from sensing
