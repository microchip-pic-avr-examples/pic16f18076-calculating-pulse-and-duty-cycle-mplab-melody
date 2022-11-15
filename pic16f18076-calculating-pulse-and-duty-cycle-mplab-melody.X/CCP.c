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

void CCP_Pulse_Calculation(void){
    CCP_Initialize();

}
void CCP_Duty_Cycle_Calculation(void){
    
    CCP_Deinitialize();
}
