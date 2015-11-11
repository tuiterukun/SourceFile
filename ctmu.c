
#ifdef __XC32
#include <plib.h>
#endif
#ifdef __XC16
#include <xc.h>
#include "delay.h"
#include "ctmu.h"
#endif

#define DISCHARGE_TIME 1000 //[us]
#define CHARGE_TIME 10 //[us]
//#define DELAY_CONST 16 //const

#define MES_COUNT 30


/*********************************************************************************************
 * calibrate CTMU module (not completed)
 ********************************************************************************************/
void calibIsrc(void){
#if defined(__XC32) || defined(__XC16)
    /*
    InitADC();
    InitCTMU();
    CTMUCONbits.TGEN = 0; //disable edge delay generation mode of the CTMU
    CTMUCONbits.EDG1STAT = 1;
    __delay32(80); //wait 20us
    */
#endif
}
void calibCAP(void){
//#if defined(__XC32) || defined(__XC16)
//#endif
}

/*********************************************************************************************
 * initialize AD converter
 * initialize the Ann port n=ch_num
 * return 1:no error
 * return 0:error
 ********************************************************************************************/
unsigned char InitADC(unsigned char ch_num){
#if defined(__XC32) || defined(__XC16)
    if((ch_num<0)&(ch_num>15)) return 0; //error

    
    AD1PCFG = 0xFFFC; //use AN0,AN1 -> 0b 1111 1111 1111 1100 = 0xFFFD
    TRISAbits.TRISA1=1;
    TRISAbits.TRISA0=1;
    AD1CON1 = 0x0000;
    //AD1CHS = 0x0001; //Channel 0 positive input is AN1
    //AD1CHS = 0x0000; //Channel 0 positive input is AN0
    AD1CHS = ch_num;

    AD1CSSL=0x0000; //Analog channel is disabled from input scan
    AD1CON1bits.ADSIDL = 1; //Discontinue module operation when device enters Idle mode
    AD1CON1bits.FORM = 0x0; //Integer (0000 00dd dddd dddd)
    AD1CON3bits.ADRC = 0; // Clock derived from system clock
    AD1CON3bits.SAMC = 0b10000; //16TAD
    AD1CON3bits.ADCS = 0x01; //2Tcy
    AD1CON2 = 0x0000; //Interrupts are at the completion of conversion for each sample/convert sequence
    AD1CON1bits.ADON = 1; //Turn On A/D
    //CTMUCONbits.CTMUEN = 1; //Enable CTMU
    return 1;
#endif
}

/*********************************************************************************************
 * initialize CTMU
 * initialize the Ann port n=ch_num
 * return 1:no error
 * return 0:error
 ********************************************************************************************/
unsigned char InitCTMU(unsigned char ch_num){
#if defined(__XC32) || defined(__XC16)
    #ifdef __PIC24FJ64GB002__

    if((ch_num<0)&(ch_num>15)) return 0; //error    
    //*Init AD Converter*//
    if(InitADC(ch_num)==0) return 0;//error
    //**************setup CTMU************//
     //CTMUCON
    CTMUCONbits.CTMUEN = 1; //make sure CTMU is disabled
    //1.set the range of current source.
    CTMUICONbits.IRNG = 0x02; //5.5uA
    //2.set the toriming paramator of current.
    CTMUICONbits.ITRIM = 0; //Nominal - No Adjustment
    //3.set the edge
    //CTMUCONbits.EDG1SEL = 0x3; //Edge1 Src = Timer1 (don?t care)
    //CTMUCONbits.EDG2SEL = 0x3; //Edge2 Src = OC1 (don?t care)
    //4.set polarity of edge( rise or )
    CTMUCONbits.EDG2POL = 0;
    CTMUCONbits.EDG1POL = 1;
    //5.edge seq
    CTMUCONbits.EDGSEQEN = 0; //edge sequence not needed
    //6 set the mode (measure cap or time)
    CTMUCONbits.TGEN = 0; //disable edge delay generation mode of the CTMU
    //7 set auto trigger.
    CTMUCONbits.CTTRIG = 0; //Trigger Output is disabled
    //8 discharge the q
    CTMUCONbits.IDISSEN = 1; //ground the current source
    delay_us(DISCHARGE_TIME);
    CTMUCONbits.IDISSEN = 0; //Do not ground the current source
    //9 clear ON bit
    CTMUCONbits.CTMUEN = 0; //make sure CTMU is disnabled
    //10.
    CTMUCONbits.EDG1STAT = 0; //Stop charging circuit
    CTMUCONbits.EDG2STAT = 0; //Stop charging circuit
    //11.
    CTMUCONbits.EDGEN = 0; //edges are blocked
    //12.
    CTMUCONbits.CTMUSIDL = 1; //Discontinue module operation when device enters Idle mode
    CTMUCONbits.CTMUEN = 1; //Enable CTMU

    return 1;
    
    #endif
    #ifdef __PIC24FJ64GA002_

    #endif
#endif
}

/*********************************************************************************************
 * runCTMU
 * 1. run CTMU module constant time period
 * 2. get AD conversion value.
 * return 10bits value of AD conversion data
 ********************************************************************************************/
unsigned int runCTMU(void){
#ifdef __PIC24FJ64GB002__
    int raw_value;

    AD1CON1bits.SAMP = 1; //Manual sampling start
    CTMUCONbits.IDISSEN = 1; //drain charge on the circuit
    //__delay32(80); //wait 20us
    //__delay32(DISCHARGE_TIME*DELAY_CONST); //wait for 20us
    delay_us(DISCHARGE_TIME);
    CTMUCONbits.IDISSEN = 0; //end drain of circuit
    Nop(); Nop();
    IFS0bits.AD1IF = 0; //Make sure A/D interrupt flag = 0
    CTMUCONbits.EDG2STAT = 0;
    CTMUCONbits.EDG1STAT = 1; //Begin charging the circuit using CTMU current source
    //__delay32(40); //wait for 10us
    //__delay32(CHARGE_TIME*DELAY_CONST); //wait for 10us
    delay_us(CHARGE_TIME);
    AD1CON1bits.SAMP = 0; //and begin A/D conv.
    CTMUCONbits.EDG1STAT = 0; //Stop charging circuit
    IFS0bits.AD1IF = 0; //make sure A/D Intrpt not set
    while(!IFS0bits.AD1IF);//Wait for A/D convert complete
    raw_value = ADC1BUF0;
    AD1CON1bits.SAMP = 0;
    IFS0bits.AD1IF = 0;
    AD1CON1bits.DONE = 0; //Make sure A/D bits are cleared

    return(raw_value);
#endif
}

/*********************************************************************************************
 * unsigned float CapacitiveSensing(unsigned char ch_num)
 * 1. run CTMU about MES_COUNT times.
 * 2. get Capacitance
 ********************************************************************************************/
float CapacitiveSensing(unsigned char ch_num){
    
    float cap;
    int i;
    float vol;
    int totalvol = 0;
    
    for( i=0 ; i < MES_COUNT ; i++ )
    {
        InitCTMU(ch_num);
        totalvol += runCTMU();
    }
    vol = totalvol / MES_COUNT;
    cap = 5.5*10/(vol/1024*3.3);
    
    return cap;
}



/*********************************************************************************************
 * unsigned int getVbaseline(void)
 * 1. run CTMU module 50 times.
 * 2. get average value of CTMU.
 * return average value.
 ********************************************************************************************/
unsigned int getVbaseline(void){
#if defined(__XC32) || defined(__XC16)
    unsigned int vRead = 0, k;

    for(k = 0; k < 50; k++){
        vRead = vRead + runCTMU();
    }

    return (vRead/50);
#endif
}

