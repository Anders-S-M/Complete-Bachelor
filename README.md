# Complete-Bachelor
The "bach" code takes the temperature data and sends it via serial and lora every 5 seconds.

The "bach_receiver" receives this and sends it via serial.

The "TTNsenderGit" takes the temperature and sends this to TTN, insert your own appEUI and appKEY values.

The "Test" code send dummy information to TTN so you can test the communication without having to get real temperature data, insert your own appEUI and appKEY values.

This code is for the MKR WAN 1310 and needs the libraries lora, onewire and MKRWAN along with the board files for the specific board.

See main branch for ROS2 code...
