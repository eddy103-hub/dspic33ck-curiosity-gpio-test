/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.171.1
        Device            :  dsPIC33CK256MP508
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.70
        MPLAB 	          :  MPLAB X v5.50
 */

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
 */

/**
  Section: Included Files
 */
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/delay.h"
#include "mcc_generated_files/tmr1.h"

/*
                         Main application
 */
#define LEDs             LATE
#define LEDs_SetLow()    do { LATE = 0; } while(0)
#define LEDs_SetHigh()   do { LATE = 1; } while(0)
#define LEDs_Toggle()    do { LATE= ~LATE; } while(0)

static uint16_t rotateRegister;
uint16_t state = 0;
uint16_t timerFlag = 0;

void rotateLeds(void);

void TMR1_CallBack(void) {
    timerFlag = 1;
}

void rotateLeds(void) {

    if (state == 0) {

        LEDs_SetLow();
        LED1_SetHigh();

        //Initialize temporary register to begin at 1
        rotateRegister = 1;
        state = 1;
    }

    if (state == 1) {

        LEDs = rotateRegister;
        DELAY_milliseconds(500);
        rotateRegister <<= 1;
        //If the last LED has been lit, restart the pattern
        if (rotateRegister == 0)
            rotateRegister = 1;
    }
}

int main(void) {

    // initialize the device
    SYSTEM_Initialize();

    while (1) {

        if (Switch3_GetValue() == 0) {
            rotateLeds();
        } else {
            if (timerFlag) {
                timerFlag = 0;
                LEDs_Toggle();
            }
        }

    }
    return 1;
}
/**
 End of File
 */

