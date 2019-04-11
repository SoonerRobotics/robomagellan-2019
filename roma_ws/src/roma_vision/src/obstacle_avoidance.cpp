#include <ros/ros.h>
#include "std_msgs/String.h"
#include "sensor_msgs/LaserScan.h"
#include "roma_msgs/obstacles.h"

ros::Publisher obstacle_pub;
//CONSTANTS
#define MAX_DISTANCE 5 //Max distance of 8 meters
#define OBS_DST_DELTA 0.5

struct Obstacle{
    float angle;
    float distance;
};


void onLidarCallback(const sensor_msgs::LaserScan::ConstPtr& msg) {
    //Instantiate message to publish to
    roma_msgs::obstacles ob_msg;
    //Instantiate variables for obstacle detection
    std::vector<Obstacle> obs;
    std::vector<float> ranges = msg->ranges;
    bool obstacle_detected = false;
    Obstacle ob;
	
    /************************************************************************************************\
     * Currently this for loop goes through the vector of ranges and checks for obstacles. When an
     * obstacle is detected the closest distance of the object is updated and the angle is updated to
     * the corresponding indice of this closest distance divided by two. The angles increment upwards 
     * counterclockwise. If the object varies by more than +/- 0.5 meters, then we 
     * treat this as a new obstacle.
    \************************************************************************************************/
    for (int i=0; i < ranges.size(); i++) 
    {
        //If an object is detected and hasn't already been initialized
        if (ranges[i] > 0 && ranges[i] <= MAX_DISTANCE && !obstacle_detected) {
            obstacle_detected = true;
            ob.angle = i/2.0;
            ob.distance = ranges[i];
        }
        //If an object is detected and has been iniitalized
        else if(ranges[i] > 0 && ranges[i] <= MAX_DISTANCE && obstacle_detected)
        {
            //Check that the distance is still within +/- 0.25 meters, otherwise create a new object
            if(abs(ranges[i] - ob.distance) < OBS_DST_DELTA)
            {
                //Update distance to closest distance
                ob.distance = (ob.distance < ranges[i]) ? ob.distance : ranges[i];
                //Update angle to closest distance angle
                ob.angle = (ob.distance < ranges[i]) ? ob.angle : i/2.0;
            }
            else
            {
                //Push the previous object
                obs.push_back(ob);
                //Begin the new object
                ob.angle = i/2.0;
                ob.distance = ranges[i];
            } 
        }
        //If an object that was initialized is no longer detected 
        else if((ranges[i] == 0 || ranges[i] > MAX_DISTANCE) && obstacle_detected)
        {
            //Update boolean and push the object to the vector
            obstacle_detected = false;
            obs.push_back(ob);
        }
    }

    //Update the obstacle message with all obstacles found
    for (int i=0; i < obs.size(); i++) {
        ob_msg.angles.push_back(obs.at(i).angle);
        ob_msg.distances.push_back(obs.at(i).distance);
    }

    //Publish message data to the topic
    obstacle_pub.publish(ob_msg);
}

int main(int argc, char** argv) 
{
    //Initialize the node
    ros::init(argc, argv, "obstacle_avoidance_node");
    //Set up node
    ros::NodeHandle obstacle_node;
    //Create the publisher for the obstacle message
    obstacle_pub = obstacle_node.advertise<roma_msgs::obstacles>(obstacle_node.resolveName("/roma_vision/obstacles"), 10);
    //Create the subscriber to the Lidar (topic is /scan)
    ros::Subscriber lidar = obstacle_node.subscribe(obstacle_node.resolveName("/scan"), 10, onLidarCallback);
    //Automatically handles callbacks
    ros::spin();
}