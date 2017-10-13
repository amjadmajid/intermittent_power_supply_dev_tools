# uart-debugger

### Overview:
	The uart-debugger is a basic library that can be used to send a debugging
	information over uart to a terminal window. It is developped for the
	MSP430FR5969 microcontroller. The uart-debugger uses 115200 baud rate and
	1 mega clock (the defaut microcontroller clock setting).

### Project integration: 
	The user must build the library and link his project to it. 

### uart-debugger API:
	* uart_init();
		this function initializes the UART module. 

	* uart_sendText("text", textLength);
		This function takes two arguments: 1) The text to be sent. and 2) the
		length of the text to be sent. 

	* uart_sendHex8();
		This function task an unsinged char number (uint8_t). 

	* uart_sendHex16();
		This function task an unsinged int number (uint16_t). 

	* uart_sendHex32();
		This function task an unsinged int number (uint32_t). 
