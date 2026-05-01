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
    0, // Initial Rotation
    1  // Initial Scale
};

// Square Object
Object square = {
    (Coord[]){{0,0},{0,50},{50,50},{50,0},{0,0}}, // {0,0} is top left
    5, // Number of above 
    {20,100}, // Initial Position
    0, // Initial Rotation
    1  // Initial Scale
};

// Square Object
Object square2 = {
    (Coord[]){{0,0},{0,50},{50,50},{50,0},{0,0}}, // {0,0} is top left
    5, // Number of above 
    {50,100}, // Initial Position
    0, // Initial Rotation
    1  // Initial Scale
};

// Border Object
Object border = {
    (Coord[]){{0,0},{0,255},{255,255},{255,0},{0,0}}, // {0,0} is top left
    5, // Number of above 
    {0,0}, // Initial Position
    0, // Initial Rotation
    1  // Initial Scale
};

// window_width by window_height display
void display_set(uint8_t xPos, uint8_t yPos){
    // Check if above bounds, can't be negative, should actually go to best position
    if(xPos >= window_width || yPos >= window_height)
        return;
    
    // Rotate motors to align with coordinate
    const float newXAngle = (float)xPos/((float)(window_width-1)) * XAngleMax;
    const float newYAngle = (float)yPos/((float)(window_height-1)) * YAngleMax;
    // Runs one motor completely at a time, can't go diagonal for now
    motor_set(XMOTOR, (uint16_t)newXAngle);
    motor_set(YMOTOR, (uint16_t)newYAngle);
    //delay1m(); // May need to wait for motor to get to position, likely covered in motor_set though
}

// Draw input object
void display_draw(Object *obj){
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
    }
    
    _RB5 = 0; // Laser Disable
}

// Draw all objects
void display_render(){
    //Move Positions Random Direction
    // Asteroid
    /*asteroid.pos.x += 5;
    asteroid.pos.y += 5;
    display_draw(&asteroid);*/
    
    // Border
    //border.pos.x += 5;
    //border.pos.y += 5;
    display_draw(&border);
    
    // Square, Automatic Control
    static int8_t squareVelX = 1;
    static int8_t squareVelY = 1;
    // Left Boundary
    if(square.pos.x == 0){
        squareVelX = 1;
    // Right Boundary
    } else if(square.pos.x >= (255-50)){
        squareVelX = -1;
    }
    // Top Boundary
    if(square.pos.y == 0){
        squareVelY = 1;
    }
    // Bottom Boundary
    else if(square.pos.y >= (255-50)){
        squareVelY = -1;
    }
    square.pos.x += squareVelX;
    square.pos.y += squareVelY;
    display_draw(&square);
    
    // Square2, Manuel Control
    // Down
    if(!PORTAbits.RA3 == 0){
        square2.pos.y += -4;
    }
    // Up
    if(!PORTAbits.RA4 == 0){
        square2.pos.y += 4;
    }
    // Left
    if(!PORTAbits.RA1 == 0){
        square2.pos.x += -4;
    }
    // Right
    if(!PORTAbits.RA2 == 0){
        square2.pos.x += 4;
    }
    display_draw(&square2);
}
