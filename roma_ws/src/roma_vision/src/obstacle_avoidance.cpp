#include <ros/ros.h>
#include "std_msgs/String.h"
#include "roma_ws/obstacles.h"

ros::Publisher obstacle_topic;

//TODO: What is the max distance we reasonably read at? Units?
#define MAX_DISTANCE = 8;

struct {
    float angle,
    float distance
} Obstacle

// TODO: Change to correct LIDAR message type
void onLidarCallback(const std_msgs::String::ConstPtr& msg) {
    //TODO: On LIDAR read, do things and then send obstacles on obstacle topic

    //TODO: Assumes array of 360 distances for each degree, change to what it actually be
    float[] distances;

    //TODO: This literally just creates an obstacle for every distance < MAX_DISTANCE. Create better algorithm.
    std::vector<Obtsacle> obs;
    for (int i=0; i<360; i++) {
        if (distances[i] < MAX_DISTANCE) {
            ob = Obstacle();
            ob.angle = i;
            ob.distance = distances[i]
            obs.push_back(ob)
        }
    }

    
    uint8_t numObstacles = obs.size();
    float angles[numObstacles];
    float distances[numObstacles];

    for (int i=0; i<numObstacles; i++) {
        angles[i] = obs.get(i).angle;
        distances[i] = obs.get(i).angle;
    }

    //TODO: Put data into message and send it.
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "obstacle_avoidance");

    ros::NodeHandle node;

    obstacle_topic = node.advertise<roma_vision::obstacles>("roma_vision/obstacles", 1000);

    ros::Subscriber lidar = node.subscribe(node.resolveName("roma_vision/lidar"), 1000, onLidarCallback);

    ros::spin();
}