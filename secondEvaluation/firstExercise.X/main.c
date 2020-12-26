#include <avr/io.h>
#include <util/delay.h>

int numb7segment(int number)
{
    switch(number)
    {
        case 0:
            DDRD |= 0b10111111;
            PORTD |= 0b10111111;
            DDRB |= (1<<PB0);
            PORTB |= (1<<PB0);
            break;
        case 1:
            DDRD |= 0b00100100;
            PORTD |= 0b00100100;
            break;
        case 2:
            DDRD |= 0b11011100;
            PORTD |= 0b11011100;
            break;
        case 3:
            DDRD |= 0b11110100;
            PORTD |= 0b11110100;
            break;
        case 4:
            DDRD |= 0b01100100;
            PORTD |= 0b01100100;
            DDRB |= (1<<PB0);
            PORTB |= (1<<PB0);
            break;
        case 5:
            DDRD |= 0b11110000;
            PORTD |= 0b11110000;
            DDRB |= (1<<PB0);
            PORTB |= (1<<PB0);
            break;
        case 6:
            DDRD |= 0b11111000;
            PORTD |= 0b11111000;
            DDRB |= (1<<PB0);
            PORTB |= (1<<PB0);
            break;
        case 7:
            DDRD |= 0b10100100;
            PORTD |= 0b10100100;
            break;
        case 8:
            DDRD |= 0b11111111;
            PORTD |= 0b11111111;
            DDRB |= (1<<PB0);
            PORTB |= (1<<PB0);
            break;
        case 9:
            DDRD |= 0b11110100;
            PORTD |= 0b11110100;
            DDRB |= (1<<PB0);
            PORTB |= (1<<PB0);
            break;
    }
    
    return 0;
}

int main(void)
{  
    DDRC |= (1<<PC4); // PC4 as output 
    PORTC &= ~(1<<PC4); // Pull internally PC4 to GND
    
    numb7segment(1);
    _delay_ms(700);
    numb7segment(2);
    _delay_ms(700);
    numb7segment(3);
    _delay_ms(700);

    
    while(1);
    
    return 0;
}
