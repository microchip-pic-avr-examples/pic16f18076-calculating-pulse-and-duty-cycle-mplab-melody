/*
 * File:   CLC_NCO.c
 * Author: C63290
 *
 * Created on November 15, 2022, 10:31 AM
 */


#include <xc.h>
#include "CLC_NCO.h"
#include "Basic_Init.h"
#include "mcc_generated_files/system/system.h"

void CLC_NCO_Pulse_Calculation1(void){
    CLC_NCO_Initialize1();

}
void CLC_NCO_Duty_Cycle_Calculation1(void){
    
    CLC_NCO_Deinitialize1();
}
void CLC_NCO_Pulse_Calculation2(void){
    CLC_NCO_Initialize2();

}
void CLC_NCO_Duty_Cycle_Calculation2(void){
    
    CLC_NCO_Deinitialize2();
}
void CLC_NCO_Pulse_Calculation3(void){
    CLC_NCO_Initialize3();

}
void CLC_NCO_Duty_Cycle_Calculation3(void){
    
    CLC_NCO_Deinitialize3();
}