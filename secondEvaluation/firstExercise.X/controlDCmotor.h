#include <avr/io.h>


// Macros that simplify access to ports
#define MOTOR_DDR   DDRB
#define MOTOR_PORT  PORTB
#define MOTOR_PIN   PB1

#define MOTOR_VELOCITY  OCR2 // Output pin for PWM

void init_TIMER2(void); // Will use for PWM
void init_MOTOR(void); // Init ports