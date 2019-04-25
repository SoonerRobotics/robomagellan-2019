#include "RF24.h"

const int KILL_BUTTON = 2;
const int RESET_BUTTON = 3;
const int PAUSE_BUTTON = 4;
const int SUCCESS_LED = 5;
const int FAIL_LED = 6;

const unsigned long KILL = 1;
const unsigned long RESET = 2;
const unsigned long PAUSE = 3;

RF24 radio(9,10);

byte addresses[][6] = {"1Node","2Node"};

void setup() {
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
	radio.setPALevel(RF24_PA_HIGH);
	radio.openWritingPipe(addresses[1]);
	radio.openReadingPipe(1,addresses[0]);
	radio.startListening();
}

bool send_message(unsigned long message) {
	radio.stopListening();

	if (!radio.write(&message,sizeof(unsigned long))) {
		return 0; // Unable to write
	}

	// Listen for confirmation message
	radio.startListening();

	unsigned long wait_start = micros();

	// Don't wait forever
	while (!radio.available()) {
		if (micros() - wait_start > 1000000) {
			return 0; // Timeout
		}
	}

	unsigned long response;
	radio.read(&response, sizeof(unsigned long));

	//Check response
	if (response == message) {
		return 1; // Success
	} else {
		return 0; // Corruption
	}
}

unsigned long read_buttons() {
	if (digitalRead(KILL_BUTTON)) {
		return KILL;
	} else if (digitalRead(RESET_BUTTON)) {
		return RESET;
	} else if (digitalRead(PAUSE_BUTTON)) {
		return PAUSE;
	} else {
		return 0;
	}
}

void loop() {
	unsigned long message;
	if (message = read_buttons()) {
		if (send_message(message)) {
			// Success
			digitalWrite(SUCCESS_LED, HIGH);
			delay(1000);
			digitalWrite(SUCCESS_LED, LOW);
		} else {
			// Fail
			for (int i=0;i<5;i++) {
				digitalWrite(FAIL_LED, HIGH);
				delay(100);
				digitalWrite(FAIL_LED, LOW);
				delay(100);
			}
		}
	}
}
