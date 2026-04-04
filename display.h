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

// Moves the laser to align to the specified display coordinate
void display_set(uint8_t xPos, uint8_t yPos);

#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAY_H */