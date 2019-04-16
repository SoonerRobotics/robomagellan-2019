#include "roma_kalman/include/EKF.h"


EKF::EKF(Eigen::VectorXd xo, Eigen::MatrixXd Po)
{
	/**Initialize the Jacobians! **/
	//Fk = Jacobian for motion model
	this->Fk = Eigen::Identity(NUM_STATES, NUM_STATES);

	//Hk = Jacobian of the measurement function
	this->Hk = Eigen::Identity(NUM_STATES, NUM_STATES);

	/** Set the filter initial conditions **/
	this->state_vector = Eigen::Zero(NUM_STATES);
	this->last_state = init_state;
	this->Pk = Eigen::Identity(NUM_STATES, NUM_STATES) * 0.1;
	this->Pk_last = Po;

	/** Timing variables **/
	this->last_time = ros::Time::now().toSec();//TODO: use finer grain time unit

	/** Set up the noise matrices **/
	this->R = Eigen::Identity(NUM_STATES, NUM_STATES) * 0.5;
	this->Q = Eigen::Identity(NUM_STATES, NUM_STATES) * 0.6;

	//Output that the kalman filter is initialized
	printf("EKF initialized\n");
}


void EKF::run_filter(vector<double> sensor_data)
{
	//Declare local variables
	long current_time;
	double deltaT;

	//Get timing
	current_time = ros::Time::now().toSec();//TODO: use finer grain time unit
	//TODO: convert time to seconds to get decimal values
	deltaT = current_time - this->last_time;

	/**Predict the state of the robot based on the motion model (physics) **/
	//Calculate the updated state prediction
	motion_model(deltaT);

	//Calculate the uncertainty matrix based on the last state's jacobian of f(xk, uk)
	this->Pk = this->Fk * this->Pk_last * this->Fk.transpose() + this->Q;

	/** Update the state with actual measurements **/
	//Compute the gain
	this->Gk = this->Pk * this->Hk.transpose() * (this->Hk * this->Pk * this->Hk.transpose() + this->R).inverse();

	//Get new information from measurements (innovation: vk)
	this->vk = measurement_model(sensor_data);

	//Update the estimate vector and uncertainty matrix based on innovation and gain
	this->state_vector = this->state_vector + this->Gk * (this->vk);
	this->Pk = (Eigen::Identity(NUM_STATES, NUM_STATES) - (this->Gk * this->Hk)) * this->Pk;

	//Update timing
	this->last_time = current_time;

	//Update the last variable trackers for the next Calculate
	this->last_state = this->state_vector;
	this->Pk_last = this->Pk;
}


Eigen::VectorXd EKF::get_state_vector()
{
	return this->state_vector;
}


roma_msgs::kalman_state EKF::get_state_msg()
{
	this->state_msg.gps_lat 	= this->state_vector(0);
	this->state_msg.gps_lon 	= this->state_vector(1);
	this->state_msg.velocity 	= this->state_vector(2);
	this->state_msg.accel 		= this->state_vector(3);
	this->state_msg.heading		= this->state_vector(4);
	this->state_msg.steer_ang 	= this->state_vector(5);

	return this->state_msg;
}


void EKF::motion_model(double deltaT)
{
	//TODO: implement
}


Eigen::VectorXd measurement_model(vector<double> sensor_data)
{
	//Declare local variables
	Eigen::VectorXd zk;

	//Set zk to the measurement
	for(int i = 0; i < sensor_data.size(); ++i)
	{
		zk(i) = sensor_data[i];
	}

	//Subtract the state estimate from zk to find innovation
	zk = zk - this->state_vector;

	//Return innovation (zk here is now innovation)
	return zk;
}