#include "pushButton.h"
#include"sevenSegment.h"

uint8_t detectButton()
{
    DDRB &= ~(1<<FIRST_BUTTON)|
            (1<<SECOND_BUTTON)|
            (1<<THIRD_BUTTON)|
            (1<<FOURTH_BUTTON);
    
    PORTB |= (1<<FIRST_BUTTON)|
            (1<<SECOND_BUTTON)|
            (1<<THIRD_BUTTON)|
            (1<<FOURTH_BUTTON);

    if(!(PINB & (1<<FOURTH_BUTTON))) // If PB5 == 0
    {
        _delay_ms(300);
        if(!(PINB & (1<<FOURTH_BUTTON))) // If PB5 == 0
        {
            displayNumber(1,1);
            return (1);
        }
    }
    if(!(PINB & (1<<THIRD_BUTTON)))
    {
        _delay_ms(300);
        if(!(PINB & (1<<THIRD_BUTTON)))
        {
            displayNumber(2,2);
            return (1);
        }
    }
    if(!(PINB & (1<<SECOND_BUTTON)))
    {
        _delay_ms(300);
        if(!(PINB & (1<<SECOND_BUTTON)))
        {
            displayNumber(3,3);
            return (1);
        }
    }
    if(!(PINB & (1<<FIRST_BUTTON)))
    {
        _delay_ms(300);
        if(!(PINB & (1<<FIRST_BUTTON)))
        {
            displayNumber(4,4);
            return (1);
        }
    }
}

    
    // DDRB |= (1<<PB1);
    // PORTB |= (1<<PB1);