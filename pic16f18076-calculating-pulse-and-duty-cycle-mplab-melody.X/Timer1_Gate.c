/*
 * File:   Timer1_Gate.c
 * Author: C63290
 *
 * Created on November 15, 2022, 10:31 AM
 */


#include <xc.h>
#include "Timer1_Gate.h"
#include "Basic_Init.h"
#include "mcc_generated_files/system/system.h"

void Timer1_Gate_Pulse_Calculation(void){
    Timer1_Gate_Initialize();

}
void Timer1_Gate_Duty_Cycle_Calculation(void){
    
    Timer1_Gate_Deinitialize();
}