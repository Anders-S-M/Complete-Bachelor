# Complete-Bachelor
The bachelor package contains the nodes webcam_pub, camera_node, system_node.

The dynamixel code package contains the node control_node.

The dynamixel_sdk contains code for the low-level control of the motor. bachelor_interfaces contains the custom interfaces for the service \set_device and \cond_set_device.

To run this code make a repository to be your ROS2 workspace, i can be named whatever e.g. "ROS2_WS". Then make a repository in this called "src". Pull this code into "src" and build with colcon build.
This code is for ROS2 foxy and depends on OpenCV2.

Please note that the system_node needs to be restarted after an action call.

For Arduino code see the "Arduino" branch...
