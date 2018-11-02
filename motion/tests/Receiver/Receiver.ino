#include <SPI.h>
#include "RF24.h"

RF24 radio(9,10);

byte addresses[][6] = {"1Node","2Node"};

void setup() {
	Serial.begin(115200);
	Serial.println(F("Starting Receiver..."));

	radio.begin();

	//This level might have to be increased for real use.
	radio.setPALevel(RF24_PA_LOW);

	radio.openWritingPipe(addresses[0]);
	radio.openReadingPipe(0,addresses[1]);

	radio.startListening();
}

void loop() {
	unsigned long message;

	if(radio.available()) {
		while(radio.available()) {
			radio.read(&message, sizeof(unsigned long));
		}

		Serial.print(F("Received message "));
		Serial.println(message);

		//Send confirmation of message
		radio.stopListening();
		radio.write(&message, sizeof(unsigned long));
		radio.startListening();

		Serial.println(F("Responded"));
	}
}
