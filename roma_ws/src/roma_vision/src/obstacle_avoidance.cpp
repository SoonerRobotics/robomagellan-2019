#include <ros/ros.h>
#include "std_msgs/String.h"
#include "roma_vision/obstacles.h"

ros::Publisher obstacle_topic;
//CONSTANTS
#define MAX_DISTANCE = 8; //Max distance of 8 meters

struct {
    float angle,
    float distance
} Obstacle


void onLidarCallback(const sensor_msgs::LaserScan::ConstPtr& msg) {
    //TODO: On LIDAR read, do things and then send obstacles on obstacle topic
    //Instantiate message to publish to
    roma_vision::obstacle ob_msg;

    //TODO: This literally just creates an obstacle for every distance < MAX_DISTANCE. Create better algorithm.
    std::vector<Obstacle> obs;
    for (int i=0; i<360; i++) {
        if (msg->ranges[i] < MAX_DISTANCE) {
            ob = Obstacle();
            ob.angle = i;
            ob.distance = msg->ranges[i]
            obs.push_back(ob)
        }
    }

    
    ob_msg.num_obstacles = obs.size();
    

    for (int i=0; i<numObstacles; i++) {
        ob_msg.angles[i] = obs.get(i).angle;
        ob_msg.distances[i] = obs.get(i).angle;
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
    obstacle_pub = node.advertise<roma_vision::obstacles>("roma_vision/obstacles", 10);
    //Create the subscriber to the Lidar (topic is /scan)
    ros::Subscriber lidar = node.subscribe(node.resolveName("/scan"), 10, onLidarCallback);
    //Automatically handles callbacks
    ros::spin();
}