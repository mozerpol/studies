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

