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


#### catkin_make will fail the first time you call it, just call it again


### Useful commands
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
