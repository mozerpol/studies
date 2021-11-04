#include "adc.h"


void init_ADC(void)
{
	ADCSRA |= (1 << ADEN); // Turn on ADC
	ADCSRA |= (1 << ADPS2); // Sampling frequency should be internally clocked
                            // between 50 kHz and 200 kHz, but MCU is colecked
                            // at 1 Mhz, so we must divide frequency.
                            // ADPS2 = 16, so 1 MHz / 16 = 62 kHz.
	ADMUX |= (1 << REFS0); //AVCC with external capacitor at AREF pin.
    ADMUX |= (1 << MUX2)|(1 << MUX0); // Select channel ADC5 (pin PC5).
}