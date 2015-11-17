/*
 * pwm.cpp
 *
 *  Created on: 15/nov/2015
 *      Author: massimo
 */

#include "pwm.h"
#include "Energia.h"


pwm::pwm() {
	// TODO Auto-generated constructor stub
	T_PWM = 0;

}

pwm::~pwm() {
	// TODO Auto-generated destructor stub
}

void pwm::setup(uint32_t freq, uint16_t tPwm){
	/// used pins are from P1.2 to P1.4
//	P1DIR |= BIT1 + BIT2 + BIT3 + BIT4;
//	P2SEL |= BIT1 + BIT2 + BIT3 + BIT4;;

#if defined(__MSP430_HAS_TA3__) || defined(__MSP430_HAS_T0A3__) || defined(__MSP430_HAS_T0A5__) || defined(__MSP430_HAS_TA5__)
	/// TIMER0 is present

	if(freq >= 3200000)
		TA0CTL 	= TASSEL_2 + MC_1 + TACLR + ID_3;	/// si usa il clock di sistema fdco >= 16MHZ
	else
		TA0CTL 	= TASSEL_2 + MC_1 + TACLR; 	/// si usa il clock di sistema fdco = 24.576MHz
	/// la frequenza è divisa per 8 dal coefficiente ID_3. Quindi F1 = fdco/8 = 3.072MHz
	/// F1 / T_PWM = 3.072000 / 8000 = 384; numero di conteggi da scrivere in TA2CCR0
	TA0CCR0 = (freq >> 3) / tPwm;

	/// PWM mode
	TA0CCTL1 = OUTMOD_7;
	TA0CCTL2 = OUTMOD_7;
	TA0CCTL3 = OUTMOD_7;
	TA0CCTL4 = OUTMOD_7;
	//TA0CCTL5 = OUTMOD_7;
	//TA0CCTL6 = OUTMOD_7;

	/// initial value on different PWM output
	TA0CCR1 = 0;
	TA0CCR2 = 0;
	TA0CCR3 = 0;
	TA0CCR4 = 0;
	//TA0CCR5 = 0;
	//TA0CCR6 = 0;
	// set up PWM period
	T_PWM = tPwm;
#endif
}


void pwm::pinSetting(uint8_t pin){
    uint8_t bit = digitalPinToBitMask(pin); // get pin bit
    uint8_t port = digitalPinToPort(pin);   // get pin port
    volatile uint8_t *sel;

    if (port == NOT_A_PORT) return; // pin on timer?

    sel = portSelRegister(port); // get the port function select register address
    *sel |= bit;                 // set bit in pin function select register
    /// set pin in output mode
    pinMode(pin, OUTPUT);

    TA0CCR0 = T_PWM;          		 		// PWM Period
}

void pwm::pinValue(uint8_t pin, uint8_t val, uint16_t scale){
    switch(digitalPinToTimer(pin)) {                // which timer and CCR?
	//case: T0A0                            // CCR0 used as period register
	case T0A1:                              // TimerA0 / CCR1

	 TA0CCTL1 = OUTMOD_7;            		// reset/set
	 TA0CCR1 = T_PWM / (100 * scale) * val; 			// PWM duty cycle
	 break;

	case T0A2:                              // TimerA0 / CCR1

	 TA0CCTL2 = OUTMOD_7;            		// reset/set
	 TA0CCR2 = T_PWM / (100 * scale) * val; 			// PWM duty cycle
	 break;

	case T0A3:                              // TimerA0 / CCR1

	 TA0CCTL3 = OUTMOD_7;            		// reset/set
	 TA0CCR3 = T_PWM / (100 * scale) * val; 			// PWM duty cycle
	 break;

	case T0A4:                              // TimerA0 / CCR1

	 TA0CCTL4 = OUTMOD_7;            		// reset/set
	 TA0CCR4 = T_PWM / (100 * scale) * val; 			// PWM duty cycle
	 break;

    }
}

/// value used an integer angolar value
void pwm::pinValue(uint8_t pin, int8_t angle){

	int16_t valore;
	float fVal;
	/// conversion from angle to PWM value
	if (angle > 90)
		angle = 90;
	else if(angle < -90)
		angle = -90;

	/// granularity is 0.1%
	/// a PWM between 5 to 10% is split in 150 parts
	fVal = angle / 90 * 2.5 + 7.5;
	fVal *= 30;
	valore = (int16_t) fVal;
	pinValue(pin, valore, 30);
	Serial.print("valore PWM: ");
	Serial.println(valore);
}
