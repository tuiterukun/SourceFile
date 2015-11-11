#ifdef __XC32
#include <plib.h>
#endif
#ifdef __XC16
#include <xc.h>
#endif

#include <stdio.h>
#include "set_uart.h"
#include <uart.h>
#include <PPS.h>


void uart_init(void)
{
#if defined(__XC32) || defined(__XC16)
   
    //port settings
    iPPSOutput( OUT_PIN_PPS_RP3, OUT_FN_PPS_U1TX );
    iPPSInput(  IN_FN_PPS_U1RX,  IN_PIN_PPS_RP2  );



    //----------------------
    // UART1?????
    //----------------------
    CloseUART1();

    unsigned int config1 =  UART_EN &               // UART enable
                            UART_IDLE_CON &         // operate in Idle mode
                            UART_DIS_WAKE &         // Don't wake up in sleep mode
                            UART_IrDA_DISABLE &
                            UART_DIS_LOOPBACK &     // don't loop back
                            UART_NO_PAR_8BIT &      // No parity bit, 8bit
                            UART_1STOPBIT &         // Stop bit
                            UART_MODE_SIMPLEX  &    // no flow control
                            UART_UEN_00 &
                            UART_UXRX_IDLE_ONE &    // U1RX idle 1
                            UART_BRGH_SIXTEEN &     // invalid high speed transport
                            UART_DIS_ABAUD;         // disable audo baud

    unsigned int config2 =  UART_INT_TX_BUF_EMPTY &  // TXD interrupt on
                            UART_IrDA_POL_INV_ZERO & // U1TX idle clear
                            UART_TX_ENABLE &         // Enable TXD
                            UART_INT_RX_CHAR &       // RXD interrupt on
                            UART_ADR_DETECT_DIS &
                            UART_RX_OVERRUN_CLEAR;

    OpenUART1(config1, config2, UART_CLK8MHZ_9600BPS );

    ConfigIntUART1( UART_RX_INT_DIS & UART_TX_INT_DIS );
#endif
}

/****************************
 * char uart_get_char(void);
 * get char from UART Rx
 * wait until data ready
*****************************/
char uart_get_char(void){
    char cmd;
     while(1){
        //if(U1STAbits.URXDA ==1){
        if(DataRdyUART1()==1){
            if(U1STAbits.OERR||U1STAbits.FERR)break;
            cmd = ReadUART1();
            break;
        }
    }
    
    return(cmd);
}
