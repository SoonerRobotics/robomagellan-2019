#include <SPI.h>
#include "RF24.h"
#include "MotionSetup.h"
#include "MotionLoop.h"

#define s_running 1
#define s_stopped 2
#define s_paused  3

const unsigned long m_kill = 1;
const unsigned long m_reset = 2;
const unsigned long m_pause = 3;

int state = s_stopped;

RF24 radio(9,10);

byte addresses[][6] = {"1Node","2Node"};

void setup() {
	radio.begin();

//This level might have to be increased for real use.
	radio.setPALevel(RF24_PA_LOW);
	radio.maskIRQ(1,1,0);

	radio.openWritingPipe(addresses[0]);
	radio.openReadingPipe(0,addresses[1]);

	radio.startListening();

	attachInterrupt(0, receive, FALLING);

	motionSetup();
	drivetrain.setPower(0.5);
	state = s_running;
}

void loop() {
	delay(10000);
}

void receive() {
	unsigned long message;

	if(radio.available()) {
		while(radio.available()) {
			radio.read(&message, sizeof(unsigned long));
		}

		//Send confirmation of message
		radio.stopListening();
		radio.write(&message, sizeof(unsigned long));
		radio.startListening();

		if(message==m_kill) {
			drivetrain.disable();
			state = s_stopped;
		}else if(message==m_reset) {
			drivetrain.enable();
			drivetrain.setPower(0.5);
			state = s_running;
		}else if(message==m_pause) {
			if(state==s_running) {
				drivetrain.disable();
				state = s_paused;
			}else if(state==s_paused) {
				drivetrain.enable();
				drivetrain.setPower(0.2);
				state = s_running;
			}
		}
	}
}
