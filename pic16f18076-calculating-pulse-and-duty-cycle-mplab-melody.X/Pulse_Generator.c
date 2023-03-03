/*
 * File:   Pulse_Generator.c
 * Author: C63290
 *
 * Created on January 24, 2023, 9:17 AM
 */


#include <xc.h>
#include "Pulse_Generator.h"
#include "mcc_generated_files/system/system.h"

void Pulse_Generator(void){
    TRISAbits.TRISA3 = 0;       // Set RA3 as an output pin
    ANSELAbits.ANSA3 = 0;       // Set RA3 as a digital signal
    uint8_t i = 0;              
    
    //// 10% Duty Cycle 0x1A////
    for (i = 0; i < 10; i++){
        LATAbits.LATA3 = 1;     // Set RA3 high
        __delay_us(100);        // Wait for 100us
        LATAbits.LATA3 = 0;     // Set RA3 low
        __delay_us(900);        // Wait for 900us
    }
        
    //// 20% Duty Cycle 0x33////
    for (i = 0; i < 10; i++){
        LATAbits.LATA3 = 1;
        __delay_us(200);        // Wait for 200us
        LATAbits.LATA3 = 0;
        __delay_us(800);        // Wait for 800us
    }
        
    //// 30% Duty Cycle 0x4D////
    for (i = 0; i < 10; i++){
        LATAbits.LATA3 = 1;
        __delay_us(300);        // Wait for 300us
        LATAbits.LATA3 = 0;
        __delay_us(700);        // Wait for 700us
    }
        
    //// 40% Duty Cycle 0x66////
    for (i = 0; i < 10; i++){
        LATAbits.LATA3 = 1;
        __delay_us(400);        // Wait for 400us
        LATAbits.LATA3 = 0;
        __delay_us(600);        // Wait for 600us
    }
        
    //// 50% Duty Cycle 0x80////
    for (i = 0; i < 10; i++){
        LATAbits.LATA3 = 1;
        __delay_us(500);        // Wait for 500us
        LATAbits.LATA3 = 0;
        __delay_us(500);
    }
        
    //// 60% Duty Cycle 0x9A////
    for (i = 0; i < 10; i++){
        LATAbits.LATA3 = 1;
        __delay_us(600);
        LATAbits.LATA3 = 0;
        __delay_us(400);
    }

    //// 70% Duty Cycle 0xB3////
    for (i = 0; i < 10; i++){
        LATAbits.LATA3 = 1;
        __delay_us(700);
        LATAbits.LATA3 = 0;
        __delay_us(300);
    }
        
    //// 80% Duty Cycle 0xCC////
    for (i = 0; i < 10; i++){
        LATAbits.LATA3 = 1;
        __delay_us(800);
        LATAbits.LATA3 = 0;
        __delay_us(200);
    }

    //// 90% Duty Cycle 0xE6////
    for (i = 0; i < 10; i++){
        LATAbits.LATA3 = 1;
        __delay_us(900);
        LATAbits.LATA3 = 0;
        __delay_us(100);
    }
            
    TRISAbits.TRISA3 = 1;       // Set RA3 as an input pin
    ANSELAbits.ANSA3 = 1;       // Set RA3 as an analog signal
}