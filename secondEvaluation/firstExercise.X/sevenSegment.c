#include"sevenSegment.h"

uint8_t selectDisplay(uint8_t whichDisp)
{
    switch(whichDisp)
    {
        case 1:
            DDRC = (1<<FIRST_7SEG);// PC4 as output 
            PORTC &= ~(1<<whichDisp); // Pull internally PC0 to GND
            break;
        case 2:
            DDRC = (1<<SECOND_7SEG);
            PORTC &= ~(1<<whichDisp);
            break;
        case 3:
            DDRC = (1<<THIRD_7SEG);
            PORTC &= ~(1<<whichDisp);
            break;
        case 4:
            DDRC = (1<<FOURTH_7SEG);
            PORTC &= ~(1<<whichDisp);
            break;            
    }
    return 0;
}

uint8_t selectNumber(uint8_t whichNumber)
{
    DDRB |= (1<<PB0); // 7-seg display is divided between PORTB and PORTD, one
                      // pin is connected to PB0, so we must set PB0 as output.
    DDRD |= 0b11111111; // Almost all 7-seg pins are connected to PORTD, so we
                        // must set PORTD as output.
    switch(whichNumber)
    {
        case 0: // number 0 is some pins from PORTD and one pin from PORTB
            PORTD = ZERO_7SEG;
            PORTB = (1<<PB0);
            break;
        case 1:
            PORTB = (0<<PB0);
            PORTD = ONE_7SEG;
            break;
        case 2:
            PORTD = TWO_7SEG;
            break;
        case 3:
            PORTD = THREE_7SEG;
            break;
        case 4:
            PORTD = FOUR_7SEG;
            PORTB = (1<<PB0);
            break;
        case 5:
            PORTD = FIVE_7SEG;
            PORTB = (1<<PB0);
            break;
        case 6:
            PORTD = SIX_7SEG;
            PORTB = (1<<PB0);
            break;
        case 7:
            PORTD = SEVEN_7SEG;
            break;
        case 8:
            PORTD = EIGHT_7SEG;
            PORTB = (1<<PB0);
            break;
        case 9:
            PORTD = NINE_7SEG;
            PORTB = (1<<PB0);
            break;
    }
    return 0;
}

/// Function for more convenience
uint8_t displayNumber(uint8_t whichDisp, uint8_t whichNumber)
{
    selectDisplay(whichDisp);
    selectNumber(whichNumber);
    return 0;
}


