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
#ifndef BASIC_INIT_H
#define	BASIC_INIT_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */
    
 extern const struct TMR_INTERFACE Timer0;   
 extern const struct TMR_INTERFACE Timer1;

void Timer1_StartSinglePulseAcquisition(void);
void Timer1_Start(void);
void Timer1_Write(size_t timerVal);
void Timer1_Stop(void);
void Timer1_Initialize_Timer1Gate(void);
void Timer1_Initialize_CLCNCO1(void);
void Timer1_OverflowCallbackRegister(void (* CallbackHandler)(void));
void Timer1_Initialize(void);

void Timer0_Start(void);
void Timer0_Stop(void);
void Timer0_OverflowCallbackRegister(void (* CallbackHandler)(void));
uint16_t Timer0_Read(void);
void Timer0_Initialize(void);
void Timer0_Write(size_t timerVal);

void NCO1_Initialize(void);
void CLC1_Initialize(void);
void CLC2_Initialize(void);
void CLC1_CLCI_SetInterruptHandler(void (* InterruptHandler)(void));

void Timer1_Gate_Initialize(void);

void CCP_Initialize(void);
void CCP_Deinitialize(void);

void TMR0_Reset(void);
void IOC_w_Timer_Initialize(void);
void IOC_wo_Timer_Initialize(void);
void IOC_Reset(void);

    
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* BASIC_INIT_H */

