#include "RF24.h"

#define LED_PIN 4

RF24 radio(9,10);

byte addresses[][6] = {"1Node","2Node"};

byte state = 0;

void setup()
{
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, LOW);

	radio.begin();

	radio.setPALevel(RF24_PA_HIGH);
	radio.maskIRQ(1,1,0);
	radio.openReadingPipe(0,addresses[1]);
	radio.startListening();

	attachInterrupt(0, receive, FALLING);
}

void loop()
{
	if (state > 0) {
		for (int i=0; i<state; ++i) {
			blink(LED_PIN);
		}
		state = 0;
	}
}

void blink(byte pin)
{
	digitalWrite(pin, LOW);
	delay(100);
	digitalWrite(pin, HIGH);
	delay(100);
	digitalWrite(pin, LOW);
}

void receive()
{
	byte message;

	if(radio.available()) {
		while(radio.available()) {
			radio.read(&message, sizeof(byte));
		}
	}
	state = message;
}
