 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
*/

/*
© [2022] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"
#include "Basic_Init.h"
#include "CCP.h"
#include "CLC_NCO.h"
#include "IOC_w_Timer.h"
#include "IOC_wo_Timer.h"
#include "Polled_Input.h"
#include "Pulse_Generator.h"
#include "Timer1_Gate.h"


/*
    Main application
*/


enum state {
    PULSE_GENERATOR,
    TIMER1,
    CLC_NCO1,
    CLC_NCO2,
    CLC_NCO3,
    CCP,
    IOC_W_TIMER,
    IOC_WO_TIMER,
    POLLED_INPUT,
};


int main(void)
{
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts 
    // Use the following macros to: 

    // Enable the Global Interrupts 
    INTERRUPT_GlobalInterruptEnable(); 

    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable(); 

    // Enable the Peripheral Interrupts 
    INTERRUPT_PeripheralInterruptEnable(); 

    // Disable the Peripheral Interrupts 
    //INTERRUPT_PeripheralInterruptDisable(); 
    
    enum state currentState = PULSE_GENERATOR;
    uint8_t InitFlag = 0;

    while(1){
        switch (currentState) {
            case PULSE_GENERATOR:
                if (InitFlag == 0) {
                    EUSART1_sendString("\nWelcome to Pulse Generator");
                    InitFlag = 1;
                }            
                else if (sw0_flag == 1) {
                    sw0_flag = 0;
                    InitFlag = 0;
                    currentState = TIMER1;
                }
                Pulse_Generator();
                break;

            case TIMER1:
                if (InitFlag == 0) {
                    EUSART1_sendString("\nWelcome to Timer1");
                    InitFlag = 1;
                }            
                else if (sw0_flag == 1) {
                    sw0_flag = 0;
                    InitFlag = 0;
                    currentState = CLC_NCO1;
                }
                //Timer1_Calculations();
                break;
                
            case CLC_NCO1:
                if (InitFlag == 0) {
                    EUSART1_sendString("\nWelcome to CLC and NCO 1");
                    InitFlag = 1;
                }            
                else if (sw0_flag == 1) {
                    sw0_flag = 0;
                    InitFlag = 0;
                    currentState = CLC_NCO2;
                }
                //CLC_NCO1_Calculations();
                break;
           case CLC_NCO2:
                if (InitFlag == 0) {
                    EUSART1_sendString("\nWelcome to CLC and NCO 2");
                    InitFlag = 1;
                }            
                else if (sw0_flag == 1) {
                    sw0_flag = 0;
                    InitFlag = 0;
                    currentState = CLC_NCO3;
                }
                //CLC_NCO2_Calculations();
                break;

            case CLC_NCO3:
                if (InitFlag == 0) {
                    EUSART1_sendString("\nWelcome to CLC and NCO 3");
                    InitFlag = 1;
                }            
                else if (sw0_flag == 1) {
                    sw0_flag = 0;
                    InitFlag = 0;
                    currentState = CCP;
                }
                //CLC_NCO1_Calculations();
                break;
                
            case CCP:
                if (InitFlag == 0) {
                    EUSART1_sendString("\nWelcome to CCP");
                    InitFlag = 1;
                }            
                else if (sw0_flag == 1) {
                    sw0_flag = 0;
                    InitFlag = 0;
                    currentState = IOC_W_TIMER;
                }
                //CCP_Calculations();
                break;
           case IOC_W_TIMER:
                if (InitFlag == 0) {
                    EUSART1_sendString("\nWelcome to IOC with Timer");
                    InitFlag = 1;
                }            
                else if (sw0_flag == 1) {
                    sw0_flag = 0;
                    InitFlag = 0;
                    currentState = IOC_WO_TIMER;
                }
                IOC_w_Timer_Calculations();
                break;

            case IOC_WO_TIMER:
                if (InitFlag == 0) {
                    EUSART1_sendString("\nWelcome to IOC without Timer");
                    InitFlag = 1;
                }            
                else if (sw0_flag == 1) {
                    sw0_flag = 0;
                    InitFlag = 0;
                    currentState = POLLED_INPUT;
                }
                IOC_wo_Timer_Calculations();
                break;
                
            case POLLED_INPUT:
                if (InitFlag == 0) {
                    EUSART1_sendString("\nWelcome to Polled Input");
                    InitFlag = 1;
                }            
                else if (sw0_flag == 1) {
                    sw0_flag = 0;
                    InitFlag = 0;
                    currentState = PULSE_GENERATOR;
                }
                Polled_Input_Calculations();
                break;
        }
    }    
}