#include <SPI.h>
#include "RF24.h"

const int kill_button = 2;
const int reset_button = 3;
const int pause_button = 4;
const int success_led = 5;
const int fail_led = 6;

const unsigned long kill = 1;
const unsigned long reset = 2;
const unsigned long pause = 3;

RF24 radio(9,10);

byte addresses[][6] = {"1Node","2Node"};

void setup(){
	Serial.begin(115200);
	Serial.println(F("Starting Transmitter..."));

	pinMode(kill_button, INPUT);
	pinMode(success_led, OUTPUT);
	digitalWrite(success_led, LOW);
	pinMode(fail_led, OUTPUT);
	digitalWrite(fail_led, LOW);

	radio.begin();

	//This level might have to be increased for real use.
	radio.setPALevel(RF24_PA_LOW);

	radio.openWritingPipe(addresses[1]);
	radio.openReadingPipe(1,addresses[0]);

	radio.startListening();
}

int send_message(unsigned long message){
	Serial.print(F("Sending "));
	Serial.println(message);

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
			return(1); //success
		}else{
			Serial.println(F("Transmission corrupted"));
		}
	}
	return(0); //fail
}

unsigned long read_buttons(){
	if(digitalRead(kill_button)){
		return(kill);
	}else if(digitalRead(reset_button)){
		return(reset);
	}else if(digitalRead(pause_button)){
		return(pause);
	}else{
		return(0);
	}
}
void loop(){
	unsigned long button;
	if(button = read_buttons()){
		if(send_message(button)){
			digitalWrite(success_led, HIGH);
			delay(1000);
			digitalWrite(success_led, LOW);
		}else{
			for(int i=0;i<5;i++){
				digitalWrite(fail_led, HIGH);
				delay(100);
				digitalWrite(fail_led, LOW);
				delay(100);
			}
		}
	}
}
