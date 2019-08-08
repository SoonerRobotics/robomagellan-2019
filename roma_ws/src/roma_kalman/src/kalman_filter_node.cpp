#include <ros/ros.h>

#include "roma_msgs/sensor_data.h"
#include "roma_msgs/kalman_state.h"
#include "roma_kalman/EKF.h"

//Extended Kalman Filter class
EKF kalman_filter;

//Sensor data input
std::vector<double> measurements(6);	//Make a vector of the 6 relevant state measurements

//State data from the kalman filter
roma_msgs::kalman_state filtered_state;

//ROS publisher
ros::Publisher state_pub;


void update_filter(const roma_msgs::sensor_data::ConstPtr& sensor_data)
{
	//Collect the measurement data
	measurements[0] = sensor_data->gps_lat;
	measurements[1] = sensor_data->gps_lon;
	measurements[2] = sensor_data->vel;
	measurements[3] = sensor_data->accel_x;
	measurements[4] = sensor_data->heading;
	measurements[5] = sensor_data->steer_ang;

	//Run the filter on the measurements
	kalman_filter.run_filter(measurements);

	//Get the current filter state
	filtered_state = kalman_filter.get_state_msg();

	//Publish the new state estimate
	state_pub.publish(filtered_state);
}


int main(int argc, char** argv)
{
	//Initialize node
	ros::init(argc, argv, "kalman_filter");

	//Make the node handle
	ros::NodeHandle EKF_node;

	//Initialize the kalman filter
	//TODO: do this dynamically using params
	//kalman_filter.init(xo, Po);

	//Read sensor data from the data processor
	ros::Subscriber sensor_sub = EKF_node.subscribe(EKF_node.resolveName("/roma_kalman/sensor_data"), 10, update_filter);

	//Publish current state data to this topic
	state_pub = EKF_node.advertise<roma_msgs::kalman_state>(EKF_node.resolveName("/roma_kalman/state"), 10);

	//Pump callbacks
	ros::spin();
}