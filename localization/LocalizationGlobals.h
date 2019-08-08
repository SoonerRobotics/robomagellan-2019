#ifndef LOCALIZATION_GLOBALS_H
#define LOCALIZATION_GLOBALS_H

#define SERIAL_SEND_RATE 100 // The frequency at which updates are sent through Serial

#define ENCODER_PIN 		2
#define NUM_SAMPLES 		4
#define VELOCITY_TIMEOUT 	2 * (1000 * 1000)		//timeout to 0 m/s after 2 second of inaction
#define WHEEL_RAD 			(float)(0.05)			//Wheel radius in meters (m)

#endif
