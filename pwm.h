/*
 * pwm.h
 *
 *  Created on: 15/nov/2015
 *      Author: massimo
 */
 // This class defines the behaviour of PWM driven by TIMER A0 on PIN P1.2 - P1.5 and with control registers #1,2,3,4


#ifndef PWM_H_
#define PWM_H_

#include <stdint.h>

class pwm {
public:
	pwm();
	virtual ~pwm();
	/// methods
	void setup(uint32_t freq, uint16_t tPWM);
	void pinSetting(uint8_t pin);
	/// value in term of pwm with a scale factor
	void pinValue(uint8_t pin, uint8_t val, uint16_t scale);
	/// value used an integer angolar value
	void pinValue(uint8_t pin, int8_t angle);

private:
	/// proprties
	uint16_t T_PWM;
};

#endif /* PWM_H_ */
