/* 
 * File:   display.h
 * Author: JTEpic
 *
 * Created on April 3, 2026
 */

#ifndef DISPLAY_H
#define	DISPLAY_H

#ifdef	__cplusplus
extern "C" {
#endif
    
// Coordinate Struct, can be a position, scaling, pivot point, etc
typedef struct {
    uint8_t x;
    uint8_t y;
} Coord;

// Struct describing one object
typedef struct {
    const Coord *vertices; // Relative coords for object vertices, {0,0} is top left, {256,256} is bottom right, can make dynamic later for effects
    const uint8_t vCount; // Number of relative coords (above)
    Coord pos; // X and Y position of object
    uint16_t rot; // Rotation angle of object
} Object;

// Asteroid 2D representation (manual coordinates)
extern Object asteroid;

// Hold pointers to all objects to be rendered
//extern Object objects[];

// Moves the laser to align to the specified display coordinate 256x256
void display_set(uint8_t xPos, uint8_t yPos);

// Draw input object
void display_draw(Object *obj);

// Draw all objects
void display_render();

#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAY_H */