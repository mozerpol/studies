#include "controlDCmotor.h"

void init_TIMER2(void)
{
	TCCR2 |= (1<<WGM20); // Fast PWM
	TCCR2 |= (1<<COM21); // Clear OC2 on Compare Match
	TCCR2 |= (1<<CS22);	// Prescaler: 64 

	TCNT2 = 0; // Actual value of counter
	OCR2 = 12; // Count up to this value
}

void init_TIMER0(void)
{
	TCCR0 |= (1<<CS01); // Prescaler: 8 

	TCNT0 = 0; // Actual value of counter
    TIMSK |= (1<<TOIE0); // Turn on interrupt
}