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

void send_NCO_measurement(void){                            // Send NCO Accumulator U/H/L bytes over UART 
    EUSART1_sendInt(NCO1ACCU);                              
    EUSART1_sendInt(NCO1ACCH);                              
    EUSART1_sendInt(NCO1ACCL);                              
}
void send_TMR0_measurement(void){                           // Send Timer0 H/L bytes over UART 
    EUSART1_sendInt(TMR0H);                                 
    EUSART1_sendInt(TMR0L);                                 
}
void send_TMR1_measurement(void){                           // Send Timer1 H/L bytes over UART  
    EUSART1_sendInt(TMR1H);                                 
    EUSART1_sendInt(TMR1L);                                 
}
void clear_NCO_Accumulator(void){                           // Clear NCO1 Accumulator U/H/L bytes                               
    NCO1ACCU = 0x00;                                        
    NCO1ACCH = 0x00;                                        
    NCO1ACCL = 0x00;                                        
}
void clear_TMR0_Value(void){                                // Clear Timer0 H/L bytes
    TMR0H = 0xFF;                                           
    TMR0L = 0x00;                                           
}
void clear_TMR1_Value(void){                                // Clear Timer1 H/L bytes  
    TMR1H = 0x00;                                           
    TMR1L = 0x01;                                           
}
void MAX_TMR1_Value(void){                                  // Set Maximum values to Timer1 H/L bytes 
    TMR1H = 0xFF;                                           
    TMR1L = 0xFF;                                           
}
void send_DC_Calculation_CLCNCO1_CLCNCO2(void){             // Calculate the duty cycle and output as an 8-bit value, 0-255 = 0-100%, e.g. 127 = 50%
    uint24_t NCO_val = 0;                                   // Initialize the NCO_val value
    uint24_t TMR1_val = 0;                                  // Initialize the TMR1_val value
    uint24_t duty_cycle = 0;                                // Initialize the duty_cycle value
    
    NCO_val = ((NCO1ACCH << 8) + NCO1ACCL);                 // Combine the NCOACCH/L bytes into a 16-bit value by left shifting the High byte by 8
    TMR1_val = ((TMR1H << 8) + TMR1L);                      // Combine the TMR1H/L bytes into a 16-bit value by left shifting the High byte by 8

    duty_cycle = (NCO_val << 8)/TMR1_val;                   // Calculate the duty cycle by left shifting the NCO_val by 8 (effectively multiplying by 256), then dividing by the TMR1_val
    
    EUSART1_sendInt(duty_cycle);                            // Send the duty cycle value over UART
}
void send_DC_Calculation_CLCNCO3(void){                     // Calculate the duty cycle and output as an 8-bit value, 0-255 = 0-100%, e.g. 127 = 50%
    uint24_t TMR0_val = 0;                                  // Initialize the TMR0_val value
    uint24_t TMR1_val = 0;                                  // Initialize the TMR1_val value
    uint24_t duty_cycle = 0;                                // Initialize the duty_cycle value
    
    TMR0_val = (TMR0L);                                     // Update the TMR0_val to equal the TMR0L value
    TMR1_val = ((TMR1H << 8) + TMR1L);                      // Combine the TMR1H/L bytes into a 16-bit value by left shifting the High byte by 8

    TMR0_val = (TMR0_val << 8);                             // Update the TMR0_val to equal the prior TMR0_val value left shifted by 8
    TMR1_val = (TMR1_val >> 6);                             // Update the TMR1_val to equal the prior TMR1_val value right shifted by 6
      
    if (PIR1bits.TMR1IF){                                   // Check if 
        TMR0_val = (TMR0L);                                 //
        TMR1_val = 0x01;                                    //
    } 
    
    duty_cycle = TMR0_val/TMR1_val;                         //
    
    EUSART1_sendInt(duty_cycle);                            // Send duty cycle value over UART
}
void send_DC_Calculation_MT(void){                          // Calculate the duty cycle and output as an 8-bit value, 0-255 = 0-100%, e.g. 127 = 50%
    uint24_t NCO_val = 0;                                   // Initialize the NCO_val value
    uint24_t TMR1_val = 0;                                  // Initialize the NCO_val value
    uint24_t duty_cycle = 0;                                // Initialize the NCO_val value
        
    TMR1_val = 0x3F;                                        //
    NCO_val = ((NCO1ACCH << 8) + NCO1ACCL); //CONFIRMED     //
    
    duty_cycle = NCO_val/TMR1_val;                          //
    
    EUSART1_sendInt(duty_cycle);                            // Send duty cycle value over UART
}
void send_measurement_CLCNCO1_CLCNCO2(void){                //
    EUSART1_sendString("\nPULSE:"); //NCO                   //
    send_NCO_measurement();                                 //
    EUSART1_sendString("\nPD:"); //Timer1                   //
    send_TMR1_measurement();                                //
    EUSART1_sendString("\nDC:");                            //
    send_DC_Calculation_CLCNCO1_CLCNCO2();                  //
}
void send_measurement_CLCNCO3(void){                        //
    EUSART1_sendString("\nPULSE:"); //NCO                   //
    send_TMR0_measurement();                                //
    EUSART1_sendString("\nPD:"); //Timer1                   //
    send_TMR1_measurement();                                //
    EUSART1_sendString("\nDC:");                            //
    send_DC_Calculation_CLCNCO3();                          //
}
void send_measurement_MT(void){                             //
    EUSART1_sendString("\nPULSE:"); //NCO                   //
    send_NCO_measurement();                                 //
    EUSART1_sendString("\nPD:"); //Timer1                   //
    send_TMR1_measurement();                                //
    EUSART1_sendString("\nDC:");                            //
    send_DC_Calculation_MT();                               //
}
void clear_flags_CLCNCO1_CLCNCO2(void){                     //
    PIR1bits.TMR1IF = 0;                                    //
    PIR2bits.NCO1IF = 0;                                    //
    uint16_t cycles = 0;                                    //
}
void clear_flags_CLCNCO3(void){                             //
    PIR1bits.TMR1IF = 0;                                    //
    PIR0bits.TMR0IF = 0;                                    //
    uint16_t cycles = 0;                                    //
}
void reset_CLC2_CLC3(void){                                 //
    CLCSELECT = 0x1;                                        //
    CLCnPOLbits.G3POL = HIGH;                               //
    CLCSELECT = 0x2;                                        //
    CLCnPOLbits.G3POL = HIGH;                               //
    CLCnPOLbits.G3POL = LOW;                                //
    CLCSELECT = 0x1;                                        //
    CLCnPOLbits.G3POL = LOW;                                //
}
void setup_for_new_measurement_CLCNCO1(void){               //
    clear_NCO_Accumulator();                                //
    clear_TMR1_Value();                                     //
    clear_flags_CLCNCO1_CLCNCO2();                          //
    Timer1_Start();                                         //
    NCO1CONbits.EN = 1; //NCO enable                        //
}   
void setup_for_new_measurement_CLCNCO2(void){               //
    clear_NCO_Accumulator();                                //
    clear_TMR1_Value();                                     //
    clear_flags_CLCNCO1_CLCNCO2();                          //
    reset_CLC2_CLC3();                                      //
    
    Timer1_Start();                                         //
    NCO1CONbits.EN = 1; //NCO enable                        //
}
void setup_for_new_measurement_CLCNCO3(void){               //
    clear_TMR0_Value();                                     //
    clear_TMR1_Value();                                     //
    clear_flags_CLCNCO3();                                  //
    reset_CLC2_CLC3();                                      //
            
    Timer0_Start();                                         //
    Timer1_Start();                                         //
}

uint16_t cycles = 0;                                        // Initialize the cycles value

void CLC_NCO1_Calculations(void){
    if (PIR1bits.TMR1IF || PIR2bits.NCO1IF || cycles > 99){ // Check that one of the following is true: Timer1 interrupt flag, NCO1 interrupt flag, cycles > 99
        if (PIR1bits.TMR1IF){                               // Check if Timer1 interrupt flag is high
            NCO1CONbits.EN = 0;                             // Stop NCO1
            Timer1_Stop();                                  // Stop Timer1

            send_measurement_CLCNCO1_CLCNCO2();             // Send measurement information over UART
            setup_for_new_measurement_CLCNCO1();            // Setup for the next measurement
        }
        else if (PIR2bits.NCO1IF){                          // Check if NCO1 interrupt flag is high
            NCO1CONbits.EN = 0;                             // Stop NCO1
            Timer1_Stop();                                  // Stop Timer1

            send_measurement_CLCNCO1_CLCNCO2();             // Send measurement information over UART
            setup_for_new_measurement_CLCNCO1();            // Setup for the next measurement
        }
        else{                                               // Check if cycles > 99
            NCO1CONbits.EN = 0;                             // Stop NCO1
            Timer1_Stop();                                  // Stop Timer1

            send_measurement_CLCNCO1_CLCNCO2();             // Send measurement information over UART
            setup_for_new_measurement_CLCNCO1();            // Setup for the next measurement
        }
    }
    else{
        cycles++;                                           // Increment cycles
    }    
   __delay_ms(1);                                           // Wait for 1ms
}
void CLC_NCO2_Calculations(void){
    if (PIR1bits.TMR1IF || PIR2bits.NCO1IF || cycles > 99){ // Check that one of the following is true: Timer1 interrupt flag, NCO1 interrupt flag, cycles > 99
        if (PIR1bits.TMR1IF){                               // Check if Timer1 interrupt flag is high
            NCO1CONbits.EN = 0;                             // Stop NCO1
            Timer1_Stop();                                  // Stop Timer1
            MAX_TMR1_Value();                               // Set Timer1 to maximum values
            send_measurement_MT();                          // Send measurement information over UART (MT means 'Max Timer')
            setup_for_new_measurement_CLCNCO2();            // Setup for the next measurement
        }
        else if (PIR2bits.NCO1IF){                          // Check if NCO1 interrupt flag is high
            NCO1CONbits.EN = 0;                             // Stop NCO1
            Timer1_Stop();                                  // Stop Timer1
            send_measurement_CLCNCO1_CLCNCO2();             // Send measurement information over UART
            setup_for_new_measurement_CLCNCO2();            // Setup for the next measurement
        }
        else{                                               // Check if cycles > 99
            NCO1CONbits.EN = 0;                             // Stop NCO1
            Timer1_Stop();                                  // Stop Timer1
            send_measurement_CLCNCO1_CLCNCO2();             // Send measurement information over UART
            setup_for_new_measurement_CLCNCO2();            // Setup for the next measurement
        }
    }
    else{
        cycles++;                                           // Increment cycles
    }
   __delay_ms(1);                                           // Wait for 1ms
}
void CLC_NCO3_Calculations(void){
    if (PIR1bits.TMR1IF || PIR0bits.TMR0IF || cycles > 999){// Check that one of the following is true: Timer1 interrupt flag, Timer0 interrupt flag, cycles > 999
            if (PIR1bits.TMR1IF){                           // Check if Timer1 interrupt flag is high
                Timer0_Stop();                              // Stop Timer0
                Timer1_Stop();                              // Stop Timer1
                MAX_TMR1_Value();                           // Set Timer1 to maximum values
                send_measurement_CLCNCO3();                 // Send measurement information over UART
                setup_for_new_measurement_CLCNCO3();        // Setup for the next measurement
            }
            else if (PIR0bits.TMR0IF){                      // Check if Timer0 interrupt flag is high
                Timer0_Stop();                              // Stop Timer0
                Timer1_Stop();                              // Stop Timer1
                send_measurement_CLCNCO3();                 // Send measurement information over UART
                setup_for_new_measurement_CLCNCO3();        // Setup for the next measurement
            }       
            else{                                           // Check if cycles > 999
                Timer0_Stop();                              // Stop Timer0
                Timer1_Stop();                              // Stop Timer1
                send_measurement_CLCNCO3();                 // Send measurement information over UART
                setup_for_new_measurement_CLCNCO3();        // Setup for the next measurement
            }
        }
        else{
            cycles++;                                       // Increment cycles
        }
       __delay_ms(2);                                       // Wait for 2ms
    }    