#include "pushButton.h"
#include"sevenSegment.h"

uint8_t detectButton()
{
    BUTTON_DDR &= ~(1<<FIRST_BUTTON)|
            (1<<SECOND_BUTTON)|
            (1<<THIRD_BUTTON)|
            (1<<FOURTH_BUTTON);
    
    BUTTON_PORT |= (1<<FIRST_BUTTON)|
            (1<<SECOND_BUTTON)|
            (1<<THIRD_BUTTON)|
            (1<<FOURTH_BUTTON);
    
    if(!(BUTTON_PIN & (1<<FIRST_BUTTON))) // If PB2 == 0
    {
        _delay_ms(150);
        if(!(BUTTON_PIN & (1<<FIRST_BUTTON))) // If PB2 == 0
        {
            return 1;
        }
    }

    if(!(BUTTON_PIN & (1<<SECOND_BUTTON)))
    {
        _delay_ms(150);
        if(!(BUTTON_PIN & (1<<SECOND_BUTTON)))
        {
            return 2;
        }
    }
    if(!(BUTTON_PIN & (1<<THIRD_BUTTON)))
    {
        _delay_ms(150);
        if(!(BUTTON_PIN & (1<<THIRD_BUTTON)))
        {
            return 3;
        }
    }
    
    if(!(BUTTON_PIN & (1<<FOURTH_BUTTON)))
    {
        _delay_ms(150);
        if(!(BUTTON_PIN & (1<<FOURTH_BUTTON)))
        {
            return 4;
        }
    }
    
    return 0;
}