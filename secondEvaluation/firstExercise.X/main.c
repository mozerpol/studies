#include "sevenSegment.h"
#include "pushButton.h"
#include "controlDCmotor.h"

volatile uint8_t display = 1;
volatile uint8_t unities[5] = {0, 5, 0, 5, 9};
volatile uint8_t tens[5] = {0, 2, 5, 7, 9}; 
const uint8_t *unitiesPointer = unities;
const uint8_t *tensPointer = &tens[0]; // The same method as above
volatile uint8_t minusStatusFlag = 0;

int main(void)
{   
    _delay_ms(250);
    init_TIMER2();
    init_TIMER0();
    init_MOTOR();
    sei();
        
    while(1)
    {
        if((detectButton() == 1) && (MOTOR_VELOCITY != 100))
        {
            MOTOR_VELOCITY += 25;
            unitiesPointer++;
            tensPointer++;
        }
        if((detectButton() == 2) && (MOTOR_VELOCITY != 0))
        {
            MOTOR_VELOCITY -= 25;
            unitiesPointer--;
            tensPointer--;
        }
        if((detectButton() == 3) && (MOTOR_VELOCITY == 0))
        {
            minusStatusFlag ^= 1;
        }
		if(TIFR & (1 << OCF2) && (MOTOR_VELOCITY != 0) )
		{
			TIFR = (1 << OCF2);
            PORTB ^= (1 << PB1);
		} 
    }
    
    return 0;
}

ISR(TIMER0_OVF_vect)
{
    switch(display)
    {
        case 1:
            showNumber(display, *unitiesPointer);
            break;
        case 2:
            showNumber(display, *tensPointer);
            break;
        case 10:
            if(minusStatusFlag) showNumber(3, 10);
            display = 0;
            break; 
    }
    display++;
}




//	PORTB ^= (1 << PB1);	//Tutaj zmieniamy stan pinu, do ktorego podlaczona jest dioda, dzieki temu caly czas miga.
//  DDRB |= (1<<PB1);
//  PORTB |= (1<<PB1);



        
