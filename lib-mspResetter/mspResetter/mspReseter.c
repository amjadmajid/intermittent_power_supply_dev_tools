#include <msp430.h> 
#include <mspDebugger.h>

#define __nv  __attribute__((section(".nv_vars")))

 #define FIXED 1
// #define CAMEL
// #define TOWARD

#if FIXED || CAMEL
    __nv int __noise[] = {
    #include "powerPatterns.txt"
    };
#elif TOWARD
    __nv unsigned int __noise[] = {
    #include "powerPatterns.txt"
    };
#endif

__nv unsigned int __noiseSel = 0;

__nv unsigned __reset = 1;

void mr_reseter()
{
    if(__reset){
        __reset=0;
        PMMCTL0 = PMMPW|PMMSWBOR;
    }else{
        __reset=1;
    }
}

void mr_reseter_confirm()
{
    if(__reset){
        __reset=0;
        uart_sendStr("reset\n\r \0");
        PMMCTL0 = PMMPW|PMMSWBOR;
    }else{
        uart_sendStr("reset confirmed \n\r \0");
        __reset=1;
    }
}

void mr_auto_reseter(unsigned int interval)
{
  TA0CCTL0 = CCIE;                          // TACCR0 interrupt enabled
  TA0CCR0 = interval;
  TA0CTL = TASSEL__SMCLK | MC__CONTINOUS | TACLR;   // SMCLK, continuous mode

  __bis_SR_register(GIE);       // enable general interrupt
}

void mr_auto_rand_reseter(unsigned int interval)
{
   if(__noiseSel >= 200)
   {
       __noiseSel=0;
   }


  TA0CCTL0 = CCIE;                          // TACCR0 interrupt enabled
  TA0CCR0 =interval+__noise[__noiseSel];
  TA0CTL = TASSEL__SMCLK | MC__UP;   // SMCLK, continuous mode

  __noiseSel++;
  __bis_SR_register(GIE);       // enable general interrupt
}

// Timer0_A0 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) Timer0_A0_ISR (void)
#else
#error Compiler not supported!
#endif
{
    __bic_SR_register(GIE);       // disable general interrupt
    __no_operation();
    PMMCTL0 = PMMPW|PMMSWBOR;
}
