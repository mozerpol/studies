# AVR_asm 
![AVRlogo](https://upload.wikimedia.org/wikipedia/commons/thumb/9/96/Avr_logo.svg/220px-Avr_logo.svg.png)

In this project, I put the basics of assembly language for 8-bit AVR, which helped me to do projects for passing the Microprocessadores e Microcontroladores course at ISEP in Porto.

Everything was done on the breadboard with the atmega328p, which works with an internal clock of 1 MHz. I used the USBasp programmer.
![draft2](https://user-images.githubusercontent.com/43972902/100476318-8b70c680-30e5-11eb-996c-b02799e8248e.png)

Good website to learn assembly language for 8-bit AVR [28.11.2020]: http://www.rjhcoding.com/avr-asm-tutorials.php

Datasheet for atmega328p in DIP package [28.11.2020]: https://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061B.pdf

AVR Instruction Set [28.11.2020]: http://ww1.microchip.com/downloads/en/devicedoc/atmel-0856-avr-instruction-set-manual.pdf

AVR Assembler [30.11.2020]: http://ww1.microchip.com/downloads/en/devicedoc/40001917a.pdf

### How to run
On the main repository page in README I wrote that I'm using MPLAB X IDE, because this IDE has built-in simulator for 8-bit AVR. But if I want compile assembly language code I'm using command in terminal: `avra fileName.asm`, where: <br/>
`avra` is Atmel AVR Assembler, you can find it in internet, e.g. [here](https://sourceforge.net/p/avra/wiki/Home/). After command `avra fileName.asm`, `avra` should generate three files:
1. fileName.cof
2. firstExercise.eep.hex
3. firstExercise.obj

If we want upload hex file to mcu we can use command: `avrdude -c usbasp -p m328p -u -U flash:w:fileName.hex`. <br/>
`AVRDUDE` is software for programming Atmel AVR Microcontrollers. [Website of this project](http://savannah.nongnu.org/projects/avrdude). Ok, but what does mean these arguments?
1. *-c* - specify programmer type, in my case it's *usbasp*.
2. *-p m328p* - AVR device, in this case I'm using mega328p, for mega8p will be *-p m8*.
3. *-u* - disable safemode, it's default option, it's necessary if we are changing fusebits.
4. *-U* - remember, there is difference between **-u** and **-U**. Ok, but capital letter *-U* means exactly `-U <memtype>:r|w|v:<filename>[:format]:`. It's the most important command. Its the one that actually does the programming. The `memtype` is either flash or eeprom (or hfuse, lfuse or efuse for the chip configuration fuses, but we aren't going to mess with those). the `r|w|v` means you can use `r` (read) `w` (write) or `v` (verify) as the command. The `filename` is, the file that you want to write to or read from. and `:format` means theres an optional format flag. We will always be using [Intel Hex](https://en.wikipedia.org/wiki/Intel_HEX) format. So, for example. If you wanted to write the file *test.hex* to the flash memory, you would use `-U flash:w:test.hex`. If you wanted to read the eeprom memory into the file *eedump.hex* you would use `-U eeprom:r:eedump.hex`. If you need more info about *AVRDUDE* arguments, just write `avrdude` into terminal and press *enter*.
