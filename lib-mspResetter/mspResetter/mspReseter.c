#include <msp430.h> 
#include <mspDebugger.h>

#define __nv  __attribute__((section(".nv_vars")))

unsigned int __noise[] = {
 -2291 ,7608 ,1156 ,7020 ,4625 ,-2190 ,7938 ,2725 ,159 ,4252 ,3368 ,8358 ,6319 ,7882 ,295 ,3264 ,3326 ,4490 ,7154 ,-1577 ,2118 ,211 ,-1039 ,-1997 ,7253 ,5425 ,1931 ,-2337 ,9146 ,7652 ,6050 ,-968 ,1043 ,7585 ,3536 ,2146 ,748 ,2453 ,6936 ,-2487 ,9947 ,5275 ,3972 ,8214 ,5244 ,5034 ,9613 ,9296 ,9401 ,1831 ,9136 ,8985 ,1469 ,8384 ,8086 ,-1031 ,4742 ,5649 ,5615 ,340 ,-1052 ,2281 ,-1271 ,4676 ,3394 ,9122 ,-56 ,-2240 ,-835 ,7407 ,4951 ,3770 ,-410 ,5280 ,7242 ,4190 ,3645 ,-1029 ,-745 ,7050 ,3876 ,-1369 ,4695 ,3413 ,8057 ,9564 ,513 ,1978 ,1670 ,4852 ,9657 ,8497 ,6816 ,4901 ,8396 ,-2267 ,4580 ,-2288 ,5253 ,4884
};

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
   if(__noiseSel >= 100)
   {
       __noiseSel=0;
   }


  TA0CCTL0 = CCIE;                          // TACCR0 interrupt enabled
  TA0CCR0 =interval+__noise[__noiseSel];
  TA0CTL = TASSEL__SMCLK | MC__UP;   // SMCLK, continuous mode
//  uart_sendHex16(TA0CTL);
//  uart_sendStr("\n\r\0");
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
    __bic_SR_register(GIE);       // enable general interrupt
    __no_operation();
//    uart_sendStr("\n\r reset \n\r \0");

//    TA0CCTL0 &= ~CCIE | ~CCIFG; // clear the interrupt flag
//    TA0CTL |= TACLR;
//    uart_sendStr("*\n\r\0");
    PMMCTL0 = PMMPW|PMMSWBOR;
}
