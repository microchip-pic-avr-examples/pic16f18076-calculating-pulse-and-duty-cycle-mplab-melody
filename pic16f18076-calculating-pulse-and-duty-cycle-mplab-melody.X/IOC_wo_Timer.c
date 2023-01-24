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
    IOCBP = 0x20;
    IOCBN = 0x20;
    uint24_t pulse_count = 0;
    uint24_t period_count = 0;
    uint8_t period_countH = 0;
    uint8_t period_countL = 0;
    uint8_t pulse_countH = 0;
    uint8_t pulse_countL = 0;
    uint8_t duty_cycle = 0;
    IOCBFbits.IOCBF5 = 0;
    
    while(PORTBbits.RB5 == LOW);
        while(PORTBbits.RB5 == HIGH);
        IOCBFbits.IOCBF5 = 0;
        while(!IOCBFbits.IOCBF5);
        while(IOCBFbits.IOCBF5)
        {
            IOCBFbits.IOCBF5 = 0; 

            while(!IOCBFbits.IOCBF5){
                pulse_count = pulse_count + 1;
            }
            IOCBFbits.IOCBF5 = 0; 
            while(!IOCBFbits.IOCBF5){
                period_count = period_count + 1;
            }
            IOCBFbits.IOCBF5 = 0;
        }
               
        period_count = period_count + pulse_count;
        
        period_countH = (period_count & 0xFF00) >> 8;
        period_countL = (period_count & 0xFF);
        pulse_countH = (pulse_count & 0xFF00) >> 8;
        pulse_countL = (pulse_count & 0xFF);
        
        duty_cycle = (pulse_count << 8)/ period_count;
        
        EUSART1_sendAllData(pulse_countH, pulse_countL, period_countH, period_countL, duty_cycle);

        pulse_count = 0;
        period_count = 0;

        __delay_ms(1);

    IOCBP = 0x00;
    IOCBN = 0x00;

}
