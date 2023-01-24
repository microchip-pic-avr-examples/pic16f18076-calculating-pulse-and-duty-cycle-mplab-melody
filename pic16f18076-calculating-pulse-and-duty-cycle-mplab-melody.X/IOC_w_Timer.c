/*
 * File:   IOC_w_Timer.c
 * Author: C63290
 *
 * Created on November 15, 2022, 10:32 AM
 */


#include <xc.h>
#include "IOC_w_TIMER.h"
#include "Basic_Init.h"
#include "mcc_generated_files/system/system.h"


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

void Timer0_Initialize(void)
{
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

void Timer0_Start(void)
{
    T0CON0bits.T0EN = 1;
}

void Timer0_Stop(void)
{
    T0CON0bits.T0EN = 0;
}

uint16_t Timer0_Read(void)
{
    uint16_t readVal;
    uint8_t readValLow;
    uint8_t readValHigh;

    readValLow  = TMR0L;
    readValHigh = TMR0H;
    readVal  = ((uint16_t)readValHigh << 8) + readValLow;

    return readVal;
}

void Timer0_Write(size_t timerVal)
{
    TMR0H = timerVal >> 8;
    TMR0L = (uint8_t) timerVal;
}

void Timer0_OverflowCallbackRegister(void (* CallbackHandler)(void))
{
    Timer0_OverflowCallback = CallbackHandler;
}

static void Timer0_DefaultOverflowCallback(void)
{
    //Add your interrupt code here or
    //Use Timer0_OverflowCallbackRegister function to use Custom ISR
}

void IOC_w_Timer_Calculations(void){
    IOCBP = 0x20;
    IOCBN = 0x20;    
    Timer0_Initialize();
    uint24_t pulse_count = 0;
    uint24_t period_count = 0;
    uint8_t period_countH = 0;
    uint8_t period_countL = 0;
    uint8_t pulse_countH = 0;
    uint8_t pulse_countL = 0;
    uint8_t duty_cycle = 0;
    IOCBFbits.IOCBF5 = 0;
    TMR0L = 0;
    TMR0H = 0;

    while(PORTBbits.RB5 == LOW);
    while(PORTBbits.RB5 == HIGH);
    IOCBFbits.IOCBF5 = 0;
    while(!IOCBFbits.IOCBF5);
    while(IOCBFbits.IOCBF5)
    {
        IOCBFbits.IOCBF5 = 0;
        Timer0_Start();
        while(!IOCBFbits.IOCBF5);
        IOCBFbits.IOCBF5 = 0;
        Timer0_Stop();
        pulse_count = Timer0_Read();
        Timer0_Start();
        while(!IOCBFbits.IOCBF5);
        IOCBFbits.IOCBF5 = 0;
        Timer0_Stop();
        period_count = Timer0_Read();
    }
        
        //pulse_count = 0x12;
        //period_count = 0x36;
        //period_count = period_count + pulse_count;
        
        period_countH = (period_count & 0xFF00) >> 8;
        period_countL = (period_count & 0xFF);
        pulse_countH = (pulse_count & 0xFF00) >> 8;
        pulse_countL = (pulse_count & 0xFF);
        
        duty_cycle = (pulse_count << 8)/ period_count;
        
        EUSART1_sendAllData(pulse_countH, pulse_countL, period_countH, period_countL, duty_cycle);

        pulse_count = 0;
        period_count = 0;
        TMR0L = 0;
        TMR0H = 0;

        __delay_ms(1);
    
    
    
    IOCBP = 0x00;
    IOCBN = 0x00;
}
