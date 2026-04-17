#include <xc.h>
#include "AsmLib.h"
#include "motor.h"
#include <stdint.h>

float motorXTheta = 0.0f; // 0 at start
float motorYTheta = 0.0f; // 0 at start

void initMotors(){
    // PPS to Map peripherals to pins
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
    RPOR3bits.RP6R = 18;  // Use Pin RP6 (X Motor) for Output Compare 1 = "18"
    RPOR3bits.RP7R = 19;  // Use Pin RP7 (Y Motor) for Output Compare 2 = "19"
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock   PPS
    
    //AD1PCFG |= 0x0000;            //sets pins to digital I/O
    TRISB &= 0b1111100000111111;    //RB6,RB7,RB8,RB9,RB10, 0=output
    _RB10 = 0; // Motor Enables, active low
    _RB9 = 0; // Y Motor Direction
    _RB8 = 0; // X Motor Direction
    
    // X Motor (RP6)
    
    // Timer 2, 500*Tcy to send pulses in time
    T2CON = 0; // General Reg
    T2CONbits.TCKPS = 0; // Prescaler
    PR2 = 499; // Max Count
    TMR2 = 0; // Current Count
    IFS0bits.T2IF = 0; // Flag bit
    T2CONbits.TON = 1; // Enable bit
    // enable Timer 2 interrupt
    IEC0bits.T2IE = 1;
    
    // OC1 w/ Timer 2 Setup
    OC1CON = 0;    // turn off OC1 for now
    OC1R = 0;   // Pulse start position. We won't touch OC1R again
    OC1RS = 500;  // We will only change this before pulse is turned on, duration of pulse
    OC1CONbits.OCTSEL = 0; // Use Timer 2 for compare source
    //OC1CONbits.OCM = 0b100; // Output compare single pulse
    
    
    // Y Motor (RP7)
    
    // Timer 3, 1.5625ms
    T3CON = 0; // General Reg
    T3CONbits.TCKPS = 0; // Prescaler, 1:1,1:8,1:64,1:256
    PR3 = 499; // Max Count, Delay = PRE * Tcy * (PRx+1)
    TMR3 = 0; // Current Count
    IFS0bits.T3IF = 0; // Flag bit
    T3CONbits.TON = 1; // Enable bit
    // enable Timer 3 interrupt
    IEC0bits.T3IE = 1;
    
    // OC2 w/ Timer 3 Setup
    OC2CON = 0;    // turn off OC1 for now
    OC2R = 0;   // Pulse start position. We won't touch OC1R again
    OC2RS = 500;  // We will only change this before pulse is turned on, duration of pulse
    OC2CONbits.OCTSEL = 1; // Use Timer 3 for compare source
    //OC2CONbits.OCM = 0b100; // Output compare single pulse
}

void motor_set(uint8_t motor, uint16_t theta){
    // Rotate motor TO theta, current motorXTheta is starting position
    if(motor == XMOTOR){
        float diffX = ((float)theta - motorXTheta);
        // Decide Direction
        if(diffX > 0.0f)
            _RB8 = 0;
        else{
            diffX *= -1.0f;
            _RB8 = 1;
        }
        
        // Calculate pulses needed and send
        const uint16_t pulses = (uint16_t)(diffX/STEPPER_PULSE_DIST);
        for(uint16_t x = 0; x < pulses; x++){
            // Send pulse
            OC1RS = 160;  // Duration of pulse, 10us
            OC1CONbits.OCM = 0b100; // Output compare single pulse
            delay100u(); // 1/T for freq, 10kHz max
            delay100u(); // 5kHz
            delay100u();
            delay100u(); // 2.5kHz
            //delay1m(); // 1kHz recommend
        }
        
        // Set New Theta
        //motorXTheta = (float)theta;
        if(!_RB8)
            motorXTheta += (float)pulses * STEPPER_PULSE_DIST;
        else
            motorXTheta -= (float)pulses * STEPPER_PULSE_DIST;
    } else if(motor == YMOTOR){
        float diffY = ((float)theta - motorYTheta);
        // Decide Direction
        if(diffY > 0.0f)
            _RB9 = 0;
        else{
            diffY *= -1.0f;
            _RB9 = 1;
        }
        
        // Calculate pulses needed and send
        const uint16_t pulses = (uint16_t)(diffY/STEPPER_PULSE_DIST);
        for(uint16_t x = 0; x < pulses; x++){
            // Send pulse
            OC2RS = 160;  // Duration of pulse, 10us
            OC2CONbits.OCM = 0b100; // Output compare single pulse
            delay100u();
            delay100u();
            delay100u();
            delay100u();
            //delay1m();
        }
        
        // Set New Theta
        //motorYTheta = (float)theta;
        if(!_RB9)
            motorYTheta += (float)pulses * STEPPER_PULSE_DIST;
        else
            motorYTheta -= (float)pulses * STEPPER_PULSE_DIST;
    }
}