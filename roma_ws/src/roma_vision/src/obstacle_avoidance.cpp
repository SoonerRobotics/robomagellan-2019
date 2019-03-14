#include <ros/ros.h>
#include "std_msgs/String.h"
#include "sensor_msgs/LaserScan.h"
#include "roma_vision/obstacles.h"

ros::Publisher obstacle_pub;
//CONSTANTS
#define MAX_DISTANCE 8 //Max distance of 8 meters

struct Obstacle{
    float angle;
    float distance;
};


void onLidarCallback(const sensor_msgs::LaserScan::ConstPtr& msg) {
    //TODO: On LIDAR read, do things and then send obstacles on obstacle topic
    //Instantiate message to publish to
    roma_vision::obstacles ob_msg;


    //TODO: This literally just creates an obstacle for every distance < MAX_DISTANCE. Create better algorithm.
    std::vector<Obstacle> obs;
    std::vector<float> ranges = msg->ranges;
    for (int i=0; i<ranges.size(); i++) {
        if (ranges.at(i) > 0) {
            Obstacle ob;
            ob.angle = i;
            ob.distance = ranges.at(i);
            obs.push_back(ob);
        }
    }

    for (int i=0; i<obs.size(); i++) {
        ob_msg.angles.push_back(obs.at(i).angle);
        ob_msg.distances.push_back(obs.at(i).angle);
    }

    //Publish data to the message
    obstacle_pub.publish(ob_msg);
}

int main(int argc, char** argv) {
    //Initialize the node
    ros::init(argc, argv, "obstacle_avoidance");
    //Set up node
    ros::NodeHandle obstacle_node;
    //Create the publisher for the obstacle message
    obstacle_pub = obstacle_node.advertise<roma_vision::obstacles>("roma_vision/obstacles", 10);
    //Create the subscriber to the Lidar (topic is /scan)
    ros::Subscriber lidar = obstacle_node.subscribe(obstacle_node.resolveName("/scan"), 10, onLidarCallback);
    //Automatically handles callbacks
    ros::spin();
}