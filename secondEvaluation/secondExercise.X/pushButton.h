#include <avr/io.h>
#include <util/delay.h>

// Macros that simplify access to ports
#define BUTTON_DDR      DDRB
#define BUTTON_PORT     PORTB
#define BUTTON_PIN      PINB
#define BLINK_PORT      PB1

// Buttons are connected to these pins
#define FIRST_BUTTON    PB2
#define SECOND_BUTTON   PB3
#define THIRD_BUTTON    PB4
#define FOURTH_BUTTON   PB5


uint8_t detectButton(); // Recognize pressed button 
void init_Buttons(void); // Init ports
void blinkLED(void); // Blink LED on BLINK_PORT