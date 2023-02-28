/*
 * File:   CCP.c
 * Author: C63290
 *
 * Created on November 15, 2022, 10:31 AM
 */


#include <xc.h>
#include "CCP.h"
#include "Basic_Init.h"
#include "mcc_generated_files/system/system.h"

    uint24_t pulse_count = 0;
    uint24_t period_count = 0;
    uint8_t duty_cycle = 0;
    uint16_t temp1 = 0;
    uint16_t temp2 = 0;
    uint16_t temp3 = 0;
    uint16_t temp4 = 0;

void CCP_Calculations(void){
    CCP1CONbits.EN = 1;
    Timer1_Start();

    while(!PIR2bits.CCP1IF);

    CCP1CONbits.EN = 0;
    PIR2bits.CCP1IF = 0;

    temp1 = CCP1_CaptureRead();

    CCP1CONbits.EN = 1;
    CCP2CONbits.EN = 1;

    while(!PIR2bits.CCP2IF);
    CCP2CONbits.EN = 0;
    PIR2bits.CCP2IF = 0;
    CCP2CONbits.EN = 1;

    while(!PIR2bits.CCP2IF);
    CCP2CONbits.EN = 0;
    PIR2bits.CCP2IF = 0;
    temp3 = CCP2_CaptureRead();
    CCP2CONbits.EN = 1;

    while(!PIR2bits.CCP2IF);
    CCP2CONbits.EN = 0;
    PIR2bits.CCP2IF = 0;
    temp4 = CCP2_CaptureRead();

    while(!PIR2bits.CCP1IF);

    CCP1CONbits.EN = 0;
    Timer1_Stop();

    PIR2bits.CCP1IF = 0;

    temp2 = CCP1_CaptureRead();      

    period_count = temp2 - temp1;
    pulse_count = temp4 - temp3;
    duty_cycle = (pulse_count << 8)/ (period_count >> 2);

    EUSART1_sendString("\nPULSE:");
    EUSART1_sendInt(pulse_count>>16);
    EUSART1_sendInt(pulse_count>>8);
    EUSART1_sendInt(pulse_count);

    EUSART1_sendString("\nPD: ");
    EUSART1_sendInt(period_count>>8);
    EUSART1_sendInt(period_count);

    EUSART1_sendString("\nDC: ");
    EUSART1_sendInt(duty_cycle);

    pulse_count = 0;
    period_count = 0;

    __delay_ms(1);
}
