/*
 * File:   Basic_Init.c
 * Author: C63290
 *
 * Created on November 15, 2022, 10:31 AM
 */


#include <xc.h>
#include "Basic_Init.h"
#include "mcc_generated_files/system/system.h"

volatile uint16_t timer1ReloadVal;

const struct TMR_INTERFACE Timer1 = {
    .Initialize = Timer1_Initialize,
    .Start = Timer1_Start,
    .Stop = Timer1_Stop,
    .PeriodCountSet = Timer1_Write,
    .TimeoutCallbackRegister = Timer1_OverflowCallbackRegister,
    .Tasks = NULL
};

static void (*Timer1_OverflowCallback)(void);
static void Timer1_DefaultOverflowCallback(void);

void Timer1_StartSinglePulseAcquisition(void){
    T1GCONbits.T1GGO = 1;
}
void Timer1_Start(void){
    // Start the Timer by writing to TMRxON bit
    T1CONbits.TMR1ON = 1;
}
void Timer1_Write(size_t timerVal){
    if (T1CONbits.nT1SYNC == 1)
    {
        // Stop the Timer by writing to TMRxON bit
        T1CONbits.TMR1ON = 0;

        // Write to the Timer1 register
        TMR1H = (uint8_t)(timerVal >> 8);
        TMR1L = (uint8_t)timerVal;

        // Start the Timer after writing to the register
        T1CONbits.TMR1ON = 1;
    }
    else
    {
        // Write to the Timer1 register
        TMR1H = (uint8_t)(timerVal >> 8);
        TMR1L = (uint8_t)timerVal;
    }
}
void Timer1_Stop(void){
    // Stop the Timer by writing to TMRxON bit
    T1CONbits.TMR1ON = 0;
}
void Timer1_OverflowCallbackRegister(void (* CallbackHandler)(void)){
    Timer1_OverflowCallback = CallbackHandler;
}
static void Timer1_DefaultOverflowCallback(void){
    //Add your interrupt code here or
    //Use Timer1_OverflowCallbackRegister function to use Custom ISR
}
void Timer1_Initialize_Timer1Gate(void){
    //TGGO done; TGSPM enabled; TGTM disabled; TGPOL low; TMRGE disabled; 
    T1GCON = 0x10;
    //TGSS T1GPPS; 
    T1GATE = 0x0;
    //TMRCS FOSC; 
    T1CLK = 0x2;
    //TMRH 255; 
    TMR1H = 0xFF;
    //TMRL 156; 
    TMR1L = 0x9C;

    // Load the TMR1 value to reload variable
    timer1ReloadVal=(uint16_t)((TMR1H << 8) | TMR1L);

    //Set default callback for TMR1 overflow interrupt
    Timer1_OverflowCallbackRegister(Timer1_DefaultOverflowCallback);

        // Clearing TMRGI IF flag before enabling the interrupt.
         PIR1bits.TMR1GIF = 0;
        // Enabling TMRGI interrupt.
         PIE1bits.TMR1GIE = 0;

    
    //TMRON enabled; TRD16 disabled; nTSYNC synchronize; TCKPS 1:1; 
    T1CON = 0x1;
}
void Timer1_Initialize_CLCNCO1(void){
    //TGGO done; TGSPM disabled; TGTM disabled; TGPOL low; TMRGE disabled; 
    T1GCON = 0x0;
    //TGSS T1GPPS; 
    T1GATE = 0x0;
    //TMRCS FOSC; 
    T1CLK = 0x2;
    //TMRH 0; 
    TMR1H = 0x0;
    //TMRL 1; 
    TMR1L = 0x1;

    // Load the TMR1 value to reload variable
    timer1ReloadVal=(uint16_t)((TMR1H << 8) | TMR1L);

    //Set default callback for TMR1 overflow interrupt
    Timer1_OverflowCallbackRegister(Timer1_DefaultOverflowCallback);

    //Clear interrupt flags
    PIR1bits.TMR1IF = 0;
    PIR1bits.TMR1GIF = 0;
    
    //TMRON disabled; TRD16 disabled; nTSYNC synchronize; TCKPS 1:1; 
    T1CON = 0x0;
}
void Timer1_Initialize(void){
    //TGGO done; TGSPM disabled; TGTM disabled; TGPOL low; TMRGE disabled; 
    T1GCON = 0x0;
    //TGSS T1GPPS; 
    T1GATE = 0x0;
    //TMRCS FOSC; 
    T1CLK = 0x2;
    //TMRH 0; 
    TMR1H = 0x0;
    //TMRL 1; 
    TMR1L = 0x1;
};

void CCP_Initialize(void){
    
}
void CCP_Deinitialize(void){
    
}
