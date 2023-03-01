<!-- Please do not change this logo with link -->

[![MCHP](images/microchip.png)](https://www.microchip.com)

# Various Solutions for Calculating a Pulse and Duty Cycle

## Related Documentation

- [PIC16F18076 Data Sheet](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/PIC16F18056-76-28-40-Pin-Microcontroller-Data-Sheet-40002325B.pdf)
- [PIC16F18076 Family Product Page](https://www.microchip.com/wwwproducts/en/PIC16F18076)
- [Various Solutions for Calculating a Pulse and Duty Cycle Application Note](https://www.microchip.com/en-us/application-notes/an3324) <!--UPDATE APP NOTE NUMBER TO WHAT IT SHOULD BE (the new one)-->

## Software Used

- [MPLAB® X IDE](http://www.microchip.com/mplab/mplab-x-ide) **6.0.0** or newer
- [MPLAB Xpress IDE](https://www.microchip.com/en-us/development-tools-tools-and-software/mplab-xpress) (alternative to MPLAB X IDE)
- [MPLAB XC8 Compiler](http://www.microchip.com/mplab/compilers) **2.36** or a newer compiler 
- [Microchip PIC16F1xxxx Series Device Support pack](https://packs.download.microchip.com/) **1.15.191** or newer Device Pack

## Hardware Used

- PIC16F18076 Curiosity Nano [(DM182029)](https://www.microchip.com/en-us/development-tool/EV53Z50A) (x2)

## Introduction
Many times is it desirable to quantify the pulse width of a periodic signal, such as a servo motor, or duty cycle of a pulse-width modulated signal. This code example demonstrates six different methods for measuring a pulse and a period and calculating the duty cycle based off that measured pulse and period all while using the PIC16F18076. 

## Setup
### Hardware Connections

Connect two PIC16F18076 Curiousity Nano board together following the diagram in Figure 1.

*Figure 1 - Building the Circuit*
<!--add figure-->

Make sure to connect the UART pins to a lofic analyzer so that the results can be viewed.

### Programming
- Download, install, and open MPLABX IDE version 6.0.0 (or newer).

- Download and install the XC8 C-Compiler version 2.36 (or newer).

- Download and Open the 'pic16f18076-calculating-pulse-and-duty-cycle-mplab-melody.X' project as shown in Figure 2.

*Figure 2 - Open Project Menu in MPLABX*
<!--add figure-->

- Once the project is open, select either the 'free' or 'pro' configuration as shown in Figure 3.

*Figure 3 - Select project configuration*
<!--add figure-->

- Program the device by clicking on the "Make and Program Device Main Project" from the taskbar at the top (Figure 4).

*Figure 4 -  Make and Program Device Main Project Button*
<!--add figure-->

Wait for the Output tab to show 'Programming Complete' (Figure 5) then proceed to the **Operation** section below.

*Figure 5 -  Programming Complete*
<!--add figure-->

## Operation

This example utilizes a button which toggles between the various methods of measuring the pulse width and duty cycle (Figure 6). 

*Figure 6 -  PIC16F18076 Curiousity Nano Board SW0 Button*
<!--add figure-->

When the button is pressed, it changes the method based on the list below. 

1. Pulse Generator
2. Timer1 Gate
3. CLC NCO 1
4. CLC NCO 2
5. CLC NCO 3
6. CCP
7. IOC with Timer
8. IOC without Timer
9. Polled Input 

The Pulse generator mode is the default mode of this example.  It generates a 1MHz signal with varying duty cycles. The duty cycles range from 10% to 90% at 10% intervals and constantly loop. Each of the subsequent modes can be triggered by the appropriate amount of button presses (the order is the list above). Each mode takes the input signal from the pulse input pin and calculates the pulse, the period, and the duty cycle for the given pulse, and outputs that information to the logic analyzer through UART. An example of the UART data can be seen in Figure 7. 

*Figure 7 -  UART on Logic Analyzer*
<!--add figure-->

The value for duty cycle is an 8-bit value, so a conversion from an 8-bit value to a 0-100% scale will be necessary.  For more in-depth information on each of the measurement methods, please refer to the linked application note at the top of this example.

## Summary

This example has demonstrated sevreral methods of how to measure the pulse width and duty cycle of a pulse on the PIC18F18076 Curiousity Nano Board. 

<!--Note: A second Curiosty Nano Board was used to simulate the input signal at varying duty cycles (10%-90% at 10% intervals).  Replacing the pulse generating Curiosty Nano Board with a different input pulse generator may be advantageous depending on the application. -->
