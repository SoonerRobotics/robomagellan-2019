#include <ros/ros.h>

#include <eigen3/Eigen/Dense.h>




int main(int argc, char** argv)
{
	//Initialize node
	ros::init(argc, argv, "sensor_data_node");

	//Make the node handle
	ros::NodeHandle sensor_data_node;

	//Read sensor data from these topics


	//Publish current state data to this topic
	ros::Publisher state_pub = kalman_filter_node.advertise<roma_msgs::sensor_data>(sensor_data_node.resolveName("/roma_kalman/sensor_data"), )
}