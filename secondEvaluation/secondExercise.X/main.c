#include "sevenSegment.h"
#include "pushButton.h"
#include "controlDCmotor.h"
#include "adc.h"

volatile uint8_t display = 1; // Var for changing displays in interrupt handler
volatile uint8_t unities[5] = {0, 5, 0, 5, 9}; // Unities part
volatile uint8_t tens[5] = {0, 2, 5, 7, 9}; // Tens part displayed on display
volatile const uint8_t *unitiesPointer = unities; // Pointer for first element
volatile const uint8_t *tensPointer = &tens[0]; // The same method as above
volatile uint8_t minusStatusFlag = 0; // If minusStatusFlag=1 turn on minus sign

int main(void)
{   
    _delay_ms(200); // Delay for my convenience
    init_Buttons(); // Init ports
    init_MOTOR(); // Init ports
    init_TIMER2(); // For motor
    init_TIMER0(); // For multiplexing displays

    sei();
        
    while(1)
    {
        // If pressed first button and MOTOR_VELOCITY is not equal 100
        if((detectButton() == 1) && (MOTOR_VELOCITY != 100))
        {
            MOTOR_VELOCITY += 25; // Increase OCR2 reg, speed is faster
            unitiesPointer++; // Move pointer to the next value and thanks to
                              // this 7seg will show higher value
            tensPointer++;
        }
        if((detectButton() == 2) && (MOTOR_VELOCITY != 0))
        {
            MOTOR_VELOCITY -= 25; // Decrease speed
            unitiesPointer--;
            tensPointer--;
        }
        // If 7seg show value 00, can turn direction
        if((detectButton() == 3) && (MOTOR_VELOCITY == 0))
        {
            minusStatusFlag ^= 1; // Turn on or off turn direction
        }
        // If button has been pressed then turn off our engine
        if(detectButton() == 4)
        {
            PORTB = (0 << PB1); // Our output
            MOTOR_VELOCITY = 0;
            unitiesPointer = unities; // Go back to the first value, thanks to
                                      // this display will show 00 value
            tensPointer = tens;
        }
        // TIFR - interrupt flag register. If the timer counts to OCR0 it'll set
        // flag in TIFR which must be reset to count again. The flag is called
        // OCF0: Output Compare Flag 0.
		if(TIFR & (1 << OCF2) && (MOTOR_VELOCITY != 0) )
		{
			TIFR = (1 << OCF2);
            PORTB ^= (1 << PB1); // Our output. Every time when the counter
                                 // counts to OCR0 and set flag in TIFR register
                                 // then change state.
		}
    }
    
    return 0;
}

ISR(TIMER0_OVF_vect) // Interrupt handler for multiplexing 7seg displays
{
    switch(display)
    {
        case 1: // first display
            showNumber(display, *unitiesPointer);
            break;
        case 2: // second display
            showNumber(display, *tensPointer);
            break;
        case 10: // 10 value, because 7seg inertia. Should be "case 3:", but
                 // 7seg is not ideal. Thanks to '10' 7seg works properly
            if(minusStatusFlag) showNumber(3, 11); // 11 value means show minus
                                                   // sign
            display = 0;
            break; 
    }
    display++; // Change to next display
}