#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>


#define FIRST_BUTTON    PB2
#define SECOND_BUTTON   PB3
#define THIRD_BUTTON    PB4
#define FOURTH_BUTTON   PB5


uint8_t detectButton();

