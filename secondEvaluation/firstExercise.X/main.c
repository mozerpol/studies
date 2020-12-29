#include "sevenSegment.h"
#include "pushButton.h"
#include "controlDCmotor.h"

volatile uint8_t display = 1;
volatile uint8_t unities = 0;
volatile uint8_t tens = 0;

int main(void)
{   
    _delay_ms(1000);
    init_TIMER2();
    init_TIMER0();
    sei();
        
    while(1)
    {
        if((detectButton() == 1) && (OCR2 < 249))
        {
            OCR2 += 25;
            unities += 1;
        }
        if((detectButton() == 2) && (OCR2 > 1))
        {
            OCR2 -= 25;
            tens += 1;
        }
		if (TIFR & (1 << OCF2))
		{
			TIFR = (1 << OCF2);
		} 
    }
    
    return 0;
}


ISR(TIMER0_OVF_vect)
{
    switch(display)
    {
        case 1:
            showNumber(display, unities);
            break;
        case 2:
            showNumber(display, tens);
            display = 0;
            break;
    }
    display++;
}




//	PORTB ^= (1 << PB1);	//Tutaj zmieniamy stan pinu, do ktorego podlaczona jest dioda, dzieki temu caly czas miga.
//  DDRB |= (1<<PB1);
//  PORTB |= (1<<PB1);



        
        /*
        if(detectButton() == 1)
        {
            motorVelocity += 25;
        }
        if(detectButton() == 2)
        {
            motorVelocity -= 25;
        }
        if(motorVelocity == 0)
        {
            
        }
        if(motorVelocity > 0)
        {
            // delete minus sign from 7seg
        } // else // show minus sign
         * */