#include <avr/io.h>
#include <util/delay.h>

int numb7segment(int number)
{
    DDRB |= (1<<PB0);
    DDRD |= 0b11111111;
    switch(number)
    {
        case 0:
            PORTD = 0b10111111;
            PORTB = (1<<PB0);
            break;
        case 1:
            PORTB = (0<<PB0);
            PORTD = 0b00100100;
            break;
        case 2:
            PORTD = 0b11011100;
            break;
        case 3:
            PORTD = 0b11110100;
            break;
        case 4:
            PORTD = 0b01100100;
            PORTB = (1<<PB0);
            break;
        case 5:
            PORTD = 0b11110000;
            PORTB = (1<<PB0);
            break;
        case 6:
            PORTD = 0b11111000;
            PORTB = (1<<PB0);
            break;
        case 7:
            PORTD = 0b10100100;
            break;
        case 8:
            PORTD = 0b11111111;
            PORTB = (1<<PB0);
            break;
        case 9:
            PORTD = 0b11110100;
            PORTB = (1<<PB0);
            break;
    }
    return 0;
}

int main(void)
{  
    DDRC |= (1<<PC4); // PC4 as output 
    PORTC &= ~(1<<PC4); // Pull internally PC4 to GND

    for(int i = 0; i <= 9; i++)
    {
        numb7segment(i);
        _delay_ms(1000);
    }
    while(1);
    
    return 0;
}
