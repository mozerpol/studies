.include "./m328Pdef.inc" ; directive for pin and register definitions

init:
    ldi     r16, 0b11111110 ; set PC0 as input and rest of pins as output
    out     DDRC, r16
    
    ldi     r16, 0xFF
    out     PORTC, r16 ; pull all PORTC internally to logical 1
main:
    in      r16, PINC ; read the value from PORTC
    andi    r16, 0x07 ; 0x07 = 0b00000001 this will keep only MSB: PC0, PC1, PC2
    cpi     r16, 0x06 ; 0x06 = 0b00000110 compare R16 with 0x05. If PC1 = GND,
                      ; then jump to SW0 label
    breq    SW0   
    rjmp    main
    
SW0:
    call    delay
    ldi     r16, 0 ; Turn on all LEDs
    out     PORTC, r16 
    rjmp    main

delay:    
    ldi     r16, 16
    ldi     r18, 255
    loop_2:
        ldi     R17, 100
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
    
    
    
    
    
    
