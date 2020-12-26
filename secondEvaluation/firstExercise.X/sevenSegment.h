#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/io.h>

uint8_t selectDisplay(uint8_t whichDisp);
uint8_t selectNumber(uint8_t whichNumber);
uint8_t displayNumber(uint8_t whichDisp, uint8_t whichNumber);

