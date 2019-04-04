#include <ros/ros.h>

int main(int argc, char** argv) 
{
    //Initialize the node
    ros::init(argc, argv, "romain");
    //Set up the node handle
    ros::NodeHandle romain;
    //TODO: Create a publisher for motion serial
    //romain_pub = romain.advertise()
    //Subscribe to each of the topics
    ros::Subscriber obstacle_sub = romain.subscribe(romain.resolveName("/roma_vision/obstacles"), 10, &obstacleCallback);
    ros::Subscriber kalman_sub = romain.subscribe(romain.resolveName("/roma_kalman/sensor_data"), 10, &kalmanCallback);
    ros::Subscriber trajectory_sub = romain.subscribe(romain.resolveName("/roma_trajectory/trajectory"), 10, &trajectoryCallback);
    //Given state inputs from each callback, control motion
    while(ros::ok())
    {
        //Perform all callbacks
        ros::spinOnce();
    }
}