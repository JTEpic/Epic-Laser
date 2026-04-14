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

// window_width by window_height display
void display_set(uint8_t xPos, uint8_t yPos){
    // Check if above bounds, can't be negative, should actually go to best position
    if(xPos >= window_width || yPos >= window_height)
        return;
    
    // Rotate motors to align with coordinate
    const float newXAngle = (float)xPos/((float)(window_width-1)) * XAngleMax;
    const float newYAngle = (float)yPos/((float)(window_height-1)) * YAngleMax;
    motor_set(XMOTOR, (uint16_t)newXAngle);
    motor_set(YMOTOR, (uint16_t)newYAngle);
    //delay1m(); // May need to wait for motor to get to position, likely covered in motor_set though
}

// Draw input object
void display_draw(Object *obj){
    //Move Position Random Direction
    obj->pos.x += 5;
    obj->pos.y += 5;
    
    Coord position = obj->pos;
    // Go to first position with laser disabled
    if(obj->vCount > 0){
        _RB5 = 0; // Laser Disable
        display_set(obj->vertices[0].x + position.x, obj->vertices[0].y + position.y);
        _RB5 = 1; // Laser Enable
    }
    
    // Activate all vertices/coords
    for(uint8_t x=1;x<obj->vCount;x++){
        display_set(obj->vertices[x].x + position.x, obj->vertices[x].y + position.y);
        //delay(1); // Likely the delay in display_set/motor_set will suffice
    }
    
    _RB5 = 0; // Laser Disable
}

// Draw all objects
void display_render(){
    display_draw(&asteroid);
}
