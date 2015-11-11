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
   
    while(1){
    
    float cap1 = CapacitiveSensing(SENSOR1);
    float cap2 = CapacitiveSensing(SENSOR2);
    
    printf("pin0: %.4f\tpin1: %.4f \n\r",cap1,cap2);
    //putsUART1("\n\r");
    
    __delay_ms(10000); 
    
    }
    
    return 0;
}

