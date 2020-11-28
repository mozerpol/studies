How it works...

First thing to do in AVR with ports:
1. Define what to do with port - input or output
2. Set initial state for pin - 1 or 0
If the ports are not configured, they will be in a HIz state.

So...
Three registers are responsible for the state of ports in AVR: DDR, PORT and PIN. 
1. If DDR = 1, then all DDR ports will be output. 
2. If DDR = 0, then all DDR ports will be input.
3. If PORT = 1, then our input/output port (depending on DDR) will be pulled internally to logical 1. 
4. If PORT = 0, then our input/output port (depending on DDR) will be pulled internally to logical 0. 

If we want  configure port B as a output:

    ldi     r16, 0xFF
    out     DDRB, r16
    
The LDI instruction loading directly into the constant register can works only on the upper half of working registers, i.e. on registers r16 to r31. Arguments:
first - where we want load data, in this case we have r16.
second - what we want load, in this case we have 0xFF (the same in binary: 0b11111111).

The OUT instruction arguments:
first - destination, in this case we have DDRB.
second - from where we want to download the data, in this case we have r16.

Now we want set logic 1 on our 
    ldi     r16, 0xFF
    out     PORTB, r16

Instruction `out     PORTB, r16` means, that all DDRB are in high state. 

In first line I include m328Pdef.inc file using assembly directive. This file contains the register names from datasheet, thus we don't have to use hexidecimal names.
Next I used EQU directive. It assigns a value to a label, It's very similar to `#define` from C language. A label assigned to a value by the EQU directive is a constant and can not be changed or redefined. 
Next occurs the label `init`, where I conducted initialization of our MCU. 
```   
    ldi     r16, 0b11111000
    out     DDRC, r16
    ldi     r16, 0xFF
    out     PORTC, r1 
    out     DDRD, r16
    out     PORTD, r16
``` 
In this init I set PC0, PC1, PC2 as input and rest of pins as output on PORTC. PC0, PC1, PC2 is for switches, PC3, PC4 and PC5 is for LEDs. PORTD is using for 7segment display purposes. 
```
ldi     r16, 0b11111000
```
`ldi` - load the binary value 0b11111000 to r16 register.
```
out     DDRC, r16
```
`out` - stores data from register r16 to I/O Space (like Ports, Timers, Configuration Registers, etc.) in this case our I/O Space is DDRC register.
Next is `main` label, which works in a loop. In this loop the MCU waits for the button to be pressed. If the button has been pressed, it will jump to suitable label. 
```
in      r16, PINC
andi    r16, 0x07
cpi     r16, 0x05
breq    SW1
```
`in` - load data from I/O Space (like Ports, Timers, Configuration Registers, etc.) to register. In this case we're loading info from PINC to r16 register. It makes sense, I think... All 8-bit AVR family has only from 0 to 7 bit PORT, for example we have in mega328p PORTC, which has PC0, PC1, ..., PC7, in total eight pins. There is no 8-bit microcontroller, which has more than eight registers on a given port. So we can load eight bit value from PORTC to our eight bit r16 register. Each cell in the register can take two states: 0 or 1. 

`andi` - it's logical AND with immediate loading of the result to the register. The 0x07 value means binary 0b00000111. So if we use logical AND on PORTC with 0x07 value we will leave only the three last values. 

`cpi` - compare between register and a constant. In this case we're comparing 0x05 (it's 0b00000101) with r16 register, where we read the value a moment ago on PORTC. If register and constant are the same, set flag in Z register. 

`breq` - branch if equal.  Tests the Zero Flag (Z register), if is set jump to label, in this case jump to SW1 register. 












