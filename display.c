#include <xc.h>
#include "display.h"
#include "motor.h"

void display_set(uint8_t xPos, uint8_t yPos){
    // Rotate motors to align with coordinate
    motor_set(0, 90);
    motor_set(1, 90);
}