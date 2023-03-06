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

enum state {                                                            // Setup all states (measuring method) for project
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

    INTERRUPT_GlobalInterruptEnable();                                  // Enable the Global Interrupts 

    INTERRUPT_PeripheralInterruptEnable();                              // Enable the Peripheral Interrupts 

    enum state currentState = PULSE_GENERATOR;                          // Set initial state as Pulse Generator
    uint8_t InitFlag = 0;

    while(1){
        switch (currentState) {                                         // Check the current state, and go to that specific case
            case PULSE_GENERATOR:                                       // Pulse Generator Case
                if (InitFlag == 0) {                                    // Check if InitFlag is 0
                    EUSART1_sendString("\nWelcome to Pulse Generator"); // Send a message over UART
                    InitFlag = 1;                                       // Set InitFlag to 1
                }            
                else if (sw0_flag == 1) {                               // Check is sw0_flag is 1 (triggered by the CLC4 Interrupt Flag CLC4IF)
                    sw0_flag = 0;                                       // Clear the sw0_flag
                    InitFlag = 0;                                       // Clear the InitFlag
                    currentState = TIMER1;                              // Change the state to TIMER1
                }
                Pulse_Generator();                                      // Run the Pulse_Generator function
                break;                                                  // break out of the structure (goes to top of while loop)

            case TIMER1:                                                // Timer1 Gate Method
                if (InitFlag == 0) {                                    
                    Pins_PPS_Reset();                                   // Reset all Pins and PPS in preparation for a new initialization
                    EUSART1_sendString("\nWelcome to Timer1 Gate");     // Send a message over UART
                    Timer1_Gate_Initialize();                           // Run the Timer1 Gate Initialization function
                    InitFlag = 1;
                }            
                else if (sw0_flag == 1) {
                    sw0_flag = 0;
                    InitFlag = 0;
                    currentState = CLC_NCO1;                            // Change the state to CLC_NCO1
                }
                Timer1_Gate_Calculations();                             // Run the Timer1 Gate Calculation function (will output data over UART)
                break;
                
            case CLC_NCO1:                                              // First CLC-NCO Method
                if (InitFlag == 0) {
                    Pins_PPS_Reset();                                   
                    EUSART1_sendString("\nWelcome to CLC and NCO 1");   // Send a message over UART
                    CLC_NCO1_Initialize();                              // Run the first CLC NCO Initialization function
                    InitFlag = 1;
                }            
                else if (sw0_flag == 1) {
                    sw0_flag = 0;
                    InitFlag = 0;
                    currentState = CLC_NCO2;                            // Change the state to CLC_NCO2
                }
                CLC_NCO1_Calculations();                                // Run the first CLC NCO Calculation function (will output data over UART)
                break;
                
           case CLC_NCO2:                                               // Second CLC-NCO Method
                if (InitFlag == 0) {
                    Pins_PPS_Reset();                                   
                    EUSART1_sendString("\nWelcome to CLC and NCO 2");   // Send a message over UART
                    CLC_NCO2_Initialize();                              // Run the second CLC NCO Initialization function
                    InitFlag = 1;
                }            
                else if (sw0_flag == 1) {
                    sw0_flag = 0;
                    InitFlag = 0;
                    currentState = CLC_NCO3;                            // Change the state to CLC_NCO3
                }
                CLC_NCO2_Calculations();                                // Run the second CLC NCO Calculation function (will output data over UART)
                break;

            case CLC_NCO3:                                              // Third CLC-NCO Method
                if (InitFlag == 0) {
                    Pins_PPS_Reset();
                    EUSART1_sendString("\nWelcome to CLC and NCO 3");   // Send a message over UART
                    CLC_NCO3_Initialize();                              // Run the third CLC NCO Initialization function
                    InitFlag = 1;
                }            
                else if (sw0_flag == 1) {
                    sw0_flag = 0;
                    InitFlag = 0;
                    currentState = CCP;                                 // Change the state to CCP
                }
                CLC_NCO3_Calculations();                                // Run the third CLC NCO Calculation function (will output data over UART)
                break;
                
            case CCP:                                                   // CCP Method
                if (InitFlag == 0) {
                    Pins_PPS_Reset();
                    EUSART1_sendString("\nWelcome to CCP");             // Send a message over UART
                    CCP_Initialize();                                   // Run the CCP Initialization function
                    InitFlag = 1;
                }            
                else if (sw0_flag == 1) {
                    sw0_flag = 0;
                    InitFlag = 0;
                    currentState = IOC_W_TIMER;                         // Change the state to IOC_W_TIMER
                }
                CCP_Calculations();                                     // Run the CCP Calculation function (will output data over UART)
                break;
                
           case IOC_W_TIMER:                                            // IOC with Timer Method
                if (InitFlag == 0) {
                    Pins_PPS_Reset();
                    EUSART1_sendString("\nWelcome to IOC with Timer");  // Send a message over UART
                    InitFlag = 1;
                }            
                else if (sw0_flag == 1) {
                    sw0_flag = 0;
                    InitFlag = 0;
                    currentState = IOC_WO_TIMER;                        // CHange the state to IOC_WO_TIMER
                }
                IOC_w_Timer_Calculations();                             // Run the IOC with Timer Calculation function (will output data over UART)
                break;

            case IOC_WO_TIMER:                                          // IOC without Timer Method
                if (InitFlag == 0) {
                    Pins_PPS_Reset();
                    EUSART1_sendString("\nWelcome to IOC without Timer");   // Send a message over UART
                    InitFlag = 1;
                }            
                else if (sw0_flag == 1) {
                    sw0_flag = 0;
                    InitFlag = 0;
                    currentState = POLLED_INPUT;                        // Change the state to POLLED_INPUT
                }
                IOC_wo_Timer_Calculations();                            // Run the IOC without Timer Calculation function (will output data over UART)
                break;
                
            case POLLED_INPUT:                                          // Polled Input Method
                if (InitFlag == 0) {
                    Pins_PPS_Reset();
                    EUSART1_sendString("\nWelcome to Polled Input");    // Send a message over UART
                    InitFlag = 1;
                }            
                else if (sw0_flag == 1) {
                    sw0_flag = 0;
                    InitFlag = 0;
                    currentState = PULSE_GENERATOR;                     // Change the state to PULSE_GENERATOR
                }
                Polled_Input_Calculations();                            // Run the Polled Input Calculation function (will output data over UART)
                break;
        }
    }    
}