#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>

// Macros for displaying numbers on the 7 segment display at PORTD
#define ZERO_7SEG   0b10111111
#define ONE_7SEG    0b00100100
#define TWO_7SEG    0b11011100
#define THREE_7SEG  0b11110100
#define FOUR_7SEG   0b01100100
#define FIVE_7SEG   0b11110000
#define SIX_7SEG    0b11111000
#define SEVEN_7SEG  0b10100100
#define EIGHT_7SEG  0b11111111
#define NINE_7SEG   0b11110100
#define MASK_PORTD  0b00000011
// Macros for selecting 7 segment display at PORTC
#define FIRST_7SEG  0b00000001
#define SECOND_7SEG 0b00000010
#define THIRD_7SEG  0b00000100
#define FOURTH_7SEG 0b00001000
#define MASK_PORTC  0b11110000



uint8_t selectDisplay(uint8_t whichDisp); // return 0
uint8_t selectNumber(uint8_t whichNumber); // return 0
uint8_t displayNumber(uint8_t whichDisp, uint8_t whichNumber); // return 0

void TIMER2_init(void); // CTC, 1MHz/64/78 = 200 Hz = 5 ms