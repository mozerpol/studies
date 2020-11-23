.include "./m328Pdef.inc" ; directive for pin and register definitions

.EQU    SEG_ONE = 0x7B ; 0b01111011
.EQU    SEG_TWO = 0x34 ; 0b00110100
.EQU    SEG_THREE = 0x31 ; 0b00110001
.EQU    SEG_FOUR = 0x63 ; 0b01100011
.EQU    SEG_FIVE = 0x81 ; 0b10000001
.EQU    SEG_SIX = 0x80 ; 0b10000000

init:
    ldi     r16, 0xFF ; set PORTD as output
    out     DDRD, r16
    
    ldi     r16, 0xFF
    out     PORTD, r16 ; pull all PORTC internally to logical 1, so turn off LED
main:
    call    increaseNumb
    call    decreaseNumb
    rjmp    main
    
SW0:
    rjmp    main

delay:    
    ldi     r16, 50
    ldi     r18, 18
    loop_2:
        ldi     R17, 17
    loop_1:   
        dec     R18
        brne    loop_1
        dec     R17 ; dec decrements 8bit register. DEC instruction sets Z flag
                    ; in the status register 
        brne    loop_1 ; branch if not equal. Tests if the result of the 
                       ; previous operation was zero. If it was not, brne jump 
                       ; to the label given as an operand. If it was zero 
                       ; brne will continue to the next instruction.
        dec     R16
        brne    loop_2
    ret  
    
increaseNumb:
    call    delay
    ldi     r16, SEG_ONE
    out     PORTD, r16
    call    delay
    ldi     r16, SEG_TWO
    out     PORTD, r16
    call    delay
    ldi     r16, SEG_THREE
    out     PORTD, r16
    call    delay
    ldi     r16, SEG_FOUR
    out     PORTD, r16
    call    delay
    ldi     r16, SEG_FIVE
    out     PORTD, r16
    call    delay
    ldi     r16, SEG_SIX
    out     PORTD, r16
ret  
decreaseNumb:
    call    delay
    ldi     r16, SEG_SIX
    out     PORTD, r16
    call    delay
    ldi     r16, SEG_FIVE
    out     PORTD, r16
    call    delay
    ldi     r16, SEG_FOUR
    out     PORTD, r16
    call    delay
    ldi     r16, SEG_THREE
    out     PORTD, r16
    call    delay
    ldi     r16, SEG_TWO
    out     PORTD, r16
    call    delay
    ldi     r16, SEG_ONE
    out     PORTD, r16
ret  
    
    
    
    
