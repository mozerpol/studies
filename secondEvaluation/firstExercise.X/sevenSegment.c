#include"sevenSegment.h"

uint8_t selectDisplay(uint8_t whichDisp)
{
    switch(whichDisp)
    {
        case 1:
            SEL_DISPLAY_DDR = ((SEL_DISPLAY_DDR & MASK_PORTC) | FIRST_7SEG);
            break;
        case 2:
            SEL_DISPLAY_DDR = ((SEL_DISPLAY_DDR & MASK_PORTC) | SECOND_7SEG);
            break;
        case 3:
            SEL_DISPLAY_DDR = ((SEL_DISPLAY_DDR & MASK_PORTC) | THIRD_7SEG);
            break;
        case 4:
            SEL_DISPLAY_DDR = ((SEL_DISPLAY_DDR & MASK_PORTC) | FOURTH_7SEG);
            break;            
    }
    return 0;
}

uint8_t selectNumber(uint8_t whichNumber)
{
    SEL_NUMBER_DDR |= 0b11111111; // Almost all 7-seg pins are connected to SEL_NUMBER_PORT, so we
                        // must set SEL_NUMBER_PORT as output.
    switch(whichNumber)
    {
        case 0:
            SEL_NUMBER_PORT = ZERO_7SEG; // mask is not necessary, because all SEL_NUMBER_PORT is
                               // for 7seg display purposes.
            break;
        case 1:
            SEL_NUMBER_PORT = ONE_7SEG;
            break;
        case 2:
            SEL_NUMBER_PORT = TWO_7SEG;
            break;
        case 3:
            SEL_NUMBER_PORT = THREE_7SEG;
            break;
        case 4:
            SEL_NUMBER_PORT = FOUR_7SEG;
            break;
        case 5:
            SEL_NUMBER_PORT = FIVE_7SEG;
            break;
        case 6:
            SEL_NUMBER_PORT = SIX_7SEG;
            break;
        case 7:
            SEL_NUMBER_PORT = SEVEN_7SEG;
            break;
        case 8:
            SEL_NUMBER_PORT = EIGHT_7SEG;
            break;
        case 9:
            SEL_NUMBER_PORT = NINE_7SEG;
            break;
        default:
            SEL_NUMBER_PORT = MINUS_SIGN;
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