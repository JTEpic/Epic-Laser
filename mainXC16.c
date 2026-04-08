/*
 * File:   mainXC16.c
 * Authors: JTEpic
 *
 * Created on April 3, 2026
 */

#include <xc.h>
#include "AsmLib.h"
#include "motor.h"
#include "display.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1          // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF        // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF          // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF           // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF        // JTAG Port Enable (JTAG port is disabled)

// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI       // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF       // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON       // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME      // Clock Switching and Monitor (Clock switching is enabled, 
                                       // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL      // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))

#define DEFAULT_DELAY 100

void setup(void)
{
    // Execute once code goes here
    CLKDIVbits.RCDIV = 0;  //Set RCDIV=1:1 (default 2:1) 32MHz or FCY/2=16M
    
    AD1PCFG = 0x9ffe;            //sets all pins to digital I/O, AN0 (RA0) analog
    //AD1PCFGbits.PCFG0 = 0; //AN0
    TRISA = 0xffff;              //set port A to inputs
    TRISB = 0x0000;              //and port B to outputs, 0=output
    //LATA = 0xffff;               //Set all of port A to HIGH
    //LATB = 0xffff;               //and all of port B to HIGH
    
    // Timer 2, 100ms
    T2CON = 0; // General Reg
    T2CONbits.TCKPS = 2; // Prescaler
    PR2 = 24999; // Max Count
    TMR2 = 0; // Current Count
    IFS0bits.T2IF = 0; // Flag bit
    T2CONbits.TON = 1; // Enable bit
    // enable Timer 2 interrupt
    IEC0bits.T2IE = 1;
    
    // Timer 3, 1/16 s
    T3CON = 0; // General Reg
    T3CONbits.TCKPS = 2; // Prescaler, 1:1,1:8,1:64,1:256
    PR3 = 15624; // Max Count, (1/K) = PRE * 62.5n * (PRx+1)
    TMR3 = 0; // Current Count
    IFS0bits.T3IF = 0; // Flag bit
    T3CONbits.TON = 1; // Enable bit
    // enable Timer 3 interrupt
    IEC0bits.T3IE = 1;
}

// Delay by input's milliseconds
void delay(uint16_t delay_in_ms){
    for(uint16_t x=0;x<delay_in_ms;x++)
        delay1m();
}

// Timer 2 Interrupt, every 100ms
void __attribute__((interrupt, auto_psv)) _T2Interrupt(){
    char avgStr[20];
    uint16_t avg = 0x0000;
    
    // Float to String
    sprintf(avgStr, "%6.4f V", ((float)avg)*(3.3f/1024.0f));  // x.xxxx V
                       // 6.4 in the format string %6.4f means 6 
                       // placeholders for the whole
                       // floating-point number, 4 of which are for 
                       // the fractional part.
    
    _T2IF = 0;
}

// Timer 3 Interrupt, every 1/16
void __attribute__((interrupt, auto_psv)) _T3Interrupt(){
    _T3IF = 0;
}

void test_align(){
    // Test Moving to Angle
    motor_set(BOTTOM, 90); // Move motor1 90 degrees
    delay(1000);
    motor_set(TOP, 90); // Move motor2 90 degrees
    delay(1000);

    // Test Moving to Coordinate
    display_set(0,0);
    delay(1000);
    display_set(256,256);
    delay(1000);
}

int main(void) {
    setup();
    
    // Testing/Alignment Procedure
    test_align();
    
    while(1){
        // Test On
        //_RB5 = 1;
        //delay(500);
        //_RB5 = 0;
        
        // Draw all objects
        display_render();
        
        // Loop Delay, FPS = 1/delay
        //delay(DEFAULT_DELAY);
        delay(200);
    }
    
    return 0;
}