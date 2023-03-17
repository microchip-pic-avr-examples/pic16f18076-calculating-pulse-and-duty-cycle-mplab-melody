/*
 * File:   IOC_wo_Timer.c
 * Author: C63290
 *
 * Created on November 15, 2022, 10:32 AM
 */


#include <xc.h>
#include "IOC_wo_Timer.h"
#include "Basic_Init.h"
#include "mcc_generated_files/system/system.h"

void IOC_wo_Timer_Calculations(void){
    IOC_wo_Timer_Initialize();                              // Run the IOC without Timer Initialization function
    uint24_t pulse_count = 0;
    uint24_t period_count = 0;
    uint8_t period_countH = 0;
    uint8_t period_countL = 0;
    uint8_t pulse_countH = 0;
    uint8_t pulse_countL = 0;
    uint8_t duty_cycle = 0;
    IOCBFbits.IOCBF5 = 0;                                   // Clear the RB5 IOC Flag
    
    while(PORTBbits.RB5 == LOW)                             // Wait for the input signal to go low
    ;                                                       // Silences a warning
    while(PORTBbits.RB5 == HIGH);                           // Wait for the input signal to go high       
    IOCBFbits.IOCBF5 = 0;                                
    while(!IOCBFbits.IOCBF5);                               // Wait for the the RB5 IOC Flag to be triggered 
    while(IOCBFbits.IOCBF5){                                
        IOCBFbits.IOCBF5 = 0;                             

        while(!IOCBFbits.IOCBF5){                           
            pulse_count = pulse_count + 1;                  // While the RB5 IOC Flag is low, increment the pulse_count
        }
        IOCBFbits.IOCBF5 = 0;   
        while(!IOCBFbits.IOCBF5){
            period_count = period_count + 1;                // While the RB5 IOC Flag is low, increment the period_count
        }
        IOCBFbits.IOCBF5 = 0;
    }

    period_count = period_count + pulse_count;              // Add up the pulse and the period counts to make the correct period count

    period_countH = (period_count & 0xFF00) >> 8;           // Split the period count into a high and low byte
    period_countL = (period_count & 0xFF);
    pulse_countH = (pulse_count & 0xFF00) >> 8;             // Split the pulse count into a high and low byte
    pulse_countL = (pulse_count & 0xFF);

    duty_cycle = (pulse_count << 8)/ period_count;          // Calculate the duty cycle

    EUSART1_sendAllData(pulse_countH, pulse_countL, period_countH, period_countL, duty_cycle); // Send data over UART

    pulse_count = 0;
    period_count = 0;

    __delay_ms(1);                                          // Wait for 1ms

    IOC_Reset();                                            // Reset IOC changes
}
