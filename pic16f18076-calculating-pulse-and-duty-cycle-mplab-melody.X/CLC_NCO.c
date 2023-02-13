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