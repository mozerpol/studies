#include"sevenSegment.h"

uint8_t selectDisplay(uint8_t whichDisp)
{
    switch(whichDisp)
    {
        case 1:
            DDRC = ((DDRC & MASK_PORTC) | FIRST_7SEG);
            break;
        case 2:
            DDRC = ((DDRC & MASK_PORTC) | SECOND_7SEG);
            break;
        case 3:
            DDRC = ((DDRC & MASK_PORTC) | THIRD_7SEG);
            break;
        case 4:
            DDRC = ((DDRC & MASK_PORTC) | FOURTH_7SEG);
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
        case 0:
            PORTD = ZERO_7SEG; // mask is not necessary, because all PORTD is
                               // for 7seg display purposes.
            PORTB = ((PORTB & MASK_PORTB) | 0b00000001);
            break;
        case 1:
            PORTB = (PORTB & MASK_PORTB);
            PORTD = ONE_7SEG;
            break;
        case 2:
            PORTB = (PORTB & MASK_PORTB);
            PORTD = TWO_7SEG;
            break;
        case 3:
            PORTB = (PORTB & MASK_PORTB);
            PORTD = THREE_7SEG;
            break;
        case 4:
            PORTB = ((PORTB & MASK_PORTB) | 0b00000001);
            PORTD = FOUR_7SEG;
            break;
        case 5:
            PORTB = ((PORTB & MASK_PORTB) | 0b00000001);
            PORTD = FIVE_7SEG;
            break;
        case 6:
            PORTB = ((PORTB & MASK_PORTB) | 0b00000001);
            PORTD = SIX_7SEG;
            break;
        case 7:
            PORTB = (PORTB & MASK_PORTB);
            PORTD = SEVEN_7SEG;
            break;
        case 8:
            PORTB = ((PORTB & MASK_PORTB) | 0b00000001);
            PORTD = EIGHT_7SEG;
            break;
        case 9:
            PORTB = ((PORTB & MASK_PORTB) | 0b00000001);
            PORTD = NINE_7SEG;
            break;
        default:
            PORTD = MINUS_SIGN;
            PORTB = (PORTB & MASK_PORTB);
            break; 
    }
    return 0;
}

/// Function for more convenience
uint8_t showNumber(uint8_t whichDisp, uint8_t whichNumber)
{
    selectNumber(whichNumber);
    selectDisplay(whichDisp);
    
    return 0;
}