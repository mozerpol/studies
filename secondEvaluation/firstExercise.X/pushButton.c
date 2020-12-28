#include "pushButton.h"

uint8_t detectButton()
{
    DDRB &= ~(1<<PB2)|(1<<PB3)|(1<<PB4)|(1<<PB5);
    PORTB |= (1<<PB2)|(1<<PB3)|(1<<PB4)|(1<<PB5);
    
    if(!(PINB & (1<<PB5))) // If PB5 == 0
    {
        _delay_ms(300);
        if(!(PINB & (1<<PB5))) // If PB5 == 0
        {
            displayNumber(1,0);
            return (1); // Exit from If
        }
    }
}