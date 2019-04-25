#include <ros/ros.h>
#include "roma_msgs/motion_cmds.h"
#include "roma_msgs/kalman_state.h"

#include <queue>
#include <cmath>
#include <algorithm>

struct Coordinate {
    double lat;
    double lon;
};

std::queue<Coordinate> coordQueue;
ros::Publisher motion_pub;
roma_msgs::motion_cmds motion_cmd;

//shamelessly stolen from https://gis.stackexchange.com/questions/252672/calculate-bearing-between-two-decimal-gps-coordinates-arduino-c
float degrees2radians = 3.14159/180.0;
float bearing(float lat,float lon,float lat2,float lon2){

    float teta1 = lat * degrees2radians;
    float teta2 = lat2 * degrees2radians;
    float delta1 = (lat2-lat) * degrees2radians;
    float delta2 = (lon2-lon) * degrees2radians;

    //==================Heading Formula Calculation================//

    float y = sin(delta2) * cos(teta2);
    float x = cos(teta1)*sin(teta2) - sin(teta1)*cos(teta2)*cos(delta2);
    float brng = atan2(y,x);
    brng = brng / degrees2radians;// radians to degrees
    brng = ( ((int)brng + 360) % 360 ); 

    return brng;


  }

void ekfCallback(const roma_msgs::kalman_state::ConstPtr& filtered_state)
{
    Coordinate curCoord = coordQueue.front();
    motion_cmd.power = 0.3;
    motion_cmd.steer_ang = bearing(filtered_state->latitude, filtered_state->longitude, curCoord.lat, curCoord.lon) -  filtered_state->heading;
    
    motion_cmd.steer_ang = motion_cmd.steer_ang > 180.0 ? motion_cmd.steer_ang - 360.0 : motion_cmd.steer_ang;

    motion_pub.publish(motion_cmd);
}


int main(int argc, char** argv) 
{
    //Initialize the node
    ros::init(argc, argv, "trajectory_node");
    
	//Set up node
    ros::NodeHandle trajectory_node;
    
	//Create the publisher for the obstacle message
    motion_pub = trajectory_node.advertise<roma_msgs::motion_cmds>(trajectory_node.resolveName("/roma_motion/cmd"), 10);
    
	//Create the subscribers
    ros::Subscriber ekf_sub = trajectory_node.subscribe(trajectory_node.resolveName("/roma_kalman/state"), 10, &ekfCallback);

    //Read coords and put into queue, hardcoded values for now.
    Coordinate ex1;
    ex1.lat = 60;
    ex1.lon = 80;

    coordQueue.push(ex1);
    
	//Automatically handle callbacks
    ros::spin();
}