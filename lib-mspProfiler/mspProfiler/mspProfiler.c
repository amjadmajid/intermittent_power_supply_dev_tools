#include "codeProfiler.h"

void cp_init(){
	uart_init();
	TB0CTL = TBSSEL__SMCLK | MC__CONTINOUS | TBCLR | TBIE;
}

uint32_t cp_getRes() {
    /*
     *  cp_getRes() returns the value of timer_b and the number of
     *  timer overflow and then resets it.
     */
	uint16_t currnt_timer = TB0R;
	uint32_t ovrflw = __overflow;     // number of timer overflows
	ovrflw <<=16;                     // shift the overflow to the upper bytes
	ovrflw |= currnt_timer;          // get the current timer
	ovrflw-=10;

	__overflow = 0;                 // reset the overflow counter
	TB0CTL |= TBCLR;                // reset the timer
	return currnt_timer;
}


void  cp_sendRes(char * resId)
{
    /*
     * cp_sendRes() expects a null terminating string
     * it send the current
     */

    // Halt timer_b
   unsigned int x =  TB0R;
   x -=15;

    uart_sendStr(resId);
    uart_sendHex16(__overflow);
    uart_sendHex16(x);
    uart_sendText("\n\r", 2);

    __overflow = 0;                 // reset the overflow counter
    TB0CTL |=  TBCLR;                // reset the timer
}

unsigned int __overflow = 0;   // This must  be non-volatile



// TimerB Interrupt Vector (TBIV) handler
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_B1_VECTOR))) TIMER0_B1_ISR (void)
#else
#error Compiler not supported!
#endif
{
  switch(__even_in_range(TB0IV, TB0IV_TBIFG))
  {
    case TB0IV_NONE:   break;               // No interrupt
    case TB0IV_TBCCR1: break;               // CCR1 not used
    case TB0IV_TBCCR2: break;               // CCR2 not used
    case TB0IV_TBCCR3: break;               // CCR3 not used
    case TB0IV_TBCCR4: break;               // CCR4 not used
    case TB0IV_TBCCR5: break;               // CCR5 not used
    case TB0IV_TBCCR6: break;               // CCR6 not used
    case TB0IV_TBIFG:                       // overflow
//      P1OUT ^= BIT0;
      __overflow++;
      break;
    default: break;
  }
}
