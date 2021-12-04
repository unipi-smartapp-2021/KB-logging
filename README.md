# Knowledge Base Logging

Git clone recursively with the submodule
```
git clone --recurse-submodules -j8 https://github.com/unipi-smartapp-2021/KB-runtime.git
git submodule update --init --recursive
```

### Dependencies
ROS required tools: 
```
sudo apt install python3-rosdep python3-rosinstall python3-rosinstall-generator python3-wstool build-essential
rosdep init
rosdep update
rosdep install --from-paths src --ignore-src -r -y
```

### Building the packages
Before starting, be sure to have run `catkin_make` and `source devel/setup.*` where `*` stands for the shell you are currently using.
```
catkin_make
source devel/setup.*
```

### Running
First, run the `roscore`. Then start the logging in another terminal (remember to source devel/setup.* again)
```
roscore
rosrun logging logger.py --topics [list of topics] --rates [list of rates]
```
- `[list of topics]` is the list of topics you want to log. Example: `/IMU /mytopic`
- `[list of rates]` is the list of rates at which you want the log. Example: `5 10`. Following the previous example of `list of topics` this would imply that `/IMU` will be sampled at 5Hz, `/mytopic` will be sampled at 10Hz.

The two lists must have the same length.

When you're done with logging, simply press `Ctrl+C` in order to stop the running of the node and the logs will be saved in the directory `logs/`.


### Example
This is an demo, remember that you have to launch each node on a different terminal:
```
rostopic pub -r 60 /IMU std_msgs/String hello               # publishes data at rate 120 on /mytopic
rostopic pub -r 120 /mytopic std_msgs/String "data: ''"     # publishes data at rate 120 on /mytopic
rosrun logging logger.py --topics /IMU /mytopic --rates 2 4
```

To view the contents of a rosbag you can use the ros_readbag.py
```
# Download the file
wget https://raw.githubusercontent.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles/master/useful_scripts/ros_readbagfile.py
chmod +x ros_readbagfile.py

# Move this executable script into `~/bin` as `ros_readbagfile`, so that it will be available as that command
mkdir -p ~/bin
mv ros_readbagfile.py ~/bin/ros_readbagfile
. ~/.bashrc

# Install python dependencies (see the comments at the top of the ros_readbagfile.py 
pip install bagpy
pip3 install bagpy
```
```
ros_readbagfile <mybagfile.bag> [topic1] [topic2] [topic3] [...] | tee topics.yaml
```


### ToDo (?)
- record images
- record videso 1fps
- send all data to the fan service group
- each topic need to be logged? persisted? what is its frequency?
- retrieve based on the frequency hierarchy 
- tool for video from sensing
