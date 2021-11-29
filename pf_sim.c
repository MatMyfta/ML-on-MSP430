#include <msp430.h>
#include "pf_sim.h"

#define MIN_PF 100		//minimum power failure count

int timer_count = 200;	//initial power failure count
unsigned int volatile random_num;	// read temperature value
int mod_rand;

static void reset() {
	PMMCTL0 = 0x0008;	// power-on reset (POR)
}

static void rtc_init() {
    PJSEL0 = BIT4 | BIT5;                   	// Initialize LFXT pins
    CSCTL0_H = CSKEY_H;                     	// Unlock CS registers
        CSCTL4 &= ~LFXTOFF;                     // Enable LFXT
        do {
          CSCTL5 &= ~LFXTOFFG;                  // Clear LFXT fault flag
          SFRIFG1 &= ~OFIFG;
        } while (SFRIFG1 & OFIFG);              // Test oscillator fault flag
        CSCTL0_H = 0;                           // Lock CS registers

        // Setup RTC Timer
        RTCCTL0_H = RTCKEY_H;                   // Unlock RTC

        RTCCTL0_L = RTCTEVIE_L;                 // RTC event interrupt enable
        RTCCTL13 = RTCSSEL_2 | RTCTEV_0 | RTCHOLD; // Counter Mode, RTC1PS, 8-bit ovf
        RTCPS0CTL = RT0PSDIV1;                  // ACLK, /8
        RTCPS1CTL = RT1SSEL1 | RT1PSDIV0 | RT1PSDIV1; // out from RT0PS, /16

        RTCCTL13 &= ~(RTCHOLD);                 // Start RTC
}

static void Timer_A0_set(){
    TA0CCR0 = timer_count;			//max 65535
    TA0CTL = TASSEL__ACLK + MC_1;	//set the max period for 16bit timer operation
    TA0CCTL0 = CCIE;				//enable compare reg 0
    _BIS_SR( GIE);					//ENABLE GLOBAL INTERRRUPTS
}

void PF_sim_start()
{
    rtc_init();
    P3DIR =0xFF;
    Timer_A0_set();
}

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
	random_num=RTCPS;   // 16-bits register(RTC) to generate random number
	mod_rand= random_num % 101; // map 16-bit to 0-100 range
	random_num = MIN_PF + mod_rand*8; // 100 to 900 random number
	timer_count=random_num;
	P3OUT^=0x02;
	reset();
}
