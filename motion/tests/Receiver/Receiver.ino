#include <SPI.h>
#include "RF24.h"
#include "MotionSetup.h"
#include "MotionLoop.h"

const unsigned long kill = 1;
const unsigned long reset = 2;
const unsigned long pause = 3;

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

		if(message==kill){
			drivetrain.disable();
		}else if(message==reset){
			drivetrain.enable();
			drivetrain.setPower(0.3);
		}
	}
}
