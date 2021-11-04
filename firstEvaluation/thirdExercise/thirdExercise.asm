.include "./m328Pdef.inc" ; directive for pin and register definitions

; define symbols for first 7seg display
.EQU    SEG_ZERO1 = 0x08 ; 0x08 = 0b00001000
.EQU    SEG_ONE1 = 0x7B ; 0b01111011
.EQU    SEG_TWO1 = 0x34 ; 0b00110100
.EQU    SEG_THREE1 = 0x31 ; 0b00110001
.EQU    SEG_FOUR1 = 0x63 ; 0b01100011
.EQU    SEG_FIVE1 = 0x81 ; 0b10000001
.EQU    SEG_SIX1 = 0xA0 ; 0b10100000
.EQU    SEG_SEVEN1 = 0x3B ; 0b00111011
.EQU    SEG_EIGHT1 = 0x00 ; 0b00000000
.EQU    SEG_NINE1 = 0x01 ; 0b00000001
; define symbols for second 7seg display
.EQU    SEG_ZERO2 = 0x10 ; 0x10 = 0b00010000
.EQU    SEG_ONE2 = 0xDD ; 0b11011101
.EQU    SEG_TWO2 = 0x29 ; 0b00101001
.EQU    SEG_THREE2 = 0x89 ; 0b10001001
.EQU    SEG_FOUR2 = 0xC5 ; 0b11000101
.EQU    SEG_FIVE2 = 0x83 ; 0b10000011
.EQU    SEG_SIX2 = 0x03 ; 0b00000011
.EQU    SEG_SEVEN2 = 0xD9 ; 0b11011001
.EQU    SEG_EIGHT2 = 0x00 ; 0b00000000
.EQU    SEG_NINE2 = 0xC1 ; 0b11000001
.EQU	numB = 10 ; number of bytes in array, from 0 to 9, so 10 bytes
.DEF    temp = r16 ; define temp register
.DEF	tmp	= r21 ; define temp register
.DEF	loopCt	= r22 ; define loop count register
.DEF    delayLoopVar1 = r18 ; used for delay loop
.DEF    delayLoopVar2 = r17 ; used for delay loop

.DSEG ; data segment DSEG directive means that all next entries define variables
.ORG    SRAM_START ; directive .org is used to set the location of .dseg to 
                   ; SRAM_START. SRAM_START indicates an address in memory

initializePointer:   
    .BYTE   numB ; allocate bytes in SRAM for array. Directive BYTE can be only
                 ; be used in the DSEG area
    .CSEG ; CSEG directive means that all next entries refer to the program 
          ; memory (FLASH memory)
    .ORG	0x00
    ldi	    XL, LOW(initializePointer) ; initialize X pointer
    ldi	    XH, HIGH(initializePointer) ; to SRAM array address
    ldi	    ZL, LOW(2*numbers7seg1)	; initialize Z pointer to program mem array
    ldi	    ZH, HIGH(2*numbers7seg1) ; address
    ldi	    loopCt, numB ; initialize loop count to number of bytes
init:
    ldi     r20, 0xFF ; set PORTD as output where is 7seg display1
    out     DDRD, r20
    out     DDRB, r20 ; set PORTB as output where is 7seg display2
    ldi     r20, SEG_ZERO1
	out     PORTD, r20
    ldi     r20, SEG_NINE2   
	out     PORTB, r20

	ldi     temp, 0b11111000 ; set PC0, PC1, PC2 as input and rest of pins as
    out     DDRC, temp       ; output
    ldi     temp, 0xFF
    out     PORTC, temp ; pull all PORTC internally to logical 1
main:	     
    in      temp, PINC ; read the value from PORTC
    andi    temp, 0x07 ; 0x07 = 0b00000111 this will keep only MSB PC0, PC1, PC2
    cpi     temp, 0x05 ; 0x05 = 0b11111101 compare temp with 0x05. If PC1 = GND,          
    breq    nextValue ; then jump to nextValue label. breq = branch if equal
    
    in      temp, PINC
    andi    temp, 0x07
    cpi     temp, 0x06 ; 0b00000110, if PC0
    breq    previousValue
    
    cpi     XL, 0 ; if XL pointer is 0
    breq    onAccessBarrier ; there are some free places
    cpi     XL, 0x0A ; 0b00001010
    breq    offAccessBarrier ; no free parking spaces
    
    cpi     XL, 0x09 ;  if XL pointer is 9
    brlt    VorA ; brlt - branch if less than, not equal or less!
    cpi     XL, 0x09 ; 
    breq    E 
    rjmp    main    
VorA:
    cpi     XL, 0x06
    brlt    V
    breq    A
    rjmp    main 
V:
    ldi     temp, 0b11011111 ; pc5
    out     PORTC, temp
    rjmp    main 
A:
    ldi     temp, 0b11101111 ; pc4
    out     PORTC, temp
    rjmp    main 
E:
    ldi     temp, 0b11110111 ; pc3
    out     PORTC, temp
    rjmp    main
onAccessBarrier:
    ldi     temp, 0b11110111
    out     PORTC, temp
    rjmp    main 
offAccessBarrier:
    ldi     temp, 0b11101111
    out     PORTC, temp
    rjmp    main
nextValue:
    lpm	    tmp, Z+	; load program memory. Load constant from Z to tmp register
	out     PORTD, tmp ; set correct number on the 7seg display
	out     PORTB, tmp
	call    delay
	st	    X+, tmp	; store value to SRAM array
    rjmp    main
previousValue:
    subi    ZL, 1 ; substract, decrement lower part of Z register
    lpm	    tmp, Z ; load value from pmem array
	out     PORTD, tmp ; set correct number on the 7seg display
	out     PORTB, tmp
	call    delay
	st	    X+, tmp	; store value to SRAM array
    rjmp    main
; -------- delay function - about 1 sek -------- 
delay:    
    ldi     temp, 20
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
    ret ; return form subroutine   
; -------- defining constants in program memory -------- 
numbers7seg1:    
    .db     SEG_ZERO1, SEG_ONE1, SEG_TWO1, SEG_THREE1, SEG_FOUR1, SEG_FIVE1
    .db     SEG_SIX1, SEG_SEVEN1, SEG_EIGHT1, SEG_NINE1   
numbers7seg2:    
    .db     SEG_NINE2, SEG_EIGHT2, SEG_SEVEN2, SEG_SIX2, SEG_FIVE2, SEG_FOUR2
    .db     SEG_THREE2, SEG_TWO2, SEG_ONE2, SEG_ZERO2       
    
    
    
    
    
    
    
    
    
    
    
    
