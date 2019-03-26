#include <ros/ros.h>

#include <eigen3/Eigen/Dense.h>


int main(int argc, char** argv)
{
	//Initialize node
	ros::init(argc, argv, "kalman_filter");

	//Make the node handle
	ros::NodeHandle kalman_filter_node;

	//Read sensor data from these topics


	//Publish current state data to this topic
	ros::Publisher state_pub = kalman_filter_node.advertise<roma_msgs::kalman_state>(kalman_filter_node.resolveName("/roma_kalman/state"), )
}