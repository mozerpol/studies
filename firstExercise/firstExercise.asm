.include "./m328Pdef.inc"

.EQU    SEG_ONE = 0b11111100
.EQU    SEG_TWO = 0b11110000
.EQU    SEG_THREE = 0b11000000

init:
    ldi     r16, 0b11111000 ; set PC0, PC1, PC2 as input and rest of pins as
    out     DDRC, r16       ; output
    
        ldi     r16, 0xFF ; set PORTD as output where is 7seg display
    out     DDRD, r16
    ldi     r16, 0xFF
    out     PORTD, r16 ; pull all PORTD internally to logical 1, so turn off LED
    
    
    ldi     r16, 0xFF
    out     PORTC, r16 ; pull all PORTC internally to logical 0
main:
    in      r16, PINC ; read the value from PORTC
    andi    r16, 0x07 ; 0x07 = 0b00000111 this will keep only MSB: PC0, PC1, PC2
    cpi     r16, 0x05 ; 0x05 = 0b00000101 compare R16 with 0x05. If PC1 = GND,
    breq    SW1       ; then jump to SW1 label
    
    in      r16, PINC
    andi    r16, 0x07
    cpi     r16, 0x06 ; 0b00000110
    breq    SW0
    
    in      r16, PINC
    andi    r16, 0x07
    cpi     r16, 0x03 ; 0b00000011
    breq    SW2
    
    in      r16, PINC
    andi    r16, 0x07
    cpi     r16, 0x01 ; 0b00000001
    breq    SWRESET 
       
    rjmp    main

SW0:
    ldi     r16, SEG_ONE ; Turn on all LEDs
    out     PORTD, r16 
    rjmp    main
SW1:
    ldi     r16, SEG_TWO ; Turn off all LEDs
    out     PORTD, r16 
    rjmp    main
SW2:
    ldi     r16, SEG_THREE ; Turn off all LEDs
    out     PORTD, r16 
    rjmp    main    
SWRESET:    
    ldi     r16, 0xFF ; Turn off all LEDs
    out     PORTD, r16 
  
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

    rjmp    main     
    
    
    
    
    
    
    
    
