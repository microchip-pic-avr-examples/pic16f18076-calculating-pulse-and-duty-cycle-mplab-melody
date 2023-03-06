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
    uint16_t value1 = 0;
    uint16_t value2 = 0;
    uint16_t value3 = 0;
    uint16_t value4 = 0;

void CCP_Calculations(void){
    CCP1CONbits.EN = 1;                                         // Enable CCP1
    Timer1_Start();                                             // Start Timer1

    while(!PIR2bits.CCP1IF);                                    // Wait until the CCP1 Interrupt Flag is set

    CCP1CONbits.EN = 0;                                         // Disable CCP1
    PIR2bits.CCP1IF = 0;                                        // Clear the CCP1 Interrupt Flag

    value1 = CCP1_CaptureRead();                                // Set value1 to be the current CCP1 value

    CCP1CONbits.EN = 1;                                         
    CCP2CONbits.EN = 1;                                         // Enable CCP2

    while(!PIR2bits.CCP2IF);                                    // Wait until the CCP2 Interrupt Flag is set
    CCP2CONbits.EN = 0;                                         // Disable CCP2
    PIR2bits.CCP2IF = 0;                                        // Clear the CCP2 Interrupt Flag
    CCP2CONbits.EN = 1;

    while(!PIR2bits.CCP2IF);
    CCP2CONbits.EN = 0;
    PIR2bits.CCP2IF = 0;
    value3 = CCP2_CaptureRead();                                // Set value3 to be the current CCP2 value
    CCP2CONbits.EN = 1;

    while(!PIR2bits.CCP2IF);
    CCP2CONbits.EN = 0;
    PIR2bits.CCP2IF = 0;
    value4 = CCP2_CaptureRead();                                // Set value4 to be the current CCP2 value

    while(!PIR2bits.CCP1IF);

    CCP1CONbits.EN = 0;
    Timer1_Stop();                                              // Stop Timer1

    PIR2bits.CCP1IF = 0;

    value2 = CCP1_CaptureRead();                                // Set value2 to be the current CCP1 value

    period_count = value2 - value1;                             // Calculate the period (difference between value2 and value1)
    pulse_count = value4 - value3;                              // Calculate the pulse (difference between value4 and value3)
    duty_cycle = (pulse_count << 8)/ (period_count >> 2);       // Calculate the duty cycle (pulse value right shifted 8 divided by the period left shifted 2)

    EUSART1_sendString("\nPULSE:");                             // Send pulse data over UART
    EUSART1_sendInt(pulse_count>>16);
    EUSART1_sendInt(pulse_count>>8);
    EUSART1_sendInt(pulse_count);

    EUSART1_sendString("\nPD: ");                               // Send period data over UART
    EUSART1_sendInt(period_count>>8);
    EUSART1_sendInt(period_count);

    EUSART1_sendString("\nDC: ");                               // Send duty cycle data over UART
    EUSART1_sendInt(duty_cycle);

    pulse_count = 0;
    period_count = 0;

    __delay_ms(1);                                              // Wait for 1ms
}
