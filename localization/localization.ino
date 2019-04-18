#include <ros.h>
#include "roma_msgs/localization_data.h"

//FIXME: Make these things not broken. Also, use the SCR_bno055 file?
#include "GPSModule.h"
#include "IMU.h"

#include "LocalizationGlobals.h"
#include "LocalizationSetup.h"

//Set up ROS node
ros::NodeHandle_<ArduinoHardware, 1, 1, 16, 128> localization_node;

//Set up ROS publisher
roma_msgs::localization_data local_data;
ros::Publisher data_pub("/roma_localization/data", &local_data);
 
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
	local_data.vel = 0;
	local_data.accel_x = imu0.getAccelX();
	local_data.heading = imu0.getOrientX();

	//Publish the message
	data_pub.publish(&local_data);

	localization_node.spinOnce();

	intellectualWait(100);	
}
