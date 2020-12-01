.include "./m328Pdef.inc" ; directive for pin and register definitions

; define symbols on 7seg display
.EQU    SEG_ONE = 0b11111100
.EQU    SEG_TWO = 0b11110000
.EQU    SEG_THREE = 0b11000000
; define symbolic names for registers
.DEF    temp = r16 
.DEF    delayLoopVar1 = r18 ; used for delay loop
.DEF    delayLoopVar2 = r17 ; used for delay loop

init:
    ldi     temp, 0b11111000 ; set PC0, PC1, PC2 as input and rest of pins as
    out     DDRC, temp       ; output 
    ldi     temp, 0xFF ; pull all PORTC internally to logical 1, onnect to
    out     PORTC, temp ; internall resistor
    
    out     DDRD, temp ; set PORTD as output where is 7seg display
    out     PORTD, temp ; pull all PORTD internally to logical 1, so turn off LED
main:
    in      temp, PINC ; read the value from PORTC
    andi    temp, 0x07 ; 0x07 = 0b00000111 this will keep only MSB: PC0, PC1, PC2
    cpi     temp, 0x05 ; 0x05 = 0b00000101 compare temp with 0x05. If PC1 = GND,
    breq    SW1       ; then jump to SW1 label
    
    in      temp, PINC
    andi    temp, 0x07
    cpi     temp, 0x06 ; 0b00000110
    breq    SW0
    
    in      temp, PINC
    andi    temp, 0x07
    cpi     temp, 0x03 ; 0b00000011
    breq    SW2
    
    in      temp, PINC
    andi    temp, 0x07
    cpi     temp, 0x01 ; 0b00000001 If press at the same time SW1 and SW2 jump to
    breq    SWRESET 
       
    rjmp    main
SW0:
    ldi     temp, SEG_ONE ; Turn on D4, D5
    out     PORTD, temp 
    rjmp    main
SW1:
    ldi     temp, SEG_TWO ; Turn on D3, D4, D5, D6
    out     PORTD, temp 
    rjmp    main
SW2:
    ldi     temp, SEG_THREE ; Turn on D2, D3, D4, D5, D6, D7
    out     PORTD, temp 
    rjmp    main    
SWRESET:    
    ldi     temp, 0xFF ; Turn off all LEDs
    out     PORTD, temp 
; -------- delay function --------  
; MCU is too fast, without it will be mishmash with LEDs
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
    rjmp    main     
    
    
    
    
    
    
    
    
