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

void IOC_wo_Timer_Pulse_Calculation(void){
    IOC_wo_Timer_Initialize();

}
void IOC_wo_Timer_Calculation(void){
    
    IOC_wo_Timer_Deinitialize();
}
