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
	/// value with 0.1 % granularity
	SERVO.pinValue(P1_2, 50, 10);
}

void loop() {
  // put your main code here, to run repeatedly: 

}


