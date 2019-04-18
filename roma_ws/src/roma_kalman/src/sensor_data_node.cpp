#include <ros/ros.h>

//Include libraries
#include <eigen3/Eigen/Dense>

//Include messages
#include <roma_msgs/sensor_data.h>
#include <roma_msgs/localization_data.h>
#include <roma_msgs/motion_feedback.h>

//Track if data is valid
bool valid_data = false;

//Keep track of the sensor data
roma_msgs::sensor_data sensor_data;

//ROS publisher
ros::Publisher state_pub;


/**
 * @brief 
 * 
 * @param data 
 */
void localization_callback(const roma_msgs::sensor_data::ConstPtr& data)
{
	//Get the data from the localization board
	sensor_data.gps_lat = data->gps_lat;
	sensor_data.gps_lon = data->gps_lon;
	sensor_data.vel 	= data->vel;
	sensor_data.accel_x = data->accel_x;
	sensor_data.heading	= data->heading;

	//Note the localization sensor update
	sensor_data.localization = true;

	//Update the valid data flag when both feedbacks are sent
	if(sensor_data.motion)
	{
		valid_data = true;
	}
}


/**
 * @brief 
 * 
 * @param motion_data 
 */
void motion_callback(const roma_msgs::motion_feedback::ConstPtr& motion_data)
{
	//Get the steering angle from the motion board
	sensor_data.steer_ang = motion_data->steer_ang;

	//Note the motion feedback update
	sensor_data.motion = true;

	//Update valid data flag if the localization has happened
	if(sensor_data.localization)
	{
		valid_data = true;
	}
}


/**
 * @brief 
 * 
 * @param event 
 */
void sensor_data_callback(const ros::TimerEvent& event)
{
	//If the data is valid, publish it to the kalman filter
	if(valid_data)
	{
		state_pub.publish(sensor_data);
	}
}


/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char** argv)
{
	//Initialize node
	ros::init(argc, argv, "sensor_data_node");

	//Make the node handle
	ros::NodeHandle sensor_data_node;

	//Read sensor data from these topics
	ros::Subscriber localization_sub = sensor_data_node.subscribe(sensor_data_node.resolveName("/roma_localization/data"), 10, &localization_callback);

	//Publish current state data to this topic
	state_pub = sensor_data_node.advertise<roma_msgs::sensor_data>(sensor_data_node.resolveName("/roma_kalman/sensor_data"), 10);

	//Publish to the sensor data pub at a frequency
	ros::Timer state_timer = sensor_data_node.createTimer(ros::Duration(0.05), &sensor_data_callback);

	//Pump callbacks
	ros::spin();
}
