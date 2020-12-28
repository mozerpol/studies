#include "sevenSegment.h"
#include "pushButton.h"

int main(void)
{
    displayNumber(1,0);
    while(1);
    
    return 0;
}

/*
uint8_t odbicie(void)
{
	if((PIND & (1<<PD6)) == 0)		//jesli(do pinu PD6 dochodzi stan logiczny 0 to: )
	{
		_delay_ms(1000);		//najpierw opoznienie 1 sek
		if((PIND & (1<<PD6)) == 0)	//Ponownie - jesli(do pinu PD6 dochodzi stan logiczny 0 to: )
		{
			_delay_ms(1000);	//opoznienie 1 sek
			return (1);		//wyjdz z ifow
		}
	}
return (0);
}
*/
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