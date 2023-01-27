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

void send_NCO_measurement(void){
    EUSART1_sendInt(NCO1ACCU);
    EUSART1_sendInt(NCO1ACCH);
    EUSART1_sendInt(NCO1ACCL);
}
void send_TMR1_measurement(void){
    EUSART1_sendInt(TMR1H);
    EUSART1_sendInt(TMR1L);
}
void clear_NCO_Accumulator(void){
    // Clear NCO1 Accumulator
    NCO1ACCU = 0x00;
    NCO1ACCH = 0x00;
    NCO1ACCL = 0x00;
}
void clear_TMR1_Value(void){
    TMR1H = 0x00;
    TMR1L = 0x01;
}
void send_DC_Calculation(void){
    //calculate the duty cycle and output as an 8-bit value, 0-255 = 0-100%, e.g. 127 = 50%
    uint24_t NCO_val = 0;
    uint24_t TMR1_val = 0;
    uint24_t duty_cycle = 0;
    
    NCO_val = ((NCO1ACCH << 8) + NCO1ACCL);
    TMR1_val = ((TMR1H << 8) + TMR1L);

    duty_cycle = (NCO_val << 8)/TMR1_val;
    
    EUSART1_sendInt(duty_cycle);    
}
void send_measurement(void){
    EUSART1_sendString("\nPULSE:"); //NCO
    send_NCO_measurement();
    EUSART1_sendString("\nPD:"); //Timer1
    send_TMR1_measurement();
    EUSART1_sendString("\nDC:");
    send_DC_Calculation();
} 
void clear_flags(void){
    PIR1bits.TMR1IF = 0;
    PIR2bits.NCO1IF = 0; 
    uint16_t cycles = 0;
}
void setup_for_new_measurement(void){
    clear_NCO_Accumulator();    
    clear_TMR1_Value();
    clear_flags();
    Timer1_Start();
    NCO1CONbits.EN = 1; //NCO enable
}
void CLC_NCO1_Initialize(void){
    T1CON = 0x0;
    NCO1_Initialize();
    CLC1_Initialize();
    CLC2_Initialize();
    Timer1_Initialize_CLCNCO1();
    ANSELAbits.ANSA1 = 0;
    ANSELAbits.ANSA2 = 0;
    TRISAbits.TRISA5 = 0;
    ANSELAbits.ANSA5 = 0;
    ANSELCbits.ANSC0 = 0;
    TRISCbits.TRISC2 = 0;
    ANSELCbits.ANSC2 = 0;
    RA5PPS = 0x01;  //RA5->CLC1:CLC1OUT;
    RC2PPS = 0x02;  //RC2->CLC2:CLC2OUT;
    T1CKIPPS = 0x10; //RC0->TMR1:T1CKI;
    T1GPPS = 0xD; //RB5->TMR1:T1G;
    CLCIN0PPS = 0x2; //RA2->CLC1:CLCIN0;
    CLCIN1PPS = 0x1; //RA1->CLC2:CLCIN1;
    setup_for_new_measurement(); 
}
uint16_t cycles = 0;

void CLC_NCO1_Calculations(void){
 
        if (PIR1bits.TMR1IF || PIR2bits.NCO1IF || cycles > 99){
            //EUSART1_sendString("\ntest1");
            if (PIR1bits.TMR1IF){
                //EUSART1_sendString("\ntest2");
                NCO1CONbits.EN = 0;
                Timer1_Stop();
                
                send_measurement();
                setup_for_new_measurement();
            }
            else if (PIR2bits.NCO1IF){
                //EUSART1_sendString("\ntest3");
                NCO1CONbits.EN = 0;
                Timer1_Stop();
                
                send_measurement();
                setup_for_new_measurement();
            }
            else{
                //EUSART1_sendString("\ntest4");
                NCO1CONbits.EN = 0;
                Timer1_Stop();
                
                send_measurement();
                setup_for_new_measurement();
            }
        }
        else{
            //EUSART1_sendString("\n");
            //EUSART1_sendInt(cycles);
            cycles++;
        }
       
       __delay_ms(1);
}
void CLC_NCO2_Calculations(void){

}
void CLC_NCO3_Calculations(void){

}