#include <xc.h>
#include "motor.h"
#include <stdint.h>

uint16_t motorOneTheta = 0;
uint16_t motorTwoTheta = 0;
void motor_set(uint8_t motor, uint16_t theta){
    // Rotate motor TO theta, 0 is starting position
    if(motor == BOTTOM){
        // Send pulse
        
        motorOneTheta = theta;
    } else if(motor == TOP){
        // Send pulse
        
        motorTwoTheta = theta;
    }
}