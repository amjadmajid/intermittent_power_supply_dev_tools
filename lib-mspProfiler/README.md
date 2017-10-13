# CP: is a MSP430 Code Profiler 

**CP** is little library that uses timer_b to count the number of MCU cycles.  


## Usage: 
A user must build the library and link its project to it.  
In order to count the unmber of cycles a user must: 

1. Call the `cp_init()` function to initialize the the peripherals (timer_b and uart)
2. Before the section of the code that needs to be measured a user   calls `cp_reset()` to reset the timer value 
3. Directly after the section of the code a user calls `cp_getRes()` to get the value or `cp_sendRes("str_id \0")` to send it over the uart


## Settings:
Leaving the system clock to its default configuration.  
The **CP** library uses [uart_debugger library](https://github.com/amjadmajid/uart-debugger-repo) to send data to the computer  
This library is tested on `MSP-EXP430FR5969` launchPad.  


## Example:
```
int main(void)
{
	...
	cp_init();  			// initialize the counter 
	...

	cp_reset() ;			// Start the measurement 
	__delay_cycles(50000);
	val = cp_getRes();     // this function returns the timer value 
	...

	cp_reset() ;			// Start the measurement 
	__delay_cycles(50000);
	cp_sendRes("func_id \0");     // this function sends timer value with func_id to the console
  }
```

