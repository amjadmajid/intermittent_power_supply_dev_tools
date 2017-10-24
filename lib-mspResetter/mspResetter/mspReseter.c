#include <msp430.h> 
#include <mspDebugger.h>

#define __nv  __attribute__((section(".nv_vars")))

unsigned int __noise[] = {
-404,4398,7037,4325,6103,9913,6811,6966,3114,1552,-399,3274,3,-24,2594,1170,4335,3004,4103,4173,3085,2318,6176,6881,4734,9397,8348,6603,5910,4148,2729,-12,1561,1988,3878,2066,1663,1007,3423,4346,1090,4595,7292,8414,4564,6429,9229,8701,4910,4426,3303,-336,4505,910,1756,2464,4685,-460,4506,2552,2806,6412,3469,4035,4560,7028,7478,7993,6295,1437,1348,1156,4456,442,1832,-324,331,1632,3131,4268,1873,3093,3291,6185,9704,7135,7065,4939,4290,2600,3790,2277,153,-438,1214,2079,4077,238,624,3102,2911,5092,5897,6238,6206,8104,4357,5935,3201,3880,2475,3582,1799,2423,2052,4021,2259,3044,1335,3166,-398,4333,6331,8675,7756,5049,6544,7612,2869,5952,1648,3548,2287,2580,3699,3195,-197,1951,1104,4403,2690,4064,6710,6955,5564,7461,9379,4404,4985,3153,2151,4065,3770,2204,4106,3531,786,1842,1228,3800,2362,2376,3022,7529,7989,8490,7201,5297,5867,1997,-97,4215,1782,4306,1296,3901,-73,-61,3884,2934,751,5245,6241,5004,5036,5543,9423,7286,3999,4881,773,4651,3353,2910,1935,4334,2857,629,4328,1530
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
