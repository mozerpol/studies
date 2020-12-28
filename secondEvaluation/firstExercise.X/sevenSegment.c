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
                               // for 7seg diplay purposes.
            PORTB = (1<<PB0);
            break;
        case 1:
            PORTB = (0<<PB0);
            PORTD = ONE_7SEG;
            break;
        case 2:
            PORTB = (0<<PB0);
            PORTD = TWO_7SEG;
            break;
        case 3:
            PORTB = (0<<PB0);
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
            PORTB = (0<<PB0);
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
    
    selectNumber(whichNumber);
    selectDisplay(whichDisp);
    
    return 0;
}

// Interrupt for every 5 ms.
void TIMER2_init(void)
{
	TCCR2 |= (1<<WGM21);	// CTC (Clear Timer on Compare Match)
	TCCR2 |= (1<<CS22);		// Prescaler: 64 

	TCNT2 = 0;				// Actual value of counter
	OCR2 = 78;				// Count up to this value
    TIMSK |= (1<<OCIE2); // Turn on interrupts
}

ISR(TIMER2_COMP_vect);