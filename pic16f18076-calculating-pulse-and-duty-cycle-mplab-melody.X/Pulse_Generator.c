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
    TRISAbits.TRISA3 = 0;
    ANSELAbits.ANSA3 = 0;
    uint8_t i = 0;
    
    //// 10% DC 0x1A////
    for (i = 0; i < 10; i++){
        LATAbits.LATA3 = 1;

        __delay_us(100);
        LATAbits.LATA3 = 0;

        __delay_us(900);
    }
        
    //// 20% DC 0x33////
    for (i = 0; i < 10; i++){
        LATAbits.LATA3 = 1;

        __delay_us(200);
        LATAbits.LATA3 = 0;

        __delay_us(800);
    }
        
    //// 30% DC 0x4D////
    for (i = 0; i < 10; i++){
        LATAbits.LATA3 = 1;

        __delay_us(300);
        LATAbits.LATA3 = 0;

        __delay_us(700);
    }
        
    //// 40% DC 0x66////
    for (i = 0; i < 10; i++){
        LATAbits.LATA3 = 1;

        __delay_us(400);
        LATAbits.LATA3 = 0;

        __delay_us(600);
    }
        
    //// 50% DC 0x80////
    for (i = 0; i < 10; i++){
        LATAbits.LATA3 = 1;

        __delay_us(500);
        LATAbits.LATA3 = 0;

        __delay_us(500);
    }
        
    //// 60% DC 0x9A////
    for (i = 0; i < 10; i++){
        LATAbits.LATA3 = 1;

        __delay_us(600);
        LATAbits.LATA3 = 0;

        __delay_us(400);
    }

    //// 70% DC 0xB3////
    for (i = 0; i < 10; i++){
        LATAbits.LATA3 = 1;

        __delay_us(700);
        LATAbits.LATA3 = 0;

        __delay_us(300);
    }
        
    //// 80% DC 0xCC////
    for (i = 0; i < 10; i++){
        LATAbits.LATA3 = 1;

        __delay_us(800);
        LATAbits.LATA3 = 0;

        __delay_us(200);
    }

    //// 90% DC 0xE6////
    for (i = 0; i < 10; i++){
        LATAbits.LATA3 = 1;

        __delay_us(900);
        LATAbits.LATA3 = 0;

        __delay_us(100);
    }
            
    TRISAbits.TRISA3 = 1;
    ANSELAbits.ANSA3 = 1;
}