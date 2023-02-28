/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef CLC_NCO_H
#define	CLC_NCO_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

void CLC_NCO1_Calculations(void);
void CLC_NCO2_Calculations(void);
void CLC_NCO3_Calculations(void);

void send_NCO_measurement(void);
void send_TMR0_measurement(void);
void send_TMR1_measurement(void);
void clear_NCO_Accumulator(void);
void clear_TMR0_Value(void);
void clear_TMR1_Value(void);
void MAX_TMR1_Value(void);
void send_DC_Calculation_CLCNCO1_CLCNCO2(void);
void send_DC_Calculation_CLCNCO3(void);
void send_DC_Calculation_MT(void);
void send_measurement_CLCNCO1_CLCNCO2(void);
void send_measurement_CLCNCO3(void);
void send_measurement_MT(void);
void clear_flags_CLCNCO1_CLCNCO2(void);
void clear_flags_CLCNCO3(void);
void reset_CLC2_CLC3(void);
void setup_for_new_measurement_CLCNCO1(void);
void setup_for_new_measurement_CLCNCO2(void);
void setup_for_new_measurement_CLCNCO3(void);


#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* CLC_NCO_H */

