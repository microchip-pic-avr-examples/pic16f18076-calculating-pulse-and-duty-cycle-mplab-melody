/*
 * File:   Polled_Input.c
 * Author: C63290
 *
 * Created on November 15, 2022, 10:32 AM
 */


#include <xc.h>
#include "Polled_Input.h"
#include "Basic_Init.h"
#include "mcc_generated_files/system/system.h"





void Polled_Input_Calculations(void){  
    uint24_t pulse_count = 0;
    uint24_t period_count = 0;
    uint8_t period_countH = 0;
    uint8_t period_countL = 0;
    uint8_t pulse_countH = 0;
    uint8_t pulse_countL = 0;
    uint8_t duty_cycle = 0;
    
    while(PORTBbits.RB5 == HIGH);
    while(PORTBbits.RB5 == LOW);
    while(PORTBbits.RB5 == HIGH){
        pulse_count = pulse_count + 1;
    }
    while(PORTBbits.RB5 == LOW){
        period_count = period_count + 1;
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
}
