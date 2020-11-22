.include "./m328Pdef.inc"

init:
    ldi     r16, 0b11111000 ; set PC0, PC1, PC2 as input and rest of pins as
                            ; output
    out     DDRC, r16
    
    ldi     r16, 0
    out     PORTC, r16 ; pull all PORTC internally to logical 0
main:
    in      r16, PINC ; read the value from PORTC
    andi    r16, 0x07 ; 0x07 = 0b00000111 this will keep only MSB: PC0, PC1, PC2
    cpi     r16, 0x05 ; 0x05 = 0b11111101 compare R16 with 0x05. If PC1 = GND,
                      ; then jump to SW1 label
    breq    SW1
    
    in      r16, PINC
    andi    r16, 0x07
    cpi     r16, 0x06 ; 0b11111110
    breq    SW0
    
    rjmp    main
SW1:
    ldi     r16, 0xFF ; Turn off all LEDs
    out     PORTC, r16 
    rjmp    main
SW0:
    ldi     r16, 0 ; Turn on all LEDs
    out     PORTC, r16 
    rjmp    main    
    
    
    
    
    
    
    
    
    
    
