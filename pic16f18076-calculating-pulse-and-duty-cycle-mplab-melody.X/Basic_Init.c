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

void Timer1_Gate_Initialize(void){
    T1GPPS = 0xD; //RB5->TMR1:T1G;
    
    Timer1_Initialize_Timer1Gate(); 
}

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

static void (*CLC1_CLCI_InterruptHandler)(void);
static void CLC1_DefaultCLCI_ISR(void);

void NCO1_Initialize(void){

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
void CLC1_CLCI_SetInterruptHandler(void (* InterruptHandler)(void)){
    CLC1_CLCI_InterruptHandler = InterruptHandler;
}
static void CLC1_DefaultCLCI_ISR(void){
    //Add your interrupt code here or
    //Use CLC1_CLCI_SetInterruptHandler() function to use Custom ISR
}




void TMR0_Reset(void){
    //insert default values for initialization when second CLCNCO3 gets included
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

void IOC_Reset(void){
    IOCBP = 0x00;
    IOCBN = 0x00;
}

void CCP_Initialize(void){
    
}
void CCP_Deinitialize(void){
    
}
