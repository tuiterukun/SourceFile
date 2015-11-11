/* 
 * File:   system.c
 * Author: yasutomo
 *
 * Created on November 8, 2015, 5:05 PM
 */


#include <PPS.h>
#include "system.h"

void SYSTEM_Initialize (void)
{
    /*set AD converter*/
    AD1PCFG = 0xF1F0; //use AN0,AN1,AN2,AN3,AN9,AN10,AN11 -> 0b 1111 0001 1111 0000 = 0xFFFD

    TRISAbits.TRISA1 = 1;   //P2: set to Input for analog in
    TRISAbits.TRISA0 = 1;   //P3: set to Input for analog in
    TRISAbits.TRISA2 = 1;   //P4: set to Input for analog in
    TRISAbits.TRISA3 = 1;   //P5: set to Input for analog in

    TRISBbits.TRISB2 = 1;   //P6: set to Input  for UART Rx
    TRISBbits.TRISB3 = 0;   //P7: set to Output for UART Tx

    TRISAbits.TRISA3 = 0;   //P10: set to Output for high side switch
    PORTAbits.RA3 = 0;      //turn off high side switch

    TRISBbits.TRISB13 = 1;   //P24: set to Input for analog in
    TRISBbits.TRISB14 = 1;   //P25: set to Input for analog in
    TRISBbits.TRISB15 = 1;   //P26: set to Input for analog in

    TRISBbits.TRISB11 = 1;
    TRISBbits.TRISB10 = 0;

    TRISBbits.TRISB7 = 0;   //set 
    RPINR20bits.SDI1R = 11; // SDI??RP7??
    RPOR5bits.RP10R = 8;    // SCK1??RP2??
    RPOR3bits.RP7R = 7;     // SDO1??RP3??
    
}
