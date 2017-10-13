#include "msp430.h"
#include "codeProfiler.h"

unsigned int x1 = 0;
unsigned int x2 = 0;


int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;
  PM5CTL0 &= ~LOCKLPM5;
  cp_init();
  __enable_interrupt();

  while(1){

	  cp_reset() ;
//	  __delay_cycles(50000);
	  cp_sendRes("1 \0");
	  __no_operation();


	  cp_reset() ;
	  __delay_cycles(50000);
	  __delay_cycles(50000);
	  cp_sendRes("2 \0");

	  __no_operation();
  }


}
