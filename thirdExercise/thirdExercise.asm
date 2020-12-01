.include "./m328Pdef.inc" ; directive for pin and register definitions

.EQU    SEG_ZERO = 0x08 ; 0x08 = 0b00001000
.EQU    SEG_ONE = 0x7B ; 0x7B = 0b01111011
.EQU    SEG_TWO = 0x34 ; 0x34 = 0b00110100
.EQU    SEG_THREE = 0x31 ; 0x31 = 0b00110001
.EQU    SEG_FOUR = 0x63 ; 0x63 = 0b01100011
.EQU    SEG_FIVE = 0x81 ; 0x81 = 0b10000001
.EQU    SEG_SIX = 0xA0 ; 0xA0 = 0b10100000
.EQU    SEG_SEVEN = 0x3B ; 0x3B = 0b00111011
.EQU    SEG_EIGHT = 0x00 ; 0x00 = 0b00000000
.EQU    SEG_NINE = 0x01 ; 0x01 = 0b00000001

.EQU	numB = 10 ; number of bytes in array
.DEF	tmp	= r21 ; define temp register
.DEF	loopCt	= r22 ; define loop count register
.DSEG
.ORG    SRAM_START

sArr:   
    .BYTE   numB ; allocate bytes in SRAM for array
    .CSEG
    .ORG	0x00
    ldi	    XL, LOW(sArr)		; initialize X pointer
    ldi	    XH, HIGH(sArr)		; to SRAM array address

    ldi	    ZL, LOW(2*numbers7seg)		; initialize Z pointer
    ldi	    ZH, HIGH(2*numbers7seg)		; to pmem array address

    ldi	    loopCt, numB		; initialize loop count to number of bytes

init:
    ldi     r20, 0xff ; set PORTD as output where is 7seg display
    out     DDRD, r20
    ldi     r20, SEG_ZERO
	out     PORTD, r20
	
	ldi     r16, 0b11111000 ; set PC0, PC1, PC2 as input and rest of pins as
    out     DDRC, r16       ; output
    ldi     r16, 0xFF
    out     PORTC, r16 ; pull all PORTC internally to logical 1
	
arrLp:	     
    in      r16, PINC ; read the value from PORTC
    andi    r16, 0x07 ; 0x07 = 0b00000111 this will keep only MSB: PC0, PC1, PC2
    cpi     r16, 0x05 ; 0x05 = 0b11111101 compare R16 with 0x05. If PC1 = GND,          
    breq    nextValue ; then jump to increaseNumb label
    
    in      r16, PINC
    andi    r16, 0x07
    cpi     r16, 0x06 ; 0b00000110
    breq    previousValue
    
    cpi     +XL, 0x02 ; 0b00001001
    breq    onAccessBarrier
    cpi     XL, 0x05 ; 0b00001001
    breq    offAccessBarrier    
    
    rjmp    arrLp

onAccessBarrier:
    ldi     r16, 0b11011111
    out     PORTC, r16 ; pull all PORTC internally to logical 1
    rjmp    arrLp 
offAccessBarrier:
    ldi     r16, 0b11111111
    out     PORTC, r16 ; pull all PORTC internally to logical 1
    rjmp    arrLp 
nextValue:
    lpm	    tmp, Z+			; load value from pmem array
	out     PORTD, tmp
	call    delay
	st	    X+, tmp			; store value to SRAM array
    rjmp    arrLp

previousValue:
    subi    ZL, 1
    lpm	    tmp, Z			; load value from pmem array
	out     PORTD, tmp
	call    delay
	st	    X+, tmp			; store value to SRAM array
    rjmp    arrLp


 
; defining constants in program memory    
numbers7seg:    
    .db     SEG_ZERO, SEG_ONE, SEG_TWO, SEG_THREE, SEG_FOUR, SEG_FIVE
    .db     SEG_SIX, SEG_SEVEN, SEG_EIGHT, SEG_NINE
    
    
 ; -------- delay function - about 1 sek -------- 
delay:    
    ldi     r16, 20
    ldi     r18, 18
    loop_2:
        ldi     R17, 17
    loop_1:   
        dec     R18
        brne    loop_1
        dec     R17 ; decrement 8bit register. DEC instruction sets Z flag
                    ; in the status register 
        brne    loop_1 ; branch if not equal. Tests if the result of the 
                       ; previous operation was zero. If it was not, brne jump 
                       ; to the label given as an operand. If it was zero 
                       ; brne will continue to the next instruction.
        dec     R16
        brne    loop_2
    ret ; return form subroutine   
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
