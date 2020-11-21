.include "./m328Pdef.inc"

ldi     r16, 0 
out     DDRC, r16 ; set DDRC as a input

ldi     r16, 0
out     PORTC, r16 ; pull internally PORTC to logic low.
