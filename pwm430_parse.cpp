#include "Energia.h"
#include "pwm.h"


void setup();
void loop();

pwm SERVO;

void setup() {
  // put your setup code here, to run once:
	SERVO.setup(F_CPU, 50);
}

void loop() {
  // put your main code here, to run repeatedly: 
	SERVO.pinSetting(P1_2, 10);
	SERVO.pinSetting(P1_3, 30);
	SERVO.pinSetting(P1_4, 60);
	SERVO.pinSetting(P1_5, 80);
}


