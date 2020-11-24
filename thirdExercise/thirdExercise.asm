.include "./m328Pdef.inc" ; directive for pin and register definitions

.EQU    SEG_ZERO = 0b00001000
.EQU    SEG_ONE = 0x7B ; 0x7B = 0b01111011
.EQU    SEG_TWO = 0x34 ; 0x34 = 0b00110100
.EQU    SEG_THREE = 0x31 ; 0x31 = 0b00110001
.EQU    SEG_FOUR = 0x63 ; 0x63 = 0b01100011
.EQU    SEG_FIVE = 0x81 ; 0x81 = 0b10000001
.EQU    SEG_SEVEN = 0b00111011
.EQU    SEG_EIGHT = 0b00000000
.EQU    SEG_NINE = 0b00000001

init:
    ldi     r16, 0xFF ; set PORTD as output where is 7seg display
    out     DDRD, r16
    ldi     r16, 0xFF
    out     PORTD, r16 ; pull all PORTD internally to logical 1, so turn off LED

main:
    ldi     r16, 0b00000001
    out     PORTD, r16
    rjmp    main
    
    
    
    
    
    
