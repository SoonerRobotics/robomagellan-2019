#include "RF24.h"

#define KILL_BUTTON 2
#define RESET_BUTTON 3
#define PAUSE_BUTTON 4
#define SUCCESS_LED 5
#define FAIL_LED 6

#define MSG_KILL 1
#define MSG_RESET 2
#define MSG_PAUSE 3

RF24 radio(9,10);

byte addresses[][6] = {"1Node","2Node"};

/*
 * This method sets up all of the pins and the radio.
 */
void setup()
{
	// Setup pins
	pinMode(KILL_BUTTON, INPUT);
	pinMode(RESET_BUTTON, INPUT);
	pinMode(PAUSE_BUTTON, INPUT);
	pinMode(SUCCESS_LED, OUTPUT);
	pinMode(FAIL_LED, OUTPUT);
	digitalWrite(SUCCESS_LED, LOW);
	digitalWrite(FAIL_LED, LOW);

	// Setup radio
	radio.begin();
	radio.setPALevel(RF24_PA_MAX);
	radio.openWritingPipe(addresses[1]);
	// May not be necessary
	// radio.openReadingPipe(1,addresses[0]);
	radio.stopListening();
}

/*
 * Reads the buttons and returns the corresponding message.
 * If none of the buttons are depressed, it returns zero.
 * This is useful for is statements.
 */
byte read_buttons()
{
	if (digitalRead(KILL_BUTTON)) {
		return MSG_KILL;
	} else if (digitalRead(RESET_BUTTON)) {
		return MSG_RESET;
	} else if (digitalRead(PAUSE_BUTTON)) {
		return MSG_PAUSE;
	} else {
		return 0;
	}
}

/*
 * Blinks the success led to indicate success.
 */
void success()
{
	digitalWrite(SUCCESS_LED, HIGH);
	delay(1000);
	digitalWrite(SUCCESS_LED, LOW);
}

/*
 * Blinks the failure led to indicate failure.
 */
void failure()
{
	for (byte i=0;i<5;i++) {
		digitalWrite(FAIL_LED, HIGH);
		delay(100);
		digitalWrite(FAIL_LED, LOW);
		delay(100);
	}
}

/*
 * This loop repeatedly reads the buttons and send a message when one is
 * depressed.
 */
void loop()
{
	byte message;
	if (message = read_buttons()) {
		if (radio.write(&message,sizeof(byte))) {
			success();
		} else {
			failure();
		}
	}
}
