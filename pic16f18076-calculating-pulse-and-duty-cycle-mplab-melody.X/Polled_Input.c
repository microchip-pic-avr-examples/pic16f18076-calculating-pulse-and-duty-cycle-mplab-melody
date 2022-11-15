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

void Polled_Input_Pulse_Calculation(void){
    Polled_Input_Initialize();

}
void Polled_Input_Duty_Cycle_Calculation(void){
    
    Polled_Input_Deinitialize();
}