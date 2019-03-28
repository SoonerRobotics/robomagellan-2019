#include <ros.h>
#include "roma_msgs/localization_data.h"

#include "GPSModule.h"
#include "IMU.h"
#include "LocalizationGlobals.h"
#include "LocalizationSetup.h"

//Set up ROS node
ros::NodeHandle localization_node;

//Set up ROS publisher
roma_msgs::localization_data local_data;
ros::Publisher data_pub("/roma_localization/data", &local_data);
 
void setup() 
{
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
    /*
	dataArray["gps_lat"] = gps.getLat();
    dataArray["gps_lon"] = gps.getLong();
    dataArray["imu_heading"] = imu0.getOrientX();
    dataArray["imu_accel_x"] = imu0.getAccelX();
    dataArray["imu_accel_y"] = imu0.getAccelY();
    dataArray["encoder_dx"] = 0;
    dataArray["encoder_dt"] = 0;
	*/

    //Form localization msg
	local_data.gps_lat = gps.getLat();
	local_data.gps_lon = gps.getLong();
	local_data.vel = 0;
	local_data.accel_x = imu0.getAccelX();
	local_data.heading = imu0.getOrientX();

	//Publish message to topic
	data_pub.publish(&local_data);

	//Spin for callbacks
	localization_node.spinOnce();

    intellectualWait(1000 / SERIAL_SEND_RATE);
}
