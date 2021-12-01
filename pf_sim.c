#include <msp430.h>
#include "pf_sim.h"

unsigned int volatile random_num;	// read temperature value

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

void RTC_start()
{
    rtc_init();
    P3DIR =0xFF;
    random_num=RTCPS;
}

unsigned int random_number() {
    random_num=RTCPS;
    return random_num;
}
