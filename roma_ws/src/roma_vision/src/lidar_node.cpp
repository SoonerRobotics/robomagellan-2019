//ROS msgs and libs
#include <ros/ros.h>

/**
 * @brief 
 * 
 */
void lidarCallback(const ) //TODO: Find topic name

/**
 * @brief Main method
 * 
 * @param argc Number of args
 * @param argv Args into the executable
 * @return int Exit code
 */
int main(int argc, char **argv)
{
    //Start the node
    ros::init(argc, argv, "lidar_node");

    //Set up the node handle for obstacle detection
    ros::NodeHandle lidar_node;

    //Subscribe to the topic published by the lidar node
    //TODO: confirm resolveName is correct
    ros::Subscriber lidar_sub = lidar_node.subscribe(lidar_node.resolveName("/base_link_to_laser4"), 10, &lidarCallback);

    //TODO: Create lidar msg
    lidar_pub = lidar_node.advertise<roma_vision::lidar>(lidar_node.resolveName("/roma_vision/lidar"), 10);

    //Handle the callbacks
    ros::spin();
}