.include "./m328Pdef.inc"

init:
    ldi     r16, 0b11111000 ; set PC0, PC1, PC2 as input and rest of pins as
                            ; output
    out     DDRC, r16
    
    ldi     r16, 0xFF
    out     PORTC, r16 ; pull internally to logical 1
main:
    in      r16, PINC
    andi    r16, 0x07 ; 0x07 = 0b00000111
    cpi     r16, 0x05 ; 0b11111110
    breq    SW1
    
    in      r16, PINC
    andi    r16, 0x07 ; 0x07 =  0b00000111
    cpi     r16, 0x06 ; 0b11111101
    breq    SW2
    
    rjmp    main
SW1:
    ldi     r16, 0xff
    out     PORTC, r16 
    rjmp    main
SW2:
    ldi     r16, 0
    out     PORTC, r16 
    rjmp    main    
    
    
    
    
    
    
    
    
    
    
