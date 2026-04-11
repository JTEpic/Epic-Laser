#include <xc.h>
#include "AsmLib.h"
#include "display.h"
#include "motor.h"
#include <stdint.h>

// Asteroid Object
Object asteroid = {
    (Coord[]){{0,0},{10,30},{35,35},{40,20},{25,0},{0,0}}, // {0,0} is top left
    6, // Number of above 
    {100,100}, // Initial Position
    0 // Initial Rotation
};

uint16_t xAngleMax = 30; // Max angle corresponding to farthest distance rightward
uint16_t yAngleMax = 30; // Max angle corresponding to farthest distance downward
// window_width by window_height display
void display_set(uint8_t xPos, uint8_t yPos){
    // Check if above bounds, can't be negative
    if(xPos >= window_width || yPos >= window_height)
        return;
    
    // Rotate motors to align with coordinate
    motor_set(XMOTOR, (uint8_t)((float)xPos/(window_width-1)) * xAngleMax);
    motor_set(YMOTOR, (uint8_t)((float)yPos/(window_height-1)) * yAngleMax);
    //delay1m(); // May need to wait for motor to get to position, likely covered in motor_set though
}

// Draw input object
void display_draw(Object *obj){
    Coord position = obj->pos;
    //Move Position Random Direction
    position.x += 5;
    position.y += 5;
    obj->pos = position;
    
    // Activate all vertices/coords
    for(uint8_t x=0;x<obj->vCount;x++){
        display_set(obj->vertices[x].x + position.x, obj->vertices[x].y + position.y);
        //delay(1); // Likely the delay in display_set/motor_set will suffice
    }
}

// Draw all objects
void display_render(){
    display_draw(&asteroid);
}
