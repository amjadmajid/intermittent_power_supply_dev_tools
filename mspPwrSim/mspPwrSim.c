#include <msp430.h> 
#include "../mspDebugger/include/mspDebugger.h"

#define __nv  __attribute__((section(".nv_vars")))

#define off_factor 9
#define sleep_factor 40


__nv int __noise[] = {
#include "../mspPwrSim/pattern_on.txt"
};

__nv unsigned int __noiseSel = 0;
__nv unsigned int rstInterval = 0;
__nv unsigned int timecounter = 0;
__nv unsigned int power = 1;


void start_power_simulation(unsigned int interval)
{
   power = 1;
   timecounter=0;
   rstInterval = interval;

   if(__noiseSel >= 200)
   {
       __noiseSel=0;
   }

  TA0CCTL0 = CCIE;                          // TACCR0 interrupt enabled
  TA0CCR0 =rstInterval+__noise[__noiseSel]; // comment: noise is amplified as well by divider
  TA0CTL = TASSEL__SMCLK | MC__UP | ID_3;   // SMCLK, counting up, divider 8

  __noiseSel++;
  __bis_SR_register(GIE);       // enable general interrupt
}

void switch_timer_to_short(){
    //stop timer
    TA0CTL = MC__STOP;
    TA0R = 0;
    //read timecounter and set new timer
    TA0CCR0 = timecounter * ((rstInterval/sleep_factor) +1); // How short timer depends on time left in long timer
    timecounter = 0;
    //start timer
    TA0CTL = TASSEL__SMCLK | MC__UP | ID_3;
}

void switch_timer_to_long(){
    //stop timer
    TA0CTL = MC__STOP;
    //read timer and set new counter
    timecounter = (rstInterval-TA0R) / (rstInterval/sleep_factor); // How long timer depends on time left in short timer
    TA0R = 0;
    TA0CCR0 = rstInterval;
    //start timer
    TA0CTL = TASSEL__SMCLK | MC__UP | ID_3;
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
    if (power==1){
        if (timecounter==0) {
            P5IE &= ~BIT1;       // disable mic interrupt
            ADC12IER0 &= ~ADC12IE0;  // disable ADC interrupt
            power=0;  // turn node "off" in next if statement (same run of ISR)
            timecounter = off_factor;  // off-time = 9 x on-time
            P3OUT &= ~(BIT0|BIT1); // for logic analyzer
        }
        else {
            timecounter--;
            if(__noiseSel >= 200)  __noiseSel=0;

            TA0CCR0 = rstInterval+__noise[__noiseSel];
            __noiseSel++;
        }
    }

    if (power==0) {     // simulating the time that the node is off-line and harvesting energy

        if (timecounter != 0){
            timecounter--;

            if(__noiseSel >= 200)  __noiseSel=0;

            TA0CCR0 = rstInterval+__noise[__noiseSel];
            __noiseSel++;

            // sleep LPM0 -> SMCLOCK remains active if SMCLKOFF = 0 (if SMCLK in use)
            __bis_SR_register(LPM0_bits | GIE);
            __no_operation();
        }

        else    // reset
            {
            __no_operation();
            PMMCTL0 = PMMPW|PMMSWBOR;
            }
    }


}
