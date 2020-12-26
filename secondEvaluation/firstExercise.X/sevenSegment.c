#include"sevenSegment.h"

uint8_t selectDisplay(uint8_t whichDisp)
{
    DDRC = (1<<whichDisp); // PC4 as output 
    PORTC &= ~(1<<whichDisp); // Pull internally PC4 to GND
    return 0;
}

uint8_t selectNumber(uint8_t whichNumber)
{
    DDRB |= (1<<PB0);
    DDRD |= 0b11111111;
    switch(whichNumber)
    {
        case 0:
            PORTD = 0b10111111;
            PORTB = (1<<PB0);
            break;
        case 1:
            PORTB = (0<<PB0);
            PORTD = 0b00100100;
            break;
        case 2:
            PORTD = 0b11011100;
            break;
        case 3:
            PORTD = 0b11110100;
            break;
        case 4:
            PORTD = 0b01100100;
            PORTB = (1<<PB0);
            break;
        case 5:
            PORTD = 0b11110000;
            PORTB = (1<<PB0);
            break;
        case 6:
            PORTD = 0b11111000;
            PORTB = (1<<PB0);
            break;
        case 7:
            PORTD = 0b10100100;
            break;
        case 8:
            PORTD = 0b11111111;
            PORTB = (1<<PB0);
            break;
        case 9:
            PORTD = 0b11110100;
            PORTB = (1<<PB0);
            break;
    }
    return 0;
}

uint8_t displayNumber(uint8_t whichDisp, uint8_t whichNumber)
{
    selectDisplay(whichDisp);
    selectNumber(whichNumber);
    return 0;
}


