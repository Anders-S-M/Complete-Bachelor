# Complete-Bachelor
The bachelor package contains the nodes webcam_pub, camera_node, System_Node.

The dynamixel code package contains the node control_node.

The dynamixel_sdk contains code for the low-level control of the motor. bachelor_interfaces contains the custom interfaces for the service \set_device and \cond_set_device.

To run this code make a repository to be your ROS2 workspace, i can be named whatever e.g. "ROS2_WS". Then make a repository in this called "src". Pull this code into "src" and build with colcon build.
This code is for ROS2 foxy and depends on OpenCV2.

To run a node:
stand in the workspace you have made.
run: ros2 run bachelor webcam_pub
or any other node
while writing press tab twice to see names of nodes, note System_Node is capitalized.

for the control node:
ros2 run dynamixel_code control_node


Please note that the System_Node needs to be restarted after an action call.

For Arduino code see the "Arduino" branch...
