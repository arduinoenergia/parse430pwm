#include "Energia.h"
#include "pwm.h"


void setup();
void loop();

/// objects are global in Energia environment
pwm SERVO;

void setup() {
  // put your setup code here, to run once:
	SERVO.setup(F_CPU, 50);
	/// set up 4 pwm output
	SERVO.pinSetting(P1_2);
	SERVO.pinSetting(P1_3);
	SERVO.pinSetting(P1_4);
	SERVO.pinSetting(P1_5);
	/// value with 0.1 % granularity and in central position
	SERVO.pinValue(P1_2, 75, 10);
	SERVO.pinValue(P1_2, 75, 10);
	SERVO.pinValue(P1_2, 75, 10);
	SERVO.pinValue(P1_2, 75, 10);
	/// set up serial communication
	Serial.begin(9600);
}

void loop() {
  // demo of servo motion
	SERVO.pinValue(P1_2, 0);
	SERVO.pinValue(P1_3, 0);
	SERVO.pinValue(P1_4, 0);
	SERVO.pinValue(P1_5, 0);
	delay(500);
	SERVO.pinValue(P1_5, 5);
	SERVO.pinValue(P1_4, -15);
	delay(1000);
}


