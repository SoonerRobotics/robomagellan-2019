#include <Wire.h>
#include <RobotLib.h>

#define SLAVE_ADDRESS 0x04
int number = 0;
int state = 0;

float max = 255;

Motor motor1;
Motor motor2;

void setup() {
    pinMode(13, OUTPUT);
    Serial.begin(9600); // start serial for output
    // initialize i2c as slave
    Wire.begin(SLAVE_ADDRESS);

    motor1.begin(4, 5, 3);
    motor2.begin(7, 8, 6);

    // define callbacks for i2c communication
    Wire.onReceive(receiveData);
    Wire.onRequest(sendData);

    Serial.println("Ready!");
}

void loop() {
    delay(100);
}

// callback for received data
void receiveData(int byteCount){

    while(Wire.available()) {
        number = Wire.read();
        Serial.print("data received: ");
        Serial.println(number);

        float motorOutput = number/max;

        motor1.output(motorOutput);
        motor2.output(motorOutput);
    }
}

// callback for sending data
void sendData(){
    Wire.write(number);
}