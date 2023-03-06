/*
 * File:   IOC_w_Timer.c
 * Author: C63290
 *
 * Created on November 15, 2022, 10:32 AM
 */


#include <xc.h>
#include "IOC_w_Timer.h"
#include "Basic_Init.h"
#include "mcc_generated_files/system/system.h"

void IOC_w_Timer_Calculations(void){
    IOC_w_Timer_Initialize();                               // Run the IOC with Timer Initialization function
    uint24_t pulse_count = 0;
    uint24_t period_count = 0;
    uint8_t period_countH = 0;
    uint8_t period_countL = 0;
    uint8_t pulse_countH = 0;
    uint8_t pulse_countL = 0;
    uint8_t duty_cycle = 0;
    IOCBFbits.IOCBF5 = 0;                                   // Clear the RB5 IOC Flag
    TMR0L = 0;                                              // Clear Timer0 Low byte
    TMR0H = 0;                                              // Clear Timer0 High byte

    while(PORTBbits.RB5 == LOW);                            // Wait for the input signal to go low
    while(PORTBbits.RB5 == HIGH);                           // Wait for the input signal to go high 
    IOCBFbits.IOCBF5 = 0;
    while(!IOCBFbits.IOCBF5);                               // Wait for the RB5 IOC Flag to be triggered 
    while(IOCBFbits.IOCBF5){
        IOCBFbits.IOCBF5 = 0;
        Timer0_Start();                                     // Start Timer0
        while(!IOCBFbits.IOCBF5);
        IOCBFbits.IOCBF5 = 0;
        Timer0_Stop();                                      // Stop Timer0
        pulse_count = Timer0_Read();                        // Set the pulse count to equal the Timer0 count
        Timer0_Start();
        while(!IOCBFbits.IOCBF5);
        IOCBFbits.IOCBF5 = 0;
        Timer0_Stop();
        period_count = Timer0_Read();                       // Set the period count to equal the Timer0 count
    }
        
        period_countH = (period_count & 0xFF00) >> 8;       // Split the period count into a high and low byte
        period_countL = (period_count & 0xFF);
        pulse_countH = (pulse_count & 0xFF00) >> 8;         // Split the pulse count into a high and low byte
        pulse_countL = (pulse_count & 0xFF);
        
        duty_cycle = (pulse_count << 8)/ period_count;      // Calculate the duty cycle
        
        EUSART1_sendAllData(pulse_countH, pulse_countL, period_countH, period_countL, duty_cycle);  //Send data over UART

        pulse_count = 0;    
        period_count = 0;
        TMR0L = 0;
        TMR0H = 0;

        __delay_ms(1);                                      // Wait for 1ms

    IOC_Reset();                                            // Reset IOC Changes
    TMR0_Reset();                                           // Reset TMR0 Changes
}
