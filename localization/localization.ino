#include <ros.h>
#include "roma_msgs/localization_data.h"

#include "GPSModule.h"
#include "IMU.h"

#include "LocalizationGlobals.h"
#include "LocalizationSetup.h"

//Set up ROS node
ros::NodeHandle_<ArduinoHardware, 1, 1, 16, 128> localization_node;

//Set up ROS publisher
roma_msgs::localization_data local_data;
ros::Publisher data_pub("/roma_localization/data", &local_data);
 
void encoder_interrupt()
{
	//Get the distance travelled by a single rotation
	float dist_travelled = 2 * PI * WHEEL_RAD;
	
	//Calculate the time it took to turn the wheel
	cur_time = micros();
	deltaT = (float)(cur_time - last_interrupt) / 1000.0 / 1000.0;

	//Calculate robot velocity from the above two measurements
	velocity_samples[vel_idx] = dist_travelled / (deltaT + 0.001);

	//Increment the index counter
	++vel_idx;
	vel_idx >= NUM_SAMPLES ? 0 : vel_idx;

	//Save the last interrupt
	last_interrupt = cur_time;
}


float calculate_velocity()
{
	float vel = 0.0;

	//Get the current time for timing checks
	cur_time = micros();

	//If it has been too long since the last update, reset the velocity
	if((cur_time - last_interrupt) > VELOCITY_TIMEOUT)
	{
		for(int i = 0; i < NUM_SAMPLES; ++i)
		{
			velocity_samples[i] = 0.0;
		}

		return 0.0;
	}
	
	//Get a moving average of the velocity
	for(int i = 0; i < NUM_SAMPLES; ++i)
	{
		vel += (1 / NUM_SAMPLES) * velocity_samples[i];
	}

	return vel;
}


void setup() 
{
	//Set serial communication to be 115200 baud
	Serial.begin(57600);

	//Set up ROS node
	localization_node.initNode();
	localization_node.advertise(data_pub);

    localizationSetup();

    intellectualWait(1000);

    imu0.zero();

	//Add the interrupt for the encoder
	attachInterrupt(digitalPinToInterrupt(ENCODER_PIN), &encoder_interrupt, RISING);
}


void intellectualWait(unsigned long ms) {
    unsigned long startTime = millis();
    while (millis() - startTime < ms) {
        gps.update();
        imu0.update();
    }
}

void loop() 
{
	//Form localization msg
	local_data.gps_lat = gps.getLat();
	local_data.gps_lon = gps.getLong();
	//local_data.vel = calculate_velocity();
	local_data.vel = 1.0;
	local_data.accel_x = imu0.getAccelX();
	local_data.heading = imu0.getOrientX();

	//Serial.println(local_data.vel);

	//Publish the message
	data_pub.publish(&local_data);

	localization_node.spinOnce();

	intellectualWait(10);	
}
