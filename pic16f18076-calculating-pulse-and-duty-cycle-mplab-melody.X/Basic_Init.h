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
    
// Peripheral Functions and Declarations   
    
    //Timer 0 Functions and Declarations
    
extern const struct TMR_INTERFACE Timer0;      
void Timer0_Start(void);
void Timer0_Stop(void);
void Timer0_OverflowCallbackRegister(void (* CallbackHandler)(void));
uint16_t Timer0_Read(void);
void Timer0_Initialize(void);
void Timer0_Write(size_t timerVal);   
void Timer0_Initialize_CLCNCO3(void);
    
    //Timer 1 Functions and Declarations
 
extern const struct TMR_INTERFACE Timer1;

void Timer1_StartSinglePulseAcquisition(void);
void Timer1_Start(void);
void Timer1_Write(size_t timerVal);
void Timer1_Stop(void);
void Timer1_Initialize_Timer1Gate(void);
void Timer1_Initialize_CLCNCO1(void);
void Timer1_Initialize_CLCNCO2(void);
void Timer1_Initialize_CLCNCO3(void);
void Timer1_OverflowCallbackRegister(void (* CallbackHandler)(void));
void Timer1_Initialize(void);

    //CLC1 Functions and Declarations

void CLC1_Initialize(void);
void CLC1_Initialize_CLCNCO1(void);
void CLC1_Initialize_CLCNCO2(void);
void CLC1_Initialize_CLCNCO3(void);

void CLC1_CLCI_SetInterruptHandler(void (* InterruptHandler)(void));

    //CLC2 Functions and Declarations

void CLC2_Initialize(void);
void CLC2_Initialize_CLCNCO1(void);
void CLC2_Initialize_CLCNCO2(void);
void CLC2_Initialize_CLCNCO3(void);

    //CLC3 Functions and Declarations

void CLC3_Initialize(void);
void CLC3_Initialize_CLCNCO2(void);
void CLC3_Initialize_CLCNCO3(void);

    //NCO1 Functions and Declarations
void NCO1_Initialize(void);

    //CCP1 Functions and Declarations
void CCP1_Initialize(void);
uint16_t CCP1_CaptureRead(void);
typedef union CCPR1Reg_tag
{
   struct
   {
      uint8_t ccpr1l; /**< CCPR1L low byte.*/
      uint8_t ccpr1h; /**< CCPR1H high byte.*/
   };
   struct
   {
      uint16_t ccpr1_16Bit; /**< CCPR1 16-bit.*/
   };
} CCPR1_PERIOD_REG_T ;

    //CCP2 Functions and Declarations
void CCP2_Initialize(void);
uint16_t CCP2_CaptureRead(void);
typedef union CCPR2Reg_tag
{
   struct
   {
      uint8_t ccpr2l; /**< CCPR2L low byte.*/
      uint8_t ccpr2h; /**< CCPR2H high byte.*/
   };
   struct
   {
      uint16_t ccpr2_16Bit; /**< CCPR2 16-bit.*/
   };
} CCPR2_PERIOD_REG_T ;

// Initialization Functions
void Timer1_Gate_Initialize(void);
void CLC_NCO1_Initialize(void);
void CLC_NCO2_Initialize(void);
void CLC_NCO3_Initialize(void);
void CCP_Initialize(void);
void IOC_w_Timer_Initialize(void);
void IOC_wo_Timer_Initialize(void);

//Pins and PPS Functions
void CLC_NCO1_Pins_PPS(void);
void CLC_NCO2_Pins_PPS(void);
void CLC_NCO3_Pins_PPS(void);

//Reset-Clear Functions
void TMR0_Reset(void);
void TMR1_Reset(void);
void CLC1_Reset(void);
void CLC2_Reset(void);
void CLC3_Reset(void);
void IOC_Reset(void);
void Pins_PPS_Reset(void);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* BASIC_INIT_H */

