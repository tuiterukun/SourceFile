/*
 * File:   main.c
 * Author: shirahama
 *
 * Created on 2015/09/16, 9:51
 * 
 * This project works well, so do not modify.
 * AN0,1(PIN2,3) -> CTMU
 * PR2,3(PIN6,7) -> UART
 */

#include <stdio.h>
#include <stdlib.h>
#include "xc.h"

#define FCY 16000000UL
#include <libpic30.h>
#include "system.h"
#include "set_uart.h"
#include "config.h"
#include "ctmu.h"

#define SENSOR1 0 //AN0
#define SENSOR2 1 //AN1

int main(void) {
    
    config_init();
    SYSTEM_Initialize();
    uart_init();
    
    char cmd = uart_get_char();
    float cap1 = CapacitiveSensing(SENSOR1);
    printf("r%4.2f\n\r",cap1);
   
    /* 
     * for PIC measurement without Multiplexer
     * 
    char cmd = uart_get_char();
    float cap1 = CapacitiveSensing(SENSOR1);
    float cap2 = CapacitiveSensing(SENSOR2);
    printf(" PIN1        : %4.2f, PIN2: %4.2f\n\r",cap1,cap2);    //for PIC measurement
    printf(" %4.2f\n\r",cap1);
     *
     *
     */
    
    __delay_ms(100);
    
    return 0;
}

