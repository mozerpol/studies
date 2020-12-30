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
    DDRD |= 0b11111111; // Almost all 7-seg pins are connected to PORTD, so we
                        // must set PORTD as output.
    switch(whichNumber)
    {
        case 0:
            PORTD = ZERO_7SEG; // mask is not necessary, because all PORTD is
                               // for 7seg display purposes.
            break;
        case 1:
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
            break;
        case 5:
            PORTD = FIVE_7SEG;
            break;
        case 6:
            PORTD = SIX_7SEG;
            break;
        case 7:
            PORTD = SEVEN_7SEG;
            break;
        case 8:
            PORTD = EIGHT_7SEG;
            break;
        case 9:
            PORTD = NINE_7SEG;
            break;
        default:
            PORTD = MINUS_SIGN;
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

void init_TIMER0(void)
{
	TCCR0 |= (1<<CS01); // Prescaler: 8 

	TCNT0 = 0; // Actual value of counter
    TIMSK |= (1<<TOIE0); // Turn on interrupt
}