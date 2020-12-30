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
    
    if(!(PINB & (1<<FIRST_BUTTON))) // If PB2 == 0
    {
        _delay_ms(150);
        if(!(PINB & (1<<FIRST_BUTTON))) // If PB2 == 0
        {
            return 1;
        }
    }

    if(!(PINB & (1<<SECOND_BUTTON)))
    {
        _delay_ms(150);
        if(!(PINB & (1<<SECOND_BUTTON)))
        {
            return 2;
        }
    }
    if(!(PINB & (1<<THIRD_BUTTON)))
    {
        _delay_ms(150);
        if(!(PINB & (1<<THIRD_BUTTON)))
        {
            return 3;
        }
    }
    
    if(!(PINB & (1<<FOURTH_BUTTON)))
    {
        _delay_ms(150);
        if(!(PINB & (1<<FOURTH_BUTTON)))
        {
            return 4;
        }
    }
}