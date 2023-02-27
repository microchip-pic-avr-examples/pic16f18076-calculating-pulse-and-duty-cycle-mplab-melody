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
void MAX_TMR1_Value(void){
    TMR1H = 0xFF;
    TMR1L = 0xFF;
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
void send_DC_Calculation_MT(void){
    //calculate the duty cycle and output as an 8-bit value, 0-255 = 0-100%, e.g. 127 = 50%
    uint24_t NCO_val = 0;
    uint24_t TMR1_val = 0;
    uint24_t duty_cycle = 0;
    
    TMR1_val = 0x3F;
    NCO_val = ((NCO1ACCH << 8) + NCO1ACCL); //CONFIRMED
    
    duty_cycle = NCO_val/TMR1_val;
    
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
void send_measurement_MT(void){
    EUSART1_sendString("\nPULSE:"); //NCO
    send_NCO_measurement();
    EUSART1_sendString("\nPD:"); //Timer1
    send_TMR1_measurement();
    EUSART1_sendString("\nDC:");
    send_DC_Calculation_MT();
}
void clear_flags(void){
    PIR1bits.TMR1IF = 0;
    PIR2bits.NCO1IF = 0; 
    uint16_t cycles = 0;
}
void reset_CLC2_CLC3(void){
    CLCSELECT = 0x1;
    CLCnPOLbits.G3POL = HIGH;
    CLCSELECT = 0x2;
    CLCnPOLbits.G3POL = HIGH;
    CLCnPOLbits.G3POL = LOW;
    CLCSELECT = 0x1;
    CLCnPOLbits.G3POL = LOW;
}
void setup_for_new_measurement_CLCNCO1(void){
    clear_NCO_Accumulator();    
    clear_TMR1_Value();
    clear_flags();
    Timer1_Start();
    NCO1CONbits.EN = 1; //NCO enable
}
void setup_for_new_measurement_CLCNCO2_CLCNCO3(void){
    clear_NCO_Accumulator();    
    clear_TMR1_Value();
    clear_flags();
    reset_CLC2_CLC3();
    
    Timer1_Start();
    NCO1CONbits.EN = 1; //NCO enable
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
                setup_for_new_measurement_CLCNCO1();
            }
            else if (PIR2bits.NCO1IF){
                //EUSART1_sendString("\ntest3");
                NCO1CONbits.EN = 0;
                Timer1_Stop();
                
                send_measurement();
                setup_for_new_measurement_CLCNCO1();
            }
            else{
                //EUSART1_sendString("\ntest4");
                NCO1CONbits.EN = 0;
                Timer1_Stop();
                
                send_measurement();
                setup_for_new_measurement_CLCNCO1();
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
        if (PIR1bits.TMR1IF || PIR2bits.NCO1IF || cycles > 99){
//            EUSART1_sendString("\ntest1");
            if (PIR1bits.TMR1IF){
                NCO1CONbits.EN = 0;
                Timer1_Stop();
                MAX_TMR1_Value();
//                EUSART1_sendString("\ntest2");
                send_measurement_MT();
                setup_for_new_measurement_CLCNCO2_CLCNCO3();
            }
            else if (PIR2bits.NCO1IF){
                NCO1CONbits.EN = 0;
                Timer1_Stop();
//                EUSART1_sendString("\ntest3");
                send_measurement();
                setup_for_new_measurement_CLCNCO2_CLCNCO3();
            }
            else{
                NCO1CONbits.EN = 0;
                Timer1_Stop();
//                EUSART1_sendString("\ntest4");
                send_measurement();
                setup_for_new_measurement_CLCNCO2_CLCNCO3();
            }
        }

        else{
            cycles++;
        }
       __delay_ms(1); 
}
void CLC_NCO3_Calculations(void){

}