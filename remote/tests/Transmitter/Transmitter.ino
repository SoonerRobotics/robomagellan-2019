#include <SPI.h>
#include "RF24.h"

unsigned long message = 1;

RF24 radio(9,10);

byte addresses[][6] = {"1Node","2Node"};

void setup(){
	Serial.begin(115200);
	Serial.println(F("Starting Transmitter..."));

	radio.begin();

	//This level might have to be increased for real use.
	radio.setPALevel(RF24_PA_LOW);

	radio.openWritingPipe(addresses[1]);
	radio.openReadingPipe(1,addresses[0]);

	radio.startListening();
}

void loop(){
	radio.stopListening();

	if(!radio.write(&message,sizeof(unsigned long))){
		Serial.println(F("Failed, unable to write"));
	}

	//Listen for confirmation message
	radio.startListening();

	unsigned long wait_start = micros();
	boolean timeout = false;

	//Don't wait forever
	while(!radio.available()){
		if(micros() - wait_start > 200000){
			timeout = true;
			break;
		}
	}

	if(timeout){
		Serial.println(F("Failed, response timed out"));
	}else{
		unsigned long response;
		radio.read(&response, sizeof(unsigned long));

		//Check response
		if(response == message){
			Serial.println(F("Transmission successful"));
		}else{
			Serial.println(F("Transmission corrupted"));
		}
	}

	delay(1000);
}
