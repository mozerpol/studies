#include "controlDCmotor.h"

void init_TIMER2(void)
{
	TCCR2 |= (1<<WGM20); // Fast PWM
	TCCR2 |= (1<<COM21); // Clear OC2 on Compare Match
	TCCR2 |= (1<<CS22)|(1<<CS21);	// Prescaler: 256
	TCNT2 = 0; // Actual value of counter
	OCR2 = 0; // Count up to this value. This reg is changing in main file.
}

void init_MOTOR(void)
{
    MOTOR_DDR |= (1<<MOTOR_PIN);
    MOTOR_PORT |= (1<<MOTOR_PIN);
}