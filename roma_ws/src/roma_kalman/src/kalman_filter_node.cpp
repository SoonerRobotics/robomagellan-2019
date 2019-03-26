#include <ros/ros.h>

#include "roma_msgs/sensor_data.h"
#include "roma_kalman/include/EKF.h"

//Extended Kalman Filter class
EKF kalman_filter;

void update_filter(const roma_msgs::sensor_data::ConstPtr& sensor_data)
{
	//kalman_filter.run_filter()
}


int main(int argc, char** argv)
{
	//Initialize node
	ros::init(argc, argv, "kalman_filter");

	//Make the node handle
	ros::NodeHandle EKF_node;

	//Read sensor data from the data processor
	ros::Subscriber sensor_sub = EKF_node.subscribe(EKF_node.resolveName("/roma_kalman/sensor_data"), 10, update_filter);

	//Publish current state data to this topic
	ros::Publisher state_pub = EKF_node.advertise<roma_msgs::kalman_state>(EKF_node.resolveName("/roma_kalman/state"), 10);

	//Pump callbacks
	ros::spin();
}