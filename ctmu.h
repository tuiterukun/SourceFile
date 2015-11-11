/* 
 * File:   ctmu.h
 * Author: Naoy_Miyamoto
 *
 * Created on 2015/05/13, 13:50
 */

#ifndef CTMU_H
#define	CTMU_H

#ifdef	__cplusplus
extern "C" {
#endif


void calibIsrc(void);
void calibCAP(void);


unsigned char initADC(unsigned char ch_num); //set ADC for CTMU
unsigned char InitCTMU(unsigned char ch_num);//initialize ctmu module

unsigned int runCTMU(void); //measure the Voltage = IT/C
float CapacitiveSensing(unsigned char ch_num);
unsigned int getVbaseline(void);//get baseline


#ifdef	__cplusplus
}
#endif

#endif	/* CTMU_H */

