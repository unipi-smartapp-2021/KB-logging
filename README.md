# KB-runtime
Remember to git clone with the submodule
```
git clone --recurse-submodules -j8
```

Install the dependencies
```
sudo apt-get install python-pymongo mongodb mongodb-dev
sudo pip install pymongo
```

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

TODO (?):
- record images
- record videso 1fps
- send all data to the fan service group
- each topic need to be logged? persisted? what is its frequency?
- retrieve based on the frequency hierarchy 
- tool for video from sensing
