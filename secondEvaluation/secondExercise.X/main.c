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
volatile uint8_t digitalOrAnalog = 11;

int main(void)
{   
    uint8_t operatingMode = 0;

    init_Buttons(); // Init ports
    init_MOTOR(); // Init ports
    init_TIMER2(); // For motor
    init_TIMER0(); // For multiplexing displays
    init_ADC(); // Init ADC module at PORT PC5
    _delay_ms(200); // Delay for my convenience
    
    sei();

    while(1)
    { 
        switch(operatingMode)
        {
            case 0: 
                digitalOrAnalog = 11;
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

                if(detectButton() == 4)
                {
                    blinkLED();
                    MOTOR_VELOCITY = 0;
                    unitiesPointer = &unities[0]; // Go back to the first value, thanks to
                                              // this display will show 00 value
                    tensPointer = &tens[0];
                    operatingMode = 1;
                }
                break;
                
            case 1: 
                digitalOrAnalog = 10;
                ADCSRA |= (1 << ADSC); // Start conversion, measure the voltage
                                       // and change it to binary code.
                // Wait until the conversion is over. The function checks if
                // the ADC module cleared the ADSC bit.
                loop_until_bit_is_clear(ADCSRA, ADSC); 
                
                if(ADC <= 102) 
                {
                    minusStatusFlag = 0;
                    MOTOR_VELOCITY = 0; // Increase OCR2 reg, speed is faster
                    // Move pointer to the next value and thanks to this 7seg
                    // will show higher value
                    unitiesPointer = &unities[0];
                    tensPointer = &tens[0];
                }
                if((ADC > 102) && (ADC <= 204))
                {
                    MOTOR_VELOCITY = 25;
                    unitiesPointer = &unities[1];
                    tensPointer = &tens[1]; 
                }
                if((ADC > 204) && (ADC <= 306))
                {
                    MOTOR_VELOCITY = 50;
                    unitiesPointer = &unities[2];
                    tensPointer = &tens[2]; 
                }
                if((ADC > 306) && (ADC <= 408))
                {
                    MOTOR_VELOCITY = 75;
                    unitiesPointer = &unities[3];
                    tensPointer = &tens[3];
                }
                if((ADC > 408) && (ADC <= 510))
                {
                    MOTOR_VELOCITY = 100;
                    unitiesPointer = &unities[4];
                    tensPointer = &tens[4];
                    minusStatusFlag = 0;
                }
                if((ADC > 510) && (ADC <= 612))
                {
                    MOTOR_VELOCITY = 0;
                    unitiesPointer = &unities[0];
                    tensPointer = &tens[0];
                    minusStatusFlag = 1;
                }
                if((ADC > 612) && (ADC <= 714))
                {
                    MOTOR_VELOCITY = 25;
                    unitiesPointer = &unities[1];
                    tensPointer = &tens[1];
                }
                if((ADC > 714) && (ADC <= 816))
                {
                    MOTOR_VELOCITY = 50;
                    unitiesPointer = &unities[2];
                    tensPointer = &tens[2];
                }
                if((ADC > 816) && (ADC <= 918))
                {
                    MOTOR_VELOCITY = 75; // Increase OCR2 reg, speed is faster
                    unitiesPointer = &unities[3]; // Move pointer to the next value and thanks to
                                      // this 7seg will show higher value
                    tensPointer = &tens[3];
                }
                if(ADC > 918)
                {
                    MOTOR_VELOCITY = 100; // Increase OCR2 reg, speed is faster
                    unitiesPointer = &unities[4]; // Move pointer to the next value and thanks to
                                      // this 7seg will show higher value
                    tensPointer = &tens[4];
                    minusStatusFlag = 1;
                }
                if(detectButton() == 4)
                {
                    blinkLED();
                    MOTOR_VELOCITY = 0;
                    unitiesPointer = &unities[0]; // Go back to the first value, thanks to
                                              // this display will show 00 value
                    tensPointer = &tens[0];
                    operatingMode = 0;
                }
                break;
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
        case 3: // fourth display
            showNumber(4, digitalOrAnalog);
            break;
        case 4: // 10 value, because 7seg inertia. Should be "case 3:", but
                 // 7seg is not ideal. Thanks to '10' 7seg works properly
            if(minusStatusFlag) showNumber(3, 12); // 11 value means show minus
                                                   // sign
            display = 0;
            break; 
    }
    display++; // Change to next display
}

/*
 
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
        //    PORTB ^= (1 << PB1); // Our output. Every time when the counter
                                 // counts to OCR0 and set flag in TIFR register
                                 // then change state.
		}
        
        ADCSRA |= (1 << ADSC); // Start conversion, measure the voltage and
                               // change it to binary code.
        loop_until_bit_is_clear(ADCSRA, ADSC); // Wait until the conversion is 
                                               // over. The function checks if
                                               // the ADC module cleared the
                                               // ADSC bit.
        if(ADC >= 512) 
        {
            PORTB |= (1 << PB1);
            minusStatusFlag = 0;
        }
        else 
        {
            PORTB &= ~(1 << PB1);
            minusStatusFlag = 1;
        }
    }
    
    return 0;
}
 
 
 */