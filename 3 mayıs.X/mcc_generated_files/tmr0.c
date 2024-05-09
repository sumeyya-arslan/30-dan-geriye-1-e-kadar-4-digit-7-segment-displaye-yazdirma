#include <xc.h>
#include "tmr0.h"
#define Dgt1 LATCbits.LATC3
#define Dgt2 LATCbits.LATC4
#define DS  LATC6      //PORTCbits.RC6
#define STCP LATC5     //PORTCbits.RC5
#define SHCP LATC7     //PORTCbits.RC7
#define RelayControl LATCbits.LATC2
extern unsigned int counter = 0;
extern unsigned int number=0;
extern unsigned char d1, d2, d3, d4;
extern unsigned char Digit[10];
extern unsigned int displayNumber;

volatile uint8_t timer0ReloadVal;

void TMR0_Initialize(void)
{
    // Set TMR0 to the options selected in the User Interface

    // PSA assigned; PS 1:256; TMRSE Increment_hi_lo; mask the nWPUEN and INTEDG bits
    OPTION_REG = (OPTION_REG & 0xC0) | 0xF7 & 0x3F; 

    // TMR0 3; 
    TMR0 = 0x03;

    // Load the TMR value to reload variable
    timer0ReloadVal= 3;

    // Clear Interrupt flag before enabling the interrupt
    INTCONbits.TMR0IF = 0;

    // Enabling TMR0 interrupt
    INTCONbits.TMR0IE = 1;
}
uint8_t TMR0_ReadTimer(void)
{
    uint8_t readVal;

    readVal = TMR0;

    return readVal;
}
void TMR0_WriteTimer(uint8_t timerVal)
{
    // Write to the Timer0 register
    TMR0 = timerVal;
}
void TMR0_Reload(void)
{
    // Write to the Timer0 register
    TMR0 = timer0ReloadVal;
}
void TMR0_ISR(void)
{
   if (INTCONbits.TMR0IF==1) {
        // Timer0'u tekrar ba?lat
        TMR0 = timer0ReloadVal;
        // Ta?ma bayra??n? s?f?rla
        INTCONbits.TMR0IF = 0;
    }
}
