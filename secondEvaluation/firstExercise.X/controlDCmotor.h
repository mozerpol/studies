#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>


#define MOTOR_VELOCITY  OCR2

void init_TIMER2(void);
void init_MOTOR(void);