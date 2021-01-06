#include <avr/io.h>
#include <avr/interrupt.h>

// Macros that simplify access to ports
#define SEL_DISPLAY_DDR  DDRC 
#define SEL_NUMBER_DDR   DDRD
#define SEL_NUMBER_PORT  PORTD

// Macros for displaying numbers on the 7segment display (at PORTD in this case)
#define ZERO_7SEG   0b10111111
#define ONE_7SEG    0b00100100
#define TWO_7SEG    0b11011100
#define THREE_7SEG  0b11110100
#define FOUR_7SEG   0b01100110
#define FIVE_7SEG   0b11110010
#define SIX_7SEG    0b11111010
#define SEVEN_7SEG  0b10100100
#define EIGHT_7SEG  0b11111111
#define NINE_7SEG   0b11110110

// Macros for selecting 7 segment display at PORTC
#define FIRST_7SEG  0b00000001
#define SECOND_7SEG 0b00000010
#define THIRD_7SEG  0b00000100
#define FOURTH_7SEG 0b00001000

#define MASK_PORTC  0b11110000
#define MINUS_SIGN  0b01000000
#define A_CHAR      0b11101111
#define D_CHAR      0b10111111


uint8_t selectDisplay(uint8_t whichDisp); // return 0
uint8_t selectNumber(uint8_t whichNumber); // return 0
uint8_t showNumber(uint8_t whichDisp, uint8_t whichNumber); // return 0
void init_TIMER0(void); // Will be use for multiplexing displays