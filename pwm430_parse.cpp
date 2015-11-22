#include "Energia.h"
#include "pwm.h"


void setup();
void loop();

/// objects are global in Energia environment
pwm SERVO;

void setup() {
  // put your setup code here, to run once:
	/// SET up serial on usb bus
	Serial.begin(115200);
	Serial.println("Benvenuto nel sistema ENERGIA!");

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

}

void loop() {
  // demo of servo motion
	static int stato = 0;
	switch (stato){
	case 0:
		SERVO.pinValue(P1_2, 0);
		SERVO.pinValue(P1_3, 0);
		SERVO.pinValue(P1_4, 0);
		SERVO.pinValue(P1_5, 0);
		stato = 1;
	break;

	case 1:
		delay(500);
		SERVO.pinValue(P1_5, 5);
		SERVO.pinValue(P1_4, -15);
		delay(1000);
		stato = 2;
	break;

	case 2:
		SERVO.pinValue(P1_5, 25);
		SERVO.pinValue(P1_4, -65);
		delay(1000);
		stato = 1;
	break;
	}

}


