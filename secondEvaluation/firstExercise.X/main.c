#include "sevenSegment.h"
#include "pushButton.h"

int main(void)
{
    for(int j = 1; j <= 4; j++)
    {
        for(int i = 0; i <= 9; i++)
        {
            displayNumber(j, i);
            _delay_ms(250);
        }
    }
    
    while(1);
    
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