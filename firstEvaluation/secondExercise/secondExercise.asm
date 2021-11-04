.include "./m328Pdef.inc" ; directive for pin and register definitions

; define symbols for 7seg display
.EQU    SEG_ONE = 0x7B ; 0x7B = 0b01111011 
.EQU    SEG_TWO = 0x34 ; 0b00110100
.EQU    SEG_THREE = 0x31 ; 0b00110001
.EQU    SEG_FOUR = 0x63 ; 0b01100011
.EQU    SEG_FIVE = 0x81 ; 0b10000001
; define symbolic names for registers
.DEF    temp = r16 
.DEF    delayLoopVar1 = r18 ; used for delay loop
.DEF    delayLoopVar2 = r17 ; used for delay loop
.DEF    incStatFlag = r20 ; used in increaseAgainFlag routine
.DEF    decStatFlag = r21 ; used in decreaseAgainFlag routine

init:
    ldi     temp, 0xFF ; set PORTD as output where is 7seg display
    out     DDRD, temp
    out     PORTD, temp ; pull all PORTD internally to logical 1 so turn off LED
        
    ldi     temp, 0b11111000 ; set PC0, PC1, PC2 as input and rest of pins as       
    out     DDRC, temp       ; output
    ldi     temp, 0xFF
    out     PORTC, temp ; pull all PORTC internally to logical 1
main:
    in      temp, PINC ; read the value from PORTC
    andi    temp, 0x07 ; 0x07 = 0b00000111 this will keep only MSB PC0, PC1, PC2
    cpi     temp, 0x05 ; 0x05 = 0b11111101 compare temp with 0x05. If PC1 = GND,
                      ; then jump to increaseNumb label
    breq    increaseNumb ; branch if equal
    rjmp    main           
startCount:    
    call    increaseNumb ; count from 1 to 5, when the SW1 is pressed during 5,  
                         ; reverse countdown
    call    decreaseNumb ; count from 5 to 1, when the SW1 is pressed during 1,
                         ; reverse countdown
    rjmp    main
; -------- delay function - about 1 sek -------- 
delay:    
    ldi     temp, 50
    ldi     delayLoopVar1, 18
    loop_2:
        ldi     delayLoopVar2, 17
    loop_1:   
        dec     delayLoopVar1
        brne    loop_1
        dec     delayLoopVar2 ; decrement 8bit register. DEC instruction sets Z flag
                    ; in the status register 
        brne    loop_1 ; branch if not equal. Tests if the result of the 
                       ; previous operation was zero. If it was not, brne jump 
                       ; to the label given as an operand. If it was zero 
                       ; brne will continue to the next instruction.
        dec     temp
        brne    loop_2
    ret ; return form subroutine   
decreaseNumb:
    call    delay ; long call to a subroutine delay. Return address (to the 
                  ; instruction after call) will be stored onto the Stack.
    ldi     temp, SEG_FIVE
    out     PORTD, temp
    call    delay
    ldi     temp, SEG_FOUR
    out     PORTD, temp
    call    delay
    ldi     temp, SEG_THREE
    out     PORTD, temp
    call    delay
    ldi     temp, SEG_TWO
    out     PORTD, temp
    call    delay
    ldi     temp, SEG_ONE
    out     PORTD, temp
    call    delay 
    
    andi    decStatFlag, 0x00 ; reset register, which is used in decreaseAgainFlag.
                      ; Is against being pressed multiple times
    in      temp, PINC ; read the value from PORTC
    andi    temp, 0x07 ; mask for SW0 (PC0)
    cpi     temp, 0x06 ; 0b11111110, check if SW0 is pressed, compare with immedi
    breq    decreaseAgainFlag ; if SW0 is pressed go to decreaseAgainFlag
    rjmp    decreaseNumb        
increaseNumb:
    call    delay
    ldi     temp, SEG_ONE
    out     PORTD, temp
    call    delay
    ldi     temp, SEG_TWO
    out     PORTD, temp
    call    delay
    ldi     temp, SEG_THREE
    out     PORTD, temp
    call    delay
    ldi     temp, SEG_FOUR
    out     PORTD, temp
    call    delay
    ldi     temp, SEG_FIVE
    out     PORTD, temp
    call    delay  
    
    andi    incStatFlag, 0x00 ; reset register, which is used in increaseAgainFlag
                      ; Is against being pressed multiple times
    in      temp, PINC
    andi    temp, 0x07
    cpi     temp, 0x06 ; 0x06 = 0b11111110 (PC0)
    breq    increaseAgainFlag     
    rjmp    increaseNumb 
increaseAgainFlag:
    inc     incStatFlag ; increment status flag
    cpi     incStatFlag, 0x01
    breq    decreaseNumb
    ret ; return form subroutine
decreaseAgainFlag:
    inc     decStatFlag ; increment status flag
    cpi     decStatFlag, 0x01
    breq    increaseNumb
    ret  
    
    
    
    
    
    
    
    
    
    
