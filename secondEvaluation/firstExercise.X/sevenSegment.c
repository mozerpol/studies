#include"sevenSegment.h"

uint8_t selectDisplay(uint8_t whichDisp)
{
    switch(whichDisp)
    {
        case 1:
            DDRC = ((DDRC & MASK_PORTC) | FIRST_7SEG);
            break;
        case 2:
            DDRC = ((DDRC & MASK_PORTC) | SECOND_7SEG);
            break;
        case 3:
            DDRC = ((DDRC & MASK_PORTC) | THIRD_7SEG);
            break;
        case 4:
            DDRC = ((DDRC & MASK_PORTC) | FOURTH_7SEG);
            break;            
    }
    return 0;
}

uint8_t selectNumber(uint8_t whichNumber)
{
    DDRB |= (1<<PB0); // 7-seg display is divided between PORTB and PORTD, one
                      // pin is connected to PB0, so we must set PB0 as output.
    DDRD |= 0b11111111; // Almost all 7-seg pins are connected to PORTD, so we
                        // must set PORTD as output.
    switch(whichNumber)
    {
        case 0: // number 0 is some pins from PORTD and one pin from PORTB
            PORTD = ZERO_7SEG;
            PORTB = (1<<PB0);
            break;
        case 1:
            PORTB = (0<<PB0);
            PORTD = ONE_7SEG;
            break;
        case 2:
            PORTD = TWO_7SEG;
            break;
        case 3:
            PORTD = THREE_7SEG;
            break;
        case 4:
            PORTD = FOUR_7SEG;
            PORTB = (1<<PB0);
            break;
        case 5:
            PORTD = FIVE_7SEG;
            PORTB = (1<<PB0);
            break;
        case 6:
            PORTD = SIX_7SEG;
            PORTB = (1<<PB0);
            break;
        case 7:
            PORTD = SEVEN_7SEG;
            break;
        case 8:
            PORTD = EIGHT_7SEG;
            PORTB = (1<<PB0);
            break;
        case 9:
            PORTD = NINE_7SEG;
            PORTB = (1<<PB0);
            break;
    }
    return 0;
}

/// Function for more convenience
uint8_t displayNumber(uint8_t whichDisp, uint8_t whichNumber)
{
    TIMER0_init();
    selectDisplay(whichDisp);
    selectNumber(whichNumber);
    return 0;
}

void TIMER0_init(void) //ustawienie dla 8-bit Timer/Counter0 with PWM
{
	TCCR2 |= (1<<WGM21);	//wlaczajac ten bit uzywamy trybu CTC (Clear Timer on Compare Match ? czyszczenie licznika przy osi?gni?ciu zadanej
							//warto?ci) licznik samodzielnie wraca do warto?ci pocz?tkowej, gdy tylko osi?gnie warto?? zapisan? w rejestrze OCR0
	TCCR2 |= (1<<CS22);		// 1 mhz / 64

	TCNT2 = 0;				//to jest bit, w ktorym zapisywana jest dana licznika, czyli jak sobie procek liczy do 'ilustam' to tutaj jest zapisywana
							//aktualna wartosc
	OCR2 = 255;				//to jest to 'ilestam', do tej wartosci zlicza procek.
    TIMSK |= (1<<OCIE2); // wlacz przerwanie kiedy doliczy do konca
}

volatile uint8_t idx = 0;

ISR(TIMER2_COMP_vect)
{
    idx++;
    if(idx == 3) 
    {   
        idx = 0;
    } 
}