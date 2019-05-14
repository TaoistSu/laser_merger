#two keli laser scan

$ roslaunch sdkeli_ls_udp sdkeli_ls1207de_udp_nodelet_with_2_lidars.launch

$ roslaunch ira_laser_tools-master laserscan_multi_merger.launch

$ rviz

change the frame to the base_link you will see the result
