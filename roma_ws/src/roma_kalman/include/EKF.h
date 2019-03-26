#ifndef EXT_KALMAN_FILTER_H
#define EXT_KALMAN_FILTER_H

#include <ros/ros.h>
#include <eigen3/Eigen/Dense.h>

class EKF
{
	public:

		EKF();

		void run_filter(vector<double> sensor_data);

		vector<double> get_state();

	private:

		vector<double> state;

		Eigen::MatrixXd Fk;
		Eigen::MatrixXd Gk;
		Eigen::MatrixXd Hk;
		Eigen::MatrixXd Pk;

		Eigen::MatrixXd Q, R;

		void 
};

#endif