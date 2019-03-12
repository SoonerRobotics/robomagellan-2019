#include <ros/ros.h>
#include "std_msgs/String.h"
#include "roma_ws/obstacles.h"

ros::Subscriber lidar;

// TODO: Change to correct LIDAR message type
void onLidarCallback(const std_msgs::String::ConstPtr& msg) {
    //TODO: On LIDAR read, do things and then send obstacles on obstacle topic
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "obstacle_avoidance");

    ros::NodeHandle node;

    ros::Publisher obstacles = node.advertise<roma_vision::obstacles>("roma_vision/obstacles", 1000);

    lidar = node.subscribe(node.resolveName("roma_vision/lidar"), 1000, onLidarCallback);

    ros::spin();
}