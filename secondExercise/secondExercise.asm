.include "./m328Pdef.inc"

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
    petla_3:
        ldi     R16, 20   
    petla_2:
        ldi     R18, 12
    petla_1:
        dec     R18
        brne    petla_1
        dec     R17
        brne    petla_2       
        dec     R19
        brne    petla_3    
    ret  
    
    
    
    
    
    
