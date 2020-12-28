#include "sevenSegment.h"
#include "pushButton.h"
#include "controlDCmotor.h"


void TIMER2_init(void)
{
	TCCR2 |= (1<<WGM20); //Wybor fast PWM
	TCCR2 |= (1<<COM21); // Clear OC2 on Compare Match
	TCCR2 |= (1<<CS22);	// Prescaler: 64 

	TCNT2 = 0; // Actual value of counter
	OCR2 = 0; // Count up to this value
}

int main(void)
{   
    DDRB |= (1<<PB1);
    PORTB |= (1<<PB1);
    _delay_ms(1000);
    TIMER2_init();

    while(1)
    {
        if((detectButton() == 1) && (OCR2 < 249))
        {
            OCR2 += 25;
        }
        if((detectButton() == 2) && (OCR2 > 1))
        {
            OCR2 -= 25;
        }
        displayNumber(1,1);
        displayNumber(2,3);
       	//TIFR - rejestr flag przerwan (Interrupt Flag register). Jesli timer doliczy do OCR0 to ustawi flage w TIFR, ktora trzeba wyzerowac, aby
		//liczyl ponownie. Flaga nosi nazwe OCF0: Output Compare Flag 0.
		if (TIFR & (1 << OCF2))
		{
		//	PORTB ^= (1 << PB1);	//Tutaj zmieniamy stan pinu, do ktorego podlaczona jest dioda, dzieki temu caly czas miga.
			TIFR = (1 << OCF2);	//OCF0 mo?e zosta? wyzerowane po wpisaniu logicznej 1 do jej bitu, czyli obecna linijka w tym kodzie :]
		} 
    }
    
    return 0;
}


/*
for(int j = 1; j <= 4; j++)
{
    for(int i = 0; i <= 9; i++)
    {
        displayNumber(j, i);
        _delay_ms(500);
    }
}
 */


        
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