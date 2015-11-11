/* 
 * File:   set_uart.h
 * Author: Naoy_Miyamoto
 *
 * Created on 2015/05/13, 2:00
 *
 */

#ifdef __XC16
#include <xc.h>
#endif

#include <stdio.h>


#define UART_CLK8MHZ_9600BPS 103

#ifndef SET_UART_H
#define	SET_UART_H

#ifdef	__cplusplus
extern "C" {
#endif

void uart_init(void);
void uart_close(void);

#ifdef	__cplusplus
}
#endif

#endif	/* SET_UART_H */

