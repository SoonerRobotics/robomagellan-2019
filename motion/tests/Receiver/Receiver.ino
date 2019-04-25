#include "RF24.h"

RF24 radio(9,10);

byte addresses[][6] = {"1Node","2Node"};

void setup() {
	radio.begin();

	radio.setPALevel(RF24_PA_HIGH);
	radio.maskIRQ(1,1,0);

	radio.openWritingPipe(addresses[0]);
	radio.openReadingPipe(0,addresses[1]);

	radio.startListening();

	attachInterrupt(0, receive, FALLING);
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
	}
}
