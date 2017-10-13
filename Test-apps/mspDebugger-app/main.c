#include <msp430.h> 
#include <uart-debugger.h>

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    uart_init();

    unsigned var = 12121212;
    while(1)
    {
        uart_sendText("start \n\r", 8);
        uart_sendText("ק??\n\r", 5);
        uart_sendChar('c');
        uart_sendChar(0x68); // h
        uart_sendText("\n\r", 2);
        uart_sendHex16(var);
        uart_sendText("\n\r", 2);
        uart_sendHex8(0xAA);
        uart_sendHex8(0x00);
        uart_sendHex16(48815);
        uart_sendHex16(0x0000);
        uart_sendHex32(0xbbeeaaff);
        uart_sendText("\n\r", 2);
    }
	return 0;
}
