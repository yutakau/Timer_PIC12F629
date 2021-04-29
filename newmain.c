/*
 * File:   newmain.c
 * Author: yutaka usui 
 *
 * Created on 2021/04/29, 14:07
 */


// CONFIG
#pragma config FOSC = INTRCCLK  // Oscillator Selection bits (INTOSC oscillator: CLKOUT function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-Up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF      // GP3/MCLR pin function select (GP3/MCLR pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)

#include <xc.h>


#define TIMER_MIN 30
// Timer minute

void main(void) {
    unsigned char tcnt;
    unsigned int  tsec;  // 
    unsigned char endflag;

    TRISIO = 0;
    TMR1CS = 0;
    nT1SYNC = 0;
    TMR1ON = 1;

    tcnt = 0;
    tsec = 0;
    endflag = 0;

    GPIO2 = 1;
    
    while (endflag == 0) {
        if (TMR1IF == 1) {
            TMR1IF = 0; // Clear overflow flag
            TMR1ON = 0; // Timer1 off
            TMR1H = 0x3C; // set 50ms : (65535-50000)
            TMR1L = 0xB0; //
            TMR1ON = 1; // timer1 on      
            tcnt++;
        }
            
        
        if (tcnt >= 20) { // 1sec : 50msx20
            tsec++;
            tcnt = 0;
            GPIO5 = ~GPIO5;
        }

        if (tsec >= TIMER_MIN*60  ) {
            endflag = 1;
            TMR1ON = 0;
        }
    }
    
    GPIO2 = 0;
    while (1) ;
    
    return;
}
