#include "roma_kalman/EKF.h"


EKF::EKF()
{

}

EKF::EKF(Eigen::VectorXd xo, Eigen::MatrixXd Po)
{
	this->init(xo, Po);
}


void EKF::init(Eigen::VectorXd xo, Eigen::MatrixXd Po)
{
	/**Initialize the Jacobians! **/
	//Fk = Jacobian for motion model
	this->Fk = Eigen::MatrixXd::Identity(NUM_STATES, NUM_STATES);

	//Hk = Jacobian of the measurement function
	this->Hk = Eigen::MatrixXd::Identity(NUM_STATES, NUM_STATES);

	/** Set the filter initial conditions **/
	this->state_vector = Eigen::VectorXd::Zero(NUM_STATES);
	this->last_state = xo;
	this->Pk = Eigen::MatrixXd::Identity(NUM_STATES, NUM_STATES) * 0.1;
	this->Pk_last = Po;

	/** Timing variables **/
	this->last_time = ros::Time::now().toNSec() / 1000.0 / 1000.0 / 1000.0;

	/** Set up the noise matrices **/
	this->R = Eigen::MatrixXd::Identity(NUM_STATES, NUM_STATES) * 0.5;
	this->Q = Eigen::MatrixXd::Identity(NUM_STATES, NUM_STATES) * 0.6;

	//Output that the kalman filter is initialized
	printf("EKF initialized\n");
}


void EKF::run_filter(std::vector<double> sensor_data)
{
	//Declare local variables
	double current_time;
	double deltaT;

	//Get timing in nsec and convert to seconds
	current_time = ros::Time::now().toNSec() / 1000.0 / 1000.0 / 1000.0;
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
	this->Pk = (Eigen::MatrixXd::Identity(NUM_STATES, NUM_STATES) - (this->Gk * this->Hk)) * this->Pk;

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
	this->state_msg.latitude 	= this->state_vector(0);
	this->state_msg.longitude 	= this->state_vector(1);
	this->state_msg.velocity 	= this->state_vector(2);
	this->state_msg.accel 		= this->state_vector(3);
	this->state_msg.heading		= this->state_vector(4);
	this->state_msg.steer_ang 	= this->state_vector(5);

	return this->state_msg;
}


void EKF::motion_model(double deltaT)
{
	//Run the physics equations to estimate current state
	this->state_vector(0) = this->last_state(0) + (this->last_state(2) * cos(this->last_state(4) * M_PI / 180.0) * sin(last_state(5) * M_PI / 180.0) * deltaT);
	this->state_vector(1) = this->last_state(1) + (this->last_state(2) * cos(this->last_state(4) * M_PI / 180.0) * cos(last_state(5) * M_PI / 180.0) * deltaT);
	this->state_vector(2) = this->last_state(2) + (this->last_state(3) * deltaT);
	this->state_vector(3) = this->last_state(3);
	this->state_vector(4) = this->last_state(4) + (this->last_state(2) / WHEELBASE_LENGTH) * tan(this->last_state(5));
	this->state_vector(5) = this->last_state(5);

	//Update the jacobian of the motion model based on the last values
	//Latitude depends on velocity, steering angle, and heading
	this->Fk(0, 2) = cos(last_state(4) * M_PI / 180.0) * sin(last_state(5) * M_PI / 180.0);
	this->Fk(0, 4) = last_state(2) * cos(last_state(4) * M_PI / 180.0) * cos(last_state(5) * M_PI / 180.0);
	this->Fk(0, 5) = -last_state(2) * cos(last_state(4) * M_PI / 180.0) * sin(last_state(5) * M_PI / 180.0);
	
	//Longitude depends on the same things Latitude does
	this->Fk(1, 2) = cos(last_state(4) * M_PI / 180.0) * cos(last_state(5) * M_PI / 180.0);
	this->Fk(1, 4) = -last_state(2) * sin(last_state(4) * M_PI / 180.0) * cos(last_state(5) * M_PI / 180.0);
	this->Fk(1, 5) = -last_state(2) * cos(last_state(4) * M_PI / 180.0) * sin(last_state(5) * M_PI / 180.0);

	//Heading depends on velocity and steering angle
	this->Fk(4, 2) = tan(last_state(5) * M_PI / 180) / WHEELBASE_LENGTH;
	this->Fk(4, 5) = (last_state(2) / WHEELBASE_LENGTH) * pow(1 / tan(last_state(5)), 2);
}


Eigen::VectorXd EKF::measurement_model(std::vector<double> sensor_data)
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