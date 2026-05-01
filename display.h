/**
 * File:   display.h
 * Author: JTEpic
 *
 * Created on April 3, 2026
 *
 * @file display.h
 * @brief Contains functions that manipulate the display
 */

#ifndef DISPLAY_H
#define	DISPLAY_H

#ifdef	__cplusplus
extern "C" {
#endif

#define window_width 256  // Window Max X
#define window_height 256 // Window Max Y
#define XAngleMax 17.325f; // Max angle corresponding to farthest distance rightward to appear on screen, screen 1 foot away
#define YAngleMax 10.125f; // Max angle corresponding to farthest distance downward to appear on screen

/** Coordinate Struct, can be a position, scaling, pivot point, etc */
typedef struct {
    uint8_t x; /**< X Coordinate */
    uint8_t y; /**< Y Coordinate */
} Coord;

/** Struct describing one object */
typedef struct {
    const Coord *vertices; /**< Relative coords for object vertices, {0,0} is top left, {255,255} is bottom right, can make dynamic later for effects */
    const uint8_t vCount; /**< Number of relative coords (vertices) */
    Coord pos; /**< X and Y position of object */
    //Coord vel; // VelX and VelY velocity of object
    uint16_t rot; /**< Rotation angle of object */
    uint8_t scal; /**< Scale of object */
} Object;

// Asteroid 2D representation (manual coordinates)
extern Object asteroid;
// Square
extern Object square;
// Square2
extern Object square2;
// Border
extern Object border;

// Hold pointers to all objects to be rendered
//extern Object objects[];

/**
 * Moves the laser to align to the specified display coordinate (window_width by window_height)
 *
 * @param[in] xPos X Pixel to move to
 * @param[in] yPos Y Pixel to move to
 */
void display_set(uint8_t xPos, uint8_t yPos);

/**
 * Draw input object
 *
 * @param[in] obj Object to display
 */
void display_draw(Object *obj);

/**
 * Draw all objects
 */
void display_render();

#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAY_H */