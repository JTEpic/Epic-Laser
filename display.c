#include <xc.h>
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

void display_set(uint8_t xPos, uint8_t yPos){
    // Rotate motors to align with coordinate
    motor_set(BOTTOM, 90);
    motor_set(TOP, 90);
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
    }
}

// Draw all objects
void display_render(){
    display_draw(&asteroid);
}