/*
 * File:   IOC_w_Timer.c
 * Author: C63290
 *
 * Created on November 15, 2022, 10:32 AM
 */


#include <xc.h>
#include "IOC_w_TIMER.h"
#include "Basic_Init.h"
#include "mcc_generated_files/system/system.h"

void IOC_w_Timer_Pulse_Calculation(void){
    IOC_w_Timer_Initialize();

}
void IOC_w_Timer_Calculation(void){
    
    IOC_w_Timer_Deinitialize();
}
