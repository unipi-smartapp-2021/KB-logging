### Usage
Before starting, be sure to have run `catkin_make` and `source devel/setup.*` where `*` stands for the shell you are currently using.

Also, be sure to have `roscore` running.

In order to start logging, simply run:

`rosrun logging logger.py --topics [list of topics] --rates [list of rates]`

where: 

- `[list of topics]` is the list of topics you want to log. Example: `/IMU /mytopic /mytopic2`
- `[list of rates]` is the list of rates at which you want the log to happen. Example: `5 10 20`. Following the previous example of `list of topics` this would imply that `/IMU` will be sampled at 5Hz, `/mytopic` will be sampled at 10Hz, `/mytopic2` will be sampled at 20Hz.

Be sure that both lists have the same lenght, otherwise you'll get an assertion error.

When you're done with logging, simply press `Ctrl+C` in order to stop the spinning of the node and to give it the opportunity to close the bags to save the content.

You will find the bags containing the logged data in the directory `logs/`.
