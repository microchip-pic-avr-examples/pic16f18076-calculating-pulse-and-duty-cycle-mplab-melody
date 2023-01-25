/*
 * File:   Timer1_Gate.c
 * Author: C63290
 *
 * Created on November 15, 2022, 10:31 AM
 */


#include <xc.h>
#include "Timer1_Gate.h"
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

void Timer1_StartSinglePulseAcquisition(void)
{
    T1GCONbits.T1GGO = 1;
}

void Timer1_Start(void)
{
    // Start the Timer by writing to TMRxON bit
    T1CONbits.TMR1ON = 1;
}

void Timer1_Write(size_t timerVal)
{
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

void Timer1_Stop(void)
{
    // Stop the Timer by writing to TMRxON bit
    T1CONbits.TMR1ON = 0;
}

void Timer1_OverflowCallbackRegister(void (* CallbackHandler)(void))
{
    Timer1_OverflowCallback = CallbackHandler;
}

static void Timer1_DefaultOverflowCallback(void)
{
    //Add your interrupt code here or
    //Use Timer1_OverflowCallbackRegister function to use Custom ISR
}

void Timer1_Initialize(void)
{
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

void Timer1_Gate_Calculations(void){
    T1GPPS = 0xD; //RB5->TMR1:T1G;
    
    Timer1_Initialize();
    
    // TIMER1 GATE DUTY CYCLE MEASUREMENT //
        TMR1GIF = 0;                            //Clear Gate Flag
        TMR1IF = 0;                             //Clear Timer1 Flag
        T1GCONbits.GE = 1;                      //Enable Timer1 Gate
        T1GCONbits.GPOL = 1;                    //Enable Timer1 Gate Polarity
        T1GCONbits.GTM = 1;                     //Enable Timer1 Gate Toggle Mode
        TMR1H = TMR1L = 0;                      //Clear TMR1H and TMR1L
        //Uncomment line below if pulses are longer than 4.1ms
        //uint8_t overflow_count = 0;             //Clear the overflow_count 
        
        
        Timer1_StartSinglePulseAcquisition();   //Enable T1GGO bit, start measuring the pulse
        while(!TMR1GIF){                        //Wait until the Gate Flag is set
        //Uncomment 3 lines below if pulse are longer than 4.1ms
            //if (TMR1IF == 1){                   //Check if Timer1 Flag has been set
            //    overflow_count++;               //If flag is set, increment overflow_count
            //}
        } 
        uint8_t period_low = TMR1L;             //save period low byte data
        uint16_t period_high = TMR1H;            //save period high byte data
    
        
    //TIMER1 GATE PULSE MEASUREMENT //    
        TMR1GIF = 0;                            
        TMR1IF = 0;
        T1GCONbits.GPOL = 0;                    //Clear Timer1 Gate Polarity 
        T1GCONbits.GTM = 0;                     //Clear Timer1 Gate Toggle Mode
        TMR1H = TMR1L = 0;
        //Uncomment line below if pulses are longer than 4.1ms
        //overflow_count = 0;                     
        Timer1_StartSinglePulseAcquisition();   
        while(!TMR1GIF){                        
        //Uncomment 3 lines below if pulse are longer than 4.1ms
            //if (TMR1IF == 1){                   
            //    overflow_count++;               
            //}
        }       
        
        uint8_t pulse_width_low = TMR1L;        //save pulse width low byte data
        uint16_t pulse_width_high = TMR1H;       //save pulse width high byte data
        
        //calculate the duty cycle and output as an 8-bit value, 0-255 = 0-100%, e.g. 127 = 50%
        uint24_t full_period = 0;
        uint24_t full_pulse_width = 0;
        uint24_t duty_cycle = 0;
    
        full_period = ((period_high << 8) + period_low);
        full_pulse_width = ((pulse_width_high << 8) + pulse_width_low);

        duty_cycle = (full_pulse_width << 8)/full_period;
        duty_cycle = 256 - duty_cycle;
        
        //send Pulse measurement over UART
        EUSART1_sendString("\nPULSE:");
        EUSART1_sendInt(pulse_width_high);
        EUSART1_sendInt(pulse_width_low);
        //send Period measurement over UART
        EUSART1_sendString("\nPD:"); 
        EUSART1_sendInt(period_high);
        EUSART1_sendInt(period_low);
        //send Duty Cycle calculation over UART
        EUSART1_sendString("\nDC:");
        EUSART1_sendInt(duty_cycle);
        //send overflow count over UART
        //Uncomment 2 lines below if pulses are longer than 4.1ms
        //EUSART1_sendString("\n");  
        //EUSART1_sendInt(overflow_count);

}