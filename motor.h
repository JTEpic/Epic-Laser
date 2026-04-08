/* 
 * File:   motor.h
 * Author: JTEpic
 *
 * Created on April 3, 2026
 */

#ifndef MOTOR_H
#define	MOTOR_H

#ifdef	__cplusplus
extern "C" {
#endif

// Global variables holding current motor angles in degrees
extern uint16_t motorOneTheta;
extern uint16_t motorTwoTheta;

// Motor numbers to words
enum{
    BOTTOM,
    TOP
};

// Rotates the specified motor theta degrees
void motor_set(uint8_t motor, uint16_t theta);

#ifdef	__cplusplus
}
#endif

#endif	/* MOTOR_H */