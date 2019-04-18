#ifndef EXT_KALMAN_FILTER_H
#define EXT_KALMAN_FILTER_H

//Include ROS
#include <ros/ros.h>

//Include libraries
#include <math.h>
#include <eigen3/Eigen/Dense>

//Include messages
#include <roma_msgs/kalman_state.h>

//Define constants
#define NUM_STATES 					 6		//number of states
#define WHEELBASE_LENGTH 	(double)(0.333)	//wheelbase length (m)
#define TOP_SPEED 			(double)(11.1)	//top speed (m/s)

class EKF
{
	public:
		//Construct the kalman filter
		EKF();
		EKF(Eigen::VectorXd xo, Eigen::MatrixXd Po);

		//Initialize the kalman filter
		void init(Eigen::VectorXd xo, Eigen::MatrixXd Po);

		//Run the kalman filter
		void run_filter(std::vector<double> sensor_data);

		//Get the state after running the filter
		Eigen::VectorXd get_state_vector();
		roma_msgs::kalman_state get_state_msg();

	private:
		//Motion and Measurement models
		void motion_model(double deltaT);
		Eigen::VectorXd measurement_model(std::vector<double> sensor_data);

		//State vector and msgs
		Eigen::VectorXd state_vector;
		roma_msgs::kalman_state state_msg;

		//Extended kalman filter matrices
		Eigen::MatrixXd Fk;
		Eigen::MatrixXd Gk;
		Eigen::MatrixXd Hk;
		Eigen::MatrixXd Pk;
		Eigen::MatrixXd Pk_last;
		Eigen::VectorXd vk;

		//Noise matrices (tune these)
		Eigen::MatrixXd Q, R;

		//Other Filter data
		Eigen::VectorXd last_state;
		double last_time;

};

#endif