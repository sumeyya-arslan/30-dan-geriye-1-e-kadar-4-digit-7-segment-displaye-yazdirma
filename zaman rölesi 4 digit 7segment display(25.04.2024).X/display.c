#include <stdint.h>
#include <xc.h>
// Konfig�rasyon bitleri
#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config MCLRE = OFF
#pragma config CP = OFF
#pragma config BOREN = ON
#pragma config CLKOUTEN = OFF
#pragma config WRT = OFF

#define _XTAL_FREQ 4000000

#define Dgt1 LATCbits.LATC3
#define Dgt2 LATCbits.LATC4
#define DS   LATC6
#define STCP LATC5
#define SHCP LATC7

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

void displayNumber(unsigned int number) {
    d1 = number / 1000;
    number %= 1000;
    d2 = number / 100;
    number %= 100;
    d3 = number / 10;
    d4 = number % 10;

    Dgt1 = 1;
    Dgt2 = 1;
    writeDigit(Digit[d1]);
    __delay_ms(10);

    Dgt1 = 0;
    Dgt2 = 1;
    writeDigit(Digit[d2]);
    __delay_ms(10);

    Dgt1 = 1;
    Dgt2 = 0;
    writeDigit(Digit[d3]);
    __delay_ms(10);

    Dgt1 = 0;
    Dgt2 = 0;
    writeDigit(Digit[d4]);
    __delay_ms(10);
}

void interrupt TIMER_Interrupt(void) {
    if (TMR0IF) {
        TMR0IF = 0; // Clear Timer0 interrupt flag

        
        TMR0 = 155; // Reload Timer0 to generate 0.2ms interrupt again
    }
}
void main(void){
    // PIC donan?m birimlerini ba?lat


    // Timer0'? yap?land?r
    OPTION_REGbits.TMR0CS = 0; // Dahili talimat d�ng�s� saati se� (Fosc/4)
    OPTION_REGbits.PSA = 0;    // Timer0 �n b�l�c�s�n� etkinle?tir
    OPTION_REGbits.PS = 0b111; // �n b�l�c�y� 1:256 olarak ayarla
    TMR0 = 155;                // Timer0'? 0.2 ms kesinti �retmek i�in y�kle (1 saniye yapmak i�in 5000 kesinti)

    // Timer0 kesintisini etkinle?tir
    TMR0IE = 1; // Timer0 ta?ma kesintisini etkinle?tir
    PEIE = 1;   // Periferik kesintileri etkinle?tir
    GIE = 1;    // Genel kesintileri etkinle?tir

    // PORTC'yi �?k?? olarak yap?land?r
    TRISC = 0x00;
    // PORTC'yi temizle
    LATC = 0x00;

    // number'? 30'a ba?lat
    number = 30;

    // Ana d�ng�
    while (1) {
        counter++; // Increment counter
        if (counter >= 100) { 
            counter = 0; 
            if (number > 0) 
                number--;
        }
        displayNumber(number);
      if (number == 0) // number s?f?r oldu?unda tekrar 30'a ayarla
            number = 30;
}
 }