/*
 * File:   Basic_Init.c
 * Author: C63290
 *
 * Created on November 15, 2022, 10:31 AM
 */


#include <xc.h>
#include "Basic_Init.h"
#include "mcc_generated_files/system/system.h"

void Timer1_Gate_Initialize(void){
    
}
void Timer1_Gate_Deinitialize(void){
    
}

void CLC_NCO_Initialize1(void){
    
}
void CLC_NCO_Deinitialize1(void){
    
}
void CLC_NCO_Initialize2(void){
    
}
void CLC_NCO_Deinitialize2(void){
    
}
void CLC_NCO_Initialize3(void){
    
}
void CLC_NCO_Deinitialize3(void){
    
}

void CCP_Initialize(void){
    
}
void CCP_Deinitialize(void){
    
}

void IOC_w_Timer_Initialize(void){
    
}
void IOC_w_Timer_Deinitialize(void){
    
}

void IOC_wo_Timer_Initialize(void){
    
}
void IOC_wo_Timer_Deinitialize(void){
    
}

void Polled_Input_Initialize(void){
    //Pins
    //NA
    
    //Peripherals
    //NA
    
    //PPS
    //NA
    
    //Method Specific
    uint24_t pulse_count = 0;
    uint24_t period_count = 0;
    uint8_t period_countH = 0;
    uint8_t period_countL = 0;
    uint8_t pulse_countH = 0;
    uint8_t pulse_countL = 0;
    uint8_t duty_cycle = 0;
}
void Polled_Input_Deinitialize(void){
    
}
