.include "./m328Pdef.inc"

ldi     r16, 0xFF 
out     DDRC, r16 ; set DDRC as a output

ldi     r16, 0b00100000 
out     PORTC, r16 ; pull internally PC5 to logic high. The rest off the pins
; pull internally to logic low.  
