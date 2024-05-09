#include "mcc_generated_files/mcc.h"
#include <xc.h>
#define Dgt1 LATCbits.LATC3
#define Dgt2 LATCbits.LATC4
#define DS   LATC6
#define STCP LATC5
#define SHCP LATC7

unsigned int number;
unsigned char d1, d2, d3, d4;
unsigned char Digit[10] = {0x03, 0x9F, 0X25, 0x0D, 0x99, 0x49, 0x41, 0x1F, 0x01, 0x09};
unsigned int counter = 0;
unsigned int number=0;


void writeDigit(unsigned char digit) {
    unsigned char i;
    SHCP = 0;
    STCP = 0;
    SHCP = 0;
    STCP = 0;
    for (i = 0; i < 8; i++) {
        DS = (digit >> i) & 0x01;
        SHCP = 1;
        SHCP = 1;
        SHCP = 0;
        SHCP = 0;
    }
    STCP = 1;
    STCP = 1;
}

void displayNumber(unsigned int number1) {
    d1 = number1 / 1000;
    number1 %= 1000;
    d2 = number1 / 100;
    number1 %= 100;
    d3 = number1 / 10;
    d4 = number1 % 10;

    Dgt1 = 1;
    Dgt2 = 1;
    writeDigit(Digit[d1]);
    __delay_ms(5);

    Dgt1 = 0;
    Dgt2 = 1;
    writeDigit(Digit[d2]);
    __delay_ms(5);

    Dgt1 = 1;
    Dgt2 = 0;
    writeDigit(Digit[d3]);
    __delay_ms(5);

    Dgt1 = 0;
    Dgt2 = 0;
    writeDigit(Digit[d4]);
    __delay_ms(5);
}

void main(void) {
      SYSTEM_Initialize();
       TRISC = 0x00;
    // PORTC'yi temizle
    LATC = 0x00;

    // number'? 30'a ba?lat
    number = 30;
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();

    while (1) {
        counter++; // Increment counter
        if (counter >= 50)
        {
            counter = 0;
            if (number > 0)
                number--;
        }
        displayNumber(number);
      if (number == 0) // number s?f?r oldu?unda tekrar 30'a ayarla
            number = 30;
              }
}
