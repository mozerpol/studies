#include "sevenSegment.h"
#include "pushButton.h"


uint8_t main(void)
{  
    for(int j = 1; j <= 4; j++)
    {
        for(int i = 0; i <= 9; i++)
        {
            displayNumber(j, i);
            _delay_ms(500);
        }
    }
    while(1);
    
    return 0;
}