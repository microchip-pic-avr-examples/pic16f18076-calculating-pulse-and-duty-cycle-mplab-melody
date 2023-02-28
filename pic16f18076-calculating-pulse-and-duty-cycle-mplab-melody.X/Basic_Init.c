/*
 * File:   Basic_Init.c
 * Author: C63290
 *
 * Created on November 15, 2022, 10:31 AM
 */


#include <xc.h>
#include "Basic_Init.h"
#include "CLC_NCO.h"
#include "mcc_generated_files/system/system.h"

// Peripheral Functions and Declarations   
    
    //Timer 0 Functions and Declarations

volatile uint16_t timerTMR0ReloadVal16bit;

const struct TMR_INTERFACE Timer0 = {
    .Initialize = Timer0_Initialize,
    .Start = Timer0_Start,
    .Stop = Timer0_Stop,
    .PeriodCountSet = Timer0_Write,
    .TimeoutCallbackRegister = Timer0_OverflowCallbackRegister
};

static void (*Timer0_OverflowCallback)(void);
static void Timer0_DefaultOverflowCallback(void);

void Timer0_Initialize(void){
    //TMR0H 255; 
    TMR0H = 0xFF;

    //TMR0L 240; 
    TMR0L = 0xF0;

    //T0CS HFINTOSC; T0CKPS 1:1; T0ASYNC not_synchronised; 
    T0CON1 = 0x70;

    //Load TMRTMR0 value to the 16-bit reload variable
    timerTMR0ReloadVal16bit = ((uint16_t)TMR0H << 8) | TMR0L;

    //Set default callback for TMR0 overflow interrupt
    Timer0_OverflowCallbackRegister(Timer0_DefaultOverflowCallback);

    //Clear interrupt flag
    PIR0bits.TMR0IF = 0;

    //T0OUTPS 1:1; T0EN disabled; T016BIT 16-bit; 
    T0CON0 = 0x10;
}
void Timer0_Start(void){
    T0CON0bits.T0EN = 1;
}
void Timer0_Stop(void){
    T0CON0bits.T0EN = 0;
}
uint16_t Timer0_Read(void){
    uint16_t readVal;
    uint8_t readValLow;
    uint8_t readValHigh;

    readValLow  = TMR0L;
    readValHigh = TMR0H;
    readVal  = ((uint16_t)readValHigh << 8) + readValLow;

    return readVal;
}
void Timer0_Write(size_t timerVal){
    TMR0H = timerVal >> 8;
    TMR0L = (uint8_t) timerVal;
}
void Timer0_OverflowCallbackRegister(void (* CallbackHandler)(void)){
    Timer0_OverflowCallback = CallbackHandler;
}
static void Timer0_DefaultOverflowCallback(void){
    //Add your interrupt code here or
    //Use Timer0_OverflowCallbackRegister function to use Custom ISR
}
void Timer0_Initialize_CLCNCO3(void){
    //TMR0H 255; 
    TMR0H = 0xFF;

    //TMR0L 0; 
    TMR0L = 0x0;

    //T0CS CLC1_OUT; T0CKPS 1:1; T0ASYNC synchronised; 
    T0CON1 = 0xE0;

    //Set default callback for TMR0 overflow interrupt
    Timer0_OverflowCallbackRegister(Timer0_DefaultOverflowCallback);

    //Clear interrupt flag
    PIR0bits.TMR0IF = 0;

    //T0OUTPS 1:1; T0EN disabled; T016BIT 8-bit; 
    T0CON0 = 0x0;
}

    //Timer 1 Functions and Declarations

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
void Timer1_Initialize_CLCNCO2(void){
    //TGGO done; TGSPM disabled; TGTM disabled; TGPOL low; TMRGE disabled; 
    T1GCON = 0x0;
    //TGSS T1GPPS; 
    T1GATE = 0x0;
    //TMRCS FOSC; 
    T1CLK = 0x2;
    //TMRH 0; 
    TMR1H = 0x0;
    //TMRL 1; 
    TMR1L = 0x0;

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
void Timer1_Initialize_CLCNCO3(void){
    //TGGO done; TGSPM disabled; TGTM disabled; TGPOL low; TMRGE disabled; 
    T1GCON = 0x0;
    //TGSS T1GPPS; 
    T1GATE = 0x0;
    //TMRCS FOSC; 
    T1CLK = 0x2;
    //TMRH 0; 
    TMR1H = 0x0;
    //TMRL 1; 
    TMR1L = 0x0;

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

    //CLC1 Functions and Declarations

static void (*CLC1_CLCI_InterruptHandler)(void);
static void CLC1_DefaultCLCI_ISR(void);

void CLC1_Initialize(void){
    
    // SLCT 0x0; 
    CLCSELECT = 0x0;
    // LCG1POL inverted; LCG2POL not_inverted; LCG3POL not_inverted; LCG4POL inverted; LCPOL not_inverted; 
    CLCnPOL = 0x9;
    // LCD1S CLCIN2 (CLCIN2PPS); 
    CLCnSEL0 = 0x2;
    // LCD2S CLCIN0 (CLCIN0PPS); 
    CLCnSEL1 = 0x0;
    // LCD3S FOSC; 
    CLCnSEL2 = 0x4;
    // LCD4S CLC2_OUT; 
    CLCnSEL3 = 0x1D;
    // LCG1D1N disabled; LCG1D1T disabled; LCG1D2N disabled; LCG1D2T disabled; LCG1D3N disabled; LCG1D3T disabled; LCG1D4N disabled; LCG1D4T disabled; 
    CLCnGLS0 = 0x0;
    // LCG2D1N disabled; LCG2D1T disabled; LCG2D2N disabled; LCG2D2T enabled; LCG2D3N disabled; LCG2D3T disabled; LCG2D4N disabled; LCG2D4T disabled; 
    CLCnGLS1 = 0x8;
    // LCG3D1N disabled; LCG3D1T disabled; LCG3D2N disabled; LCG3D2T disabled; LCG3D3N disabled; LCG3D3T enabled; LCG3D4N disabled; LCG3D4T disabled; 
    CLCnGLS2 = 0x20;
    // LCG4D1N disabled; LCG4D1T disabled; LCG4D2N disabled; LCG4D2T disabled; LCG4D3N disabled; LCG4D3T disabled; LCG4D4N disabled; LCG4D4T enabled; 
    CLCnGLS3 = 0x80;
    // LCOUT 0x00; 
    CLCDATA = 0x0;
    // LCMODE 4-input AND; LCINTN enabled; LCINTP disabled; LCEN enabled; 
    CLCnCON = 0x8A;

    // Clear the CLC interrupt flag
    PIR2bits.CLC1IF = 0;
    //Configure interrupt handlers
    CLC1_CLCI_SetInterruptHandler(CLC1_DefaultCLCI_ISR);
    // Enabling CLC1 interrupt.
    PIE2bits.CLC1IE = 0;
}
void CLC1_Initialize_CLCNCO1(void){
    
    // SLCT 0x0; 
    CLCSELECT = 0x0;
    // LCG1POL inverted; LCG2POL not_inverted; LCG3POL not_inverted; LCG4POL inverted; LCPOL not_inverted; 
    CLCnPOL = 0x9;
    // LCD1S CLCIN2 (CLCIN2PPS); 
    CLCnSEL0 = 0x2;
    // LCD2S CLCIN0 (CLCIN0PPS); 
    CLCnSEL1 = 0x0;
    // LCD3S FOSC; 
    CLCnSEL2 = 0x4;
    // LCD4S CLC2_OUT; 
    CLCnSEL3 = 0x1D;
    // LCG1D1N disabled; LCG1D1T disabled; LCG1D2N disabled; LCG1D2T disabled; LCG1D3N disabled; LCG1D3T disabled; LCG1D4N disabled; LCG1D4T disabled; 
    CLCnGLS0 = 0x0;
    // LCG2D1N disabled; LCG2D1T disabled; LCG2D2N disabled; LCG2D2T enabled; LCG2D3N disabled; LCG2D3T disabled; LCG2D4N disabled; LCG2D4T disabled; 
    CLCnGLS1 = 0x8;
    // LCG3D1N disabled; LCG3D1T disabled; LCG3D2N disabled; LCG3D2T disabled; LCG3D3N disabled; LCG3D3T enabled; LCG3D4N disabled; LCG3D4T disabled; 
    CLCnGLS2 = 0x20;
    // LCG4D1N disabled; LCG4D1T disabled; LCG4D2N disabled; LCG4D2T disabled; LCG4D3N disabled; LCG4D3T disabled; LCG4D4N disabled; LCG4D4T enabled; 
    CLCnGLS3 = 0x80;
    // LCOUT 0x00; 
    CLCDATA = 0x0;
    // LCMODE 4-input AND; LCINTN enabled; LCINTP disabled; LCEN enabled; 
    CLCnCON = 0x8A;

    // Clear the CLC interrupt flag
    PIR2bits.CLC1IF = 0;
    //Configure interrupt handlers
    CLC1_CLCI_SetInterruptHandler(CLC1_DefaultCLCI_ISR);
    // Enabling CLC1 interrupt.
    PIE2bits.CLC1IE = 0;
}
void CLC1_Initialize_CLCNCO2(void){
    
    // SLCT 0x0; 
    CLCSELECT = 0x0;
    // LCG1POL inverted; LCG2POL not_inverted; LCG3POL not_inverted; LCG4POL inverted; LCPOL not_inverted; 
    CLCnPOL = 0x9;
    // LCD1S CLCIN0 (CLCIN0PPS); 
    CLCnSEL0 = 0x0;
    // LCD2S FOSC; 
    CLCnSEL1 = 0x4;
    // LCD3S CLC2_OUT; 
    CLCnSEL2 = 0x1D;
    // LCD4S CLC3_OUT; 
    CLCnSEL3 = 0x1E;
    // LCG1D1N disabled; LCG1D1T disabled; LCG1D2N disabled; LCG1D2T disabled; LCG1D3N disabled; LCG1D3T disabled; LCG1D4N disabled; LCG1D4T disabled; 
    CLCnGLS0 = 0x0;
    // LCG2D1N disabled; LCG2D1T disabled; LCG2D2N disabled; LCG2D2T enabled; LCG2D3N disabled; LCG2D3T disabled; LCG2D4N disabled; LCG2D4T disabled; 
    CLCnGLS1 = 0x8;
    // LCG3D1N disabled; LCG3D1T disabled; LCG3D2N disabled; LCG3D2T disabled; LCG3D3N disabled; LCG3D3T enabled; LCG3D4N disabled; LCG3D4T disabled; 
    CLCnGLS2 = 0x20;
    // LCG4D1N disabled; LCG4D1T disabled; LCG4D2N disabled; LCG4D2T disabled; LCG4D3N disabled; LCG4D3T disabled; LCG4D4N disabled; LCG4D4T enabled; 
    CLCnGLS3 = 0x80;
    // LCOUT 0x00; 
    CLCDATA = 0x0;
    // LCMODE 4-input AND; LCINTN disabled; LCINTP disabled; LCEN enabled; 
    CLCnCON = 0x82;

    // Clear the CLC interrupt flag
    PIR2bits.CLC1IF = 0;
    //Configure interrupt handlers
    CLC1_CLCI_SetInterruptHandler(CLC1_DefaultCLCI_ISR);
    // Enabling CLC1 interrupt.
    PIE2bits.CLC1IE = 0;
}
void CLC1_Initialize_CLCNCO3(void){
    
    // SLCT 0x0; 
    CLCSELECT = 0x0;
    // LCG1POL inverted; LCG2POL not_inverted; LCG3POL not_inverted; LCG4POL inverted; LCPOL not_inverted; 
    CLCnPOL = 0x9;
    // LCD1S CLCIN0 (CLCIN0PPS); 
    CLCnSEL0 = 0x0;
    // LCD2S NCO1_OUT; 
    CLCnSEL1 = 0x18;
    // LCD3S CLC2_OUT; 
    CLCnSEL2 = 0x1D;
    // LCD4S CLC3_OUT; 
    CLCnSEL3 = 0x1E;
    // LCG1D1N disabled; LCG1D1T disabled; LCG1D2N disabled; LCG1D2T disabled; LCG1D3N disabled; LCG1D3T disabled; LCG1D4N disabled; LCG1D4T disabled; 
    CLCnGLS0 = 0x0;
    // LCG2D1N disabled; LCG2D1T disabled; LCG2D2N disabled; LCG2D2T enabled; LCG2D3N disabled; LCG2D3T disabled; LCG2D4N disabled; LCG2D4T disabled; 
    CLCnGLS1 = 0x8;
    // LCG3D1N disabled; LCG3D1T disabled; LCG3D2N disabled; LCG3D2T disabled; LCG3D3N disabled; LCG3D3T enabled; LCG3D4N disabled; LCG3D4T disabled; 
    CLCnGLS2 = 0x20;
    // LCG4D1N disabled; LCG4D1T disabled; LCG4D2N disabled; LCG4D2T disabled; LCG4D3N disabled; LCG4D3T disabled; LCG4D4N disabled; LCG4D4T enabled; 
    CLCnGLS3 = 0x80;
    // LCOUT 0x00; 
    CLCDATA = 0x0;
    // LCMODE 4-input AND; LCINTN disabled; LCINTP disabled; LCEN enabled; 
    CLCnCON = 0x82;

    // Clear the CLC interrupt flag
    PIR2bits.CLC1IF = 0;
    //Configure interrupt handlers
    CLC1_CLCI_SetInterruptHandler(CLC1_DefaultCLCI_ISR);
    // Enabling CLC1 interrupt.
    PIE2bits.CLC1IE = 0;
}
void CLC1_CLCI_SetInterruptHandler(void (* InterruptHandler)(void)){
    CLC1_CLCI_InterruptHandler = InterruptHandler;
}
static void CLC1_DefaultCLCI_ISR(void){
    //Add your interrupt code here or
    //Use CLC1_CLCI_SetInterruptHandler() function to use Custom ISR
}

    //CLC2 Functions and Declarations

void CLC2_Initialize(void){
    
    // SLCT 0x1; 
    CLCSELECT = 0x1;
    // LCG1POL not_inverted; LCG2POL inverted; LCG3POL not_inverted; LCG4POL not_inverted; LCPOL not_inverted; 
    CLCnPOL = 0x2;
    // LCD1S CLCIN0 (CLCIN0PPS); 
    CLCnSEL0 = 0x0;
    // LCD2S CLCIN2 (CLCIN2PPS); 
    CLCnSEL1 = 0x2;
    // LCD3S CLCIN1 (CLCIN1PPS); 
    CLCnSEL2 = 0x1;
    // LCD4S CLCIN0 (CLCIN0PPS); 
    CLCnSEL3 = 0x0;
    // LCG1D1N disabled; LCG1D1T enabled; LCG1D2N disabled; LCG1D2T disabled; LCG1D3N disabled; LCG1D3T disabled; LCG1D4N disabled; LCG1D4T disabled; 
    CLCnGLS0 = 0x2;
    // LCG2D1N disabled; LCG2D1T disabled; LCG2D2N disabled; LCG2D2T disabled; LCG2D3N disabled; LCG2D3T disabled; LCG2D4N disabled; LCG2D4T disabled; 
    CLCnGLS1 = 0x0;
    // LCG3D1N disabled; LCG3D1T disabled; LCG3D2N disabled; LCG3D2T disabled; LCG3D3N disabled; LCG3D3T enabled; LCG3D4N disabled; LCG3D4T disabled; 
    CLCnGLS2 = 0x20;
    // LCG4D1N disabled; LCG4D1T disabled; LCG4D2N disabled; LCG4D2T disabled; LCG4D3N disabled; LCG4D3T disabled; LCG4D4N disabled; LCG4D4T disabled; 
    CLCnGLS3 = 0x0;
    // LCOUT 0x00; 
    CLCDATA = 0x0;
    // LCMODE 2-input D flip-flop with R; LCINTN disabled; LCINTP disabled; LCEN enabled; 
    CLCnCON = 0x85;

}
void CLC2_Initialize_CLCNCO1(void){
    
    // SLCT 0x1; 
    CLCSELECT = 0x1;
    // LCG1POL not_inverted; LCG2POL inverted; LCG3POL not_inverted; LCG4POL not_inverted; LCPOL not_inverted; 
    CLCnPOL = 0x2;
    // LCD1S CLCIN0 (CLCIN0PPS); 
    CLCnSEL0 = 0x0;
    // LCD2S CLCIN2 (CLCIN2PPS); 
    CLCnSEL1 = 0x2;
    // LCD3S CLCIN1 (CLCIN1PPS); 
    CLCnSEL2 = 0x1;
    // LCD4S CLCIN0 (CLCIN0PPS); 
    CLCnSEL3 = 0x0;
    // LCG1D1N disabled; LCG1D1T enabled; LCG1D2N disabled; LCG1D2T disabled; LCG1D3N disabled; LCG1D3T disabled; LCG1D4N disabled; LCG1D4T disabled; 
    CLCnGLS0 = 0x2;
    // LCG2D1N disabled; LCG2D1T disabled; LCG2D2N disabled; LCG2D2T disabled; LCG2D3N disabled; LCG2D3T disabled; LCG2D4N disabled; LCG2D4T disabled; 
    CLCnGLS1 = 0x0;
    // LCG3D1N disabled; LCG3D1T disabled; LCG3D2N disabled; LCG3D2T disabled; LCG3D3N disabled; LCG3D3T enabled; LCG3D4N disabled; LCG3D4T disabled; 
    CLCnGLS2 = 0x20;
    // LCG4D1N disabled; LCG4D1T disabled; LCG4D2N disabled; LCG4D2T disabled; LCG4D3N disabled; LCG4D3T disabled; LCG4D4N disabled; LCG4D4T disabled; 
    CLCnGLS3 = 0x0;
    // LCOUT 0x00; 
    CLCDATA = 0x0;
    // LCMODE 2-input D flip-flop with R; LCINTN disabled; LCINTP disabled; LCEN enabled; 
    CLCnCON = 0x85;

}
void CLC2_Initialize_CLCNCO2(void){
    
    // SLCT 0x1; 
    CLCSELECT = 0x1;
    // LCG1POL not_inverted; LCG2POL inverted; LCG3POL not_inverted; LCG4POL inverted; LCPOL not_inverted; 
    CLCnPOL = 0xA;
    // LCD1S CLCIN0 (CLCIN0PPS); 
    CLCnSEL0 = 0x0;
    // LCD2S CLCIN0 (CLCIN0PPS); 
    CLCnSEL1 = 0x0;
    // LCD3S CLCIN2 (CLCIN2PPS); 
    CLCnSEL2 = 0x2;
    // LCD4S CLCIN0 (CLCIN0PPS); 
    CLCnSEL3 = 0x0;
    // LCG1D1N disabled; LCG1D1T enabled; LCG1D2N disabled; LCG1D2T disabled; LCG1D3N disabled; LCG1D3T disabled; LCG1D4N disabled; LCG1D4T disabled; 
    CLCnGLS0 = 0x2;
    // LCG2D1N disabled; LCG2D1T disabled; LCG2D2N disabled; LCG2D2T disabled; LCG2D3N disabled; LCG2D3T disabled; LCG2D4N disabled; LCG2D4T disabled; 
    CLCnGLS1 = 0x0;
    // LCG3D1N disabled; LCG3D1T disabled; LCG3D2N disabled; LCG3D2T disabled; LCG3D3N disabled; LCG3D3T disabled; LCG3D4N disabled; LCG3D4T disabled; 
    CLCnGLS2 = 0x0;
    // LCG4D1N disabled; LCG4D1T disabled; LCG4D2N disabled; LCG4D2T disabled; LCG4D3N disabled; LCG4D3T disabled; LCG4D4N disabled; LCG4D4T disabled; 
    CLCnGLS3 = 0x0;
    // LCOUT 0x00; 
    CLCDATA = 0x0;
    // LCMODE 2-input D flip-flop with R; LCINTN disabled; LCINTP disabled; LCEN enabled; 
    CLCnCON = 0x85;

}
void CLC2_Initialize_CLCNCO3(void){
    
    // SLCT 0x1; 
    CLCSELECT = 0x1;
    // LCG1POL not_inverted; LCG2POL inverted; LCG3POL not_inverted; LCG4POL inverted; LCPOL not_inverted; 
    CLCnPOL = 0xA;
    // LCD1S CLCIN0 (CLCIN0PPS); 
    CLCnSEL0 = 0x0;
    // LCD2S CLCIN0 (CLCIN0PPS); 
    CLCnSEL1 = 0x0;
    // LCD3S CLCIN2 (CLCIN2PPS); 
    CLCnSEL2 = 0x2;
    // LCD4S CLCIN0 (CLCIN0PPS); 
    CLCnSEL3 = 0x0;
    // LCG1D1N disabled; LCG1D1T enabled; LCG1D2N disabled; LCG1D2T disabled; LCG1D3N disabled; LCG1D3T disabled; LCG1D4N disabled; LCG1D4T disabled; 
    CLCnGLS0 = 0x2;
    // LCG2D1N disabled; LCG2D1T disabled; LCG2D2N disabled; LCG2D2T disabled; LCG2D3N disabled; LCG2D3T disabled; LCG2D4N disabled; LCG2D4T disabled; 
    CLCnGLS1 = 0x0;
    // LCG3D1N disabled; LCG3D1T disabled; LCG3D2N disabled; LCG3D2T disabled; LCG3D3N disabled; LCG3D3T disabled; LCG3D4N disabled; LCG3D4T disabled; 
    CLCnGLS2 = 0x0;
    // LCG4D1N disabled; LCG4D1T disabled; LCG4D2N disabled; LCG4D2T disabled; LCG4D3N disabled; LCG4D3T disabled; LCG4D4N disabled; LCG4D4T disabled; 
    CLCnGLS3 = 0x0;
    // LCOUT 0x00; 
    CLCDATA = 0x0;
    // LCMODE 2-input D flip-flop with R; LCINTN disabled; LCINTP disabled; LCEN enabled; 
    CLCnCON = 0x85;

}

    //CLC3 Functions and Declarations

void CLC3_Initialize(void){
    // SLCT 0x2; 
    CLCSELECT = 0x2;
    // LCG1POL inverted; LCG2POL not_inverted; LCG3POL not_inverted; LCG4POL not_inverted; LCPOL not_inverted; 
    CLCnPOL = 0x1;
    // LCD1S CLCIN0 (CLCIN0PPS); 
    CLCnSEL0 = 0x0;
    // LCD2S CLC2_OUT; 
    CLCnSEL1 = 0x1D;
    // LCD3S CLCIN3 (CLCIN3PPS); 
    CLCnSEL2 = 0x3;
    // LCD4S CLCIN0 (CLCIN0PPS); 
    CLCnSEL3 = 0x0;
    // LCG1D1N disabled; LCG1D1T enabled; LCG1D2N disabled; LCG1D2T disabled; LCG1D3N disabled; LCG1D3T disabled; LCG1D4N disabled; LCG1D4T disabled; 
    CLCnGLS0 = 0x2;
    // LCG2D1N disabled; LCG2D1T disabled; LCG2D2N disabled; LCG2D2T enabled; LCG2D3N disabled; LCG2D3T disabled; LCG2D4N disabled; LCG2D4T disabled; 
    CLCnGLS1 = 0x8;
    // LCG3D1N disabled; LCG3D1T disabled; LCG3D2N disabled; LCG3D2T disabled; LCG3D3N disabled; LCG3D3T disabled; LCG3D4N disabled; LCG3D4T disabled; 
    CLCnGLS2 = 0x0;
    // LCG4D1N disabled; LCG4D1T disabled; LCG4D2N disabled; LCG4D2T disabled; LCG4D3N disabled; LCG4D3T disabled; LCG4D4N disabled; LCG4D4T disabled; 
    CLCnGLS3 = 0x0;
    // LCOUT 0x00; 
    CLCDATA = 0x0;
    // LCMODE 2-input D flip-flop with R; LCINTN disabled; LCINTP disabled; LCEN enabled; 
    CLCnCON = 0x85;

}
void CLC3_Initialize_CLCNCO2(void){
    
    // SLCT 0x2; 
    CLCSELECT = 0x2;
    // LCG1POL inverted; LCG2POL not_inverted; LCG3POL not_inverted; LCG4POL not_inverted; LCPOL not_inverted; 
    CLCnPOL = 0x1;
    // LCD1S CLCIN0 (CLCIN0PPS); 
    CLCnSEL0 = 0x0;
    // LCD2S CLC2_OUT; 
    CLCnSEL1 = 0x1D;
    // LCD3S CLCIN3 (CLCIN3PPS); 
    CLCnSEL2 = 0x3;
    // LCD4S CLCIN0 (CLCIN0PPS); 
    CLCnSEL3 = 0x0;
    // LCG1D1N disabled; LCG1D1T enabled; LCG1D2N disabled; LCG1D2T disabled; LCG1D3N disabled; LCG1D3T disabled; LCG1D4N disabled; LCG1D4T disabled; 
    CLCnGLS0 = 0x2;
    // LCG2D1N disabled; LCG2D1T disabled; LCG2D2N disabled; LCG2D2T enabled; LCG2D3N disabled; LCG2D3T disabled; LCG2D4N disabled; LCG2D4T disabled; 
    CLCnGLS1 = 0x8;
    // LCG3D1N disabled; LCG3D1T disabled; LCG3D2N disabled; LCG3D2T disabled; LCG3D3N disabled; LCG3D3T disabled; LCG3D4N disabled; LCG3D4T disabled; 
    CLCnGLS2 = 0x0;
    // LCG4D1N disabled; LCG4D1T disabled; LCG4D2N disabled; LCG4D2T disabled; LCG4D3N disabled; LCG4D3T disabled; LCG4D4N disabled; LCG4D4T disabled; 
    CLCnGLS3 = 0x0;
    // LCOUT 0x00; 
    CLCDATA = 0x0;
    // LCMODE 2-input D flip-flop with R; LCINTN disabled; LCINTP disabled; LCEN enabled; 
    CLCnCON = 0x85;

}
void CLC3_Initialize_CLCNCO3(void){
    
    // SLCT 0x2; 
    CLCSELECT = 0x2;
    // LCG1POL inverted; LCG2POL not_inverted; LCG3POL not_inverted; LCG4POL not_inverted; LCPOL not_inverted; 
    CLCnPOL = 0x1;
    // LCD1S CLCIN0 (CLCIN0PPS); 
    CLCnSEL0 = 0x0;
    // LCD2S CLC2_OUT; 
    CLCnSEL1 = 0x1D;
    // LCD3S CLCIN3 (CLCIN3PPS); 
    CLCnSEL2 = 0x3;
    // LCD4S CLCIN0 (CLCIN0PPS); 
    CLCnSEL3 = 0x0;
    // LCG1D1N disabled; LCG1D1T enabled; LCG1D2N disabled; LCG1D2T disabled; LCG1D3N disabled; LCG1D3T disabled; LCG1D4N disabled; LCG1D4T disabled; 
    CLCnGLS0 = 0x2;
    // LCG2D1N disabled; LCG2D1T disabled; LCG2D2N disabled; LCG2D2T enabled; LCG2D3N disabled; LCG2D3T disabled; LCG2D4N disabled; LCG2D4T disabled; 
    CLCnGLS1 = 0x8;
    // LCG3D1N disabled; LCG3D1T disabled; LCG3D2N disabled; LCG3D2T disabled; LCG3D3N disabled; LCG3D3T disabled; LCG3D4N disabled; LCG3D4T disabled; 
    CLCnGLS2 = 0x0;
    // LCG4D1N disabled; LCG4D1T disabled; LCG4D2N disabled; LCG4D2T disabled; LCG4D3N disabled; LCG4D3T disabled; LCG4D4N disabled; LCG4D4T disabled; 
    CLCnGLS3 = 0x0;
    // LCOUT 0x00; 
    CLCDATA = 0x0;
    // LCMODE 2-input D flip-flop with R; LCINTN disabled; LCINTP disabled; LCEN enabled; 
    CLCnCON = 0x85;

}

    //NCO1 Functions and Declarations


void NCO1_Initialize_CLCNCO1_CLCNCO2(void){
    //NPWS 1_clk; NCKS CLC1_OUT; 
    NCO1CLK = 0xA;
    //NCOACC 0x0; 
    NCO1ACCU = 0x0;
    //NCOACC 0x0; 
    NCO1ACCH = 0x0;
    //NCOACC 0x0; 
    NCO1ACCL = 0x0;
    //NCOINC 0; 
    NCO1INCU = 0x0;
    //NCOINC 0; 
    NCO1INCH = 0x0;
    //NCOINC 1; 
    NCO1INCL = 0x1;
    //NEN disabled; NPOL active_hi; NPFM FDC_mode; 
    NCO1CON = 0x0;
}
void NCO1_Initialize_CLCNCO3(void){
    //NPWS 1_clk; NCKS FOSC; 
    NCO1CLK = 0x0;
    //NCOACC 0x0; 
    NCO1ACCU = 0x0;
    //NCOACC 0x0; 
    NCO1ACCH = 0x0;
    //NCOACC 0x0; 
    NCO1ACCL = 0x0;
    //NCOINC 0; 
    NCO1INCU = 0x0;
    //NCOINC 130; 
    NCO1INCH = 0x82;
    //NCOINC 143; 
    NCO1INCL = 0x8F;
    //NEN enabled; NPOL active_hi; NPFM FDC_mode; 
    NCO1CON = 0x80;
}

    //CCP1 Functions and Declarations
void CCP1_Initialize(void) {
    // Set the CCP1 to the options selected in the User Interface
    
    // CCPM 4th rising edge; EN disabled; FMT right_aligned; 
    CCP1CON = 0x6;
    
    // CTS CCP1PPS; 
    CCP1CAP = 0x0;
    
    // CCPRH 0; 
    CCPR1H = 0x0;
    
    // CCPRL 0; 
    CCPR1L = 0x0;


    // Selecting Timer 1
    CCPTMRS0bits.C1TSEL = 0x1;
}
uint16_t CCP1_CaptureRead(void){
    CCPR1_PERIOD_REG_T module;

    // Copy captured value.
    module.ccpr1l = CCPR1L;
    module.ccpr1h = CCPR1H;
    
    // Return 16bit captured value
    return module.ccpr1_16Bit;
}

    //CCP2 Functions and Declarations
void CCP2_Initialize(void) {
    // Set the CCP2 to the options selected in the User Interface
    
    // CCPM Every edge; EN disabled; FMT right_aligned; 
    CCP2CON = 0x3;
    
    // CTS CCP2PPS; 
    CCP2CAP = 0x0;
    
    // CCPRH 0; 
    CCPR2H = 0x0;
    
    // CCPRL 0; 
    CCPR2L = 0x0;


    // Selecting Timer 1
    CCPTMRS0bits.C2TSEL = 0x1;
}
uint16_t CCP2_CaptureRead(void){
    CCPR2_PERIOD_REG_T module;

    // Copy captured value.
    module.ccpr2l = CCPR2L;
    module.ccpr2h = CCPR2H;
    
    // Return 16bit captured value
    return module.ccpr2_16Bit;
}

//Initialization Functions

void Timer1_Gate_Initialize(void){
    T1GPPS = 0xD; //RB5->TMR1:T1G;
    
    Timer1_Initialize_Timer1Gate(); 
}
void CLC_NCO1_Initialize(void){
    T1CON = 0x0;
    NCO1_Initialize_CLCNCO1_CLCNCO2();
    CLC1_Initialize_CLCNCO1();
    CLC2_Initialize_CLCNCO1();
    Timer1_Initialize_CLCNCO1();
    CLC_NCO1_Pins_PPS();
    setup_for_new_measurement_CLCNCO1(); 
}
void CLC_NCO2_Initialize(void){
    T1CON = 0x0;//
    NCO1_Initialize_CLCNCO1_CLCNCO2();//
    CLC1_Initialize_CLCNCO2();
    CLC2_Initialize_CLCNCO2();
    CLC3_Initialize_CLCNCO2();
    Timer1_Initialize_CLCNCO2();
    CLC_NCO2_Pins_PPS();
    setup_for_new_measurement_CLCNCO2(); 
}
void CLC_NCO3_Initialize(void){
    T1CON = 0x0;
    NCO1_Initialize_CLCNCO3();
    CLC1_Initialize_CLCNCO3();
    CLC2_Initialize_CLCNCO3();
    CLC3_Initialize_CLCNCO3();
    Timer0_Initialize_CLCNCO3();
    Timer1_Initialize_CLCNCO3();
    CLC_NCO3_Pins_PPS();
    setup_for_new_measurement_CLCNCO3();
}
void CCP_Initialize(void){
    
    CCP1_Initialize();
    CCP2_Initialize();        
    
    CCP2PPS = 0xD;  //RB5->CCP2:CCP2;
    RB5PPS = 0x0A;  //RB5->CCP1:CCP1;
    CCP1PPS = 0xD;  //RB5->CCP1:CCP1;
    
    
    PIR2bits.CCP1IF = 0;
    PIR2bits.CCP2IF = 0;
    
}
void IOC_w_Timer_Initialize(void){
    IOCBP = 0x20;
    IOCBN = 0x20;    
    Timer0_Initialize();
}
void IOC_wo_Timer_Initialize(void){
    IOCBP = 0x20;
    IOCBN = 0x20;
}

//Pins and PPS Functions

void CLC_NCO1_Pins_PPS(void){
    TRISA = 0xDF;//
    TRISC = 0xBB;//
    
    ANSELA = 0xD8;//
    ANSELC = 0x3A;//

    RA5PPS = 0x01;  //RA5->CLC1:CLC1OUT;
    RC2PPS = 0x02;  //RC2->CLC2:CLC2OUT;
    T1CKIPPS = 0x10; //RC0->TMR1:T1CKI;
    T1GPPS = 0xD; //RB5->TMR1:T1G;
    CLCIN0PPS = 0x2; //RA2->CLC1:CLCIN0;
    CLCIN1PPS = 0x1; //RA1->CLC2:CLCIN1;
}
void CLC_NCO2_Pins_PPS(void){
    TRISA = 0xDF;
    TRISB = 0xFD;
    TRISC = 0xBB;
    
    ANSELA = 0xDA;
    ANSELB = 0xD1;
    ANSELC = 0x3B;
    
    RA5PPS = 0x01;  //RA5->CLC1:CLC1OUT;
    RC2PPS = 0x02;  //RC2->CLC2:CLC2OUT;
    T1CKIPPS = 0x10; //RC0->TMR1:T1CKI;
    T1GPPS = 0xD; //RB5->TMR1:T1G;
    CLCIN0PPS = 0x2; //RA2->CLC1:CLCIN0;
    CLCIN1PPS = 0x1; //RA1->CLC2:CLCIN1;
}
void CLC_NCO3_Pins_PPS(void){
    TRISA = 0xDF;
    TRISB = 0xFD;
    TRISC = 0xBB;
    
    ANSELA = 0xDA;
    ANSELB = 0xDD;
    ANSELC = 0x3B;
    
    RA5PPS = 0x01;  //RA5->CLC1:CLC1OUT;
    RC2PPS = 0x02;  //RC2->CLC2:CLC2OUT;
    RB1PPS = 0x03;  //RB1->CLC3:CLC3OUT;
    CLCIN0PPS = 0x2; //RA2->CLC1:CLCIN0;
}

//Reset-Clear Functions

void TMR0_Reset(void){
    TMR0H = 0xFF;
    TMR0L = 0x0;
    T0CON1 = 0x0;
    T0CON0 = 0x0;
}
void TMR1_Reset(void){
    T1GCON = 0x0;
    T1GATE = 0x0;
    T1CLK = 0x0;
    TMR1H = 0x0;
    TMR1L = 0x0;
}
void CLC1_Reset(void){
    CLCSELECT = 0x0;
    CLCnPOL = 0x0;
    CLCnSEL0 = 0x0;
    CLCnSEL1 = 0x0;
    CLCnSEL2 = 0x0;
    CLCnSEL3 = 0x0;
    CLCnGLS0 = 0x0;
    CLCnGLS1 = 0x0;
    CLCnGLS2 = 0x0;
    CLCnGLS3 = 0x0;
    CLCDATA = 0x0;
    CLCnCON = 0x0;
}
void CLC2_Reset(void){
    CLCSELECT = 0x1;
    CLCnPOL = 0x0;
    CLCnSEL0 = 0x0;
    CLCnSEL1 = 0x0;
    CLCnSEL2 = 0x0;
    CLCnSEL3 = 0x0;
    CLCnGLS0 = 0x0;
    CLCnGLS1 = 0x0;
    CLCnGLS2 = 0x0;
    CLCnGLS3 = 0x0;
    CLCDATA = 0x0;
    CLCnCON = 0x0;
}
void CLC3_Reset(void){
    CLCSELECT = 0x2;
    CLCnPOL = 0x0;
    CLCnSEL0 = 0x0;
    CLCnSEL1 = 0x0;
    CLCnSEL2 = 0x0;
    CLCnSEL3 = 0x0;
    CLCnGLS0 = 0x0;
    CLCnGLS1 = 0x0;
    CLCnGLS2 = 0x0;
    CLCnGLS3 = 0x0;
    CLCDATA = 0x0;
    CLCnCON = 0x0;
}
void IOC_Reset(void){
    IOCBP = 0x00;
    IOCBN = 0x00;
}
void Pins_PPS_Reset(void){
    PIN_MANAGER_Initialize();
    RA5PPS = 0x0;  //Reset RA5
    RB1PPS = 0x0;  //Reset RB1
    RC2PPS = 0x0;  //Reset RC2
    T1CKIPPS = 0x10; //Reset T1CK
    T1GPPS = 0xD; //Reset T1G
    CLCIN0PPS = 0x0; //Reset CLCIN0
    CLCIN1PPS = 0x1; //Reset CLCIN1
}