#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRC |= (1<<PC4); // PC4 as output
    PORTC &= ~(1<<PC4); // Pull internally PC4 to gnd
    
    DDRD |= (1<<PD5)|(1<<PD6); // PD5, PD6 as output
    PORTD |= (1<<PD5)|(1<<PD6); // Pull internally PD5 and PD6 to vcc
    
    while(1);
    
    return 0;
}
