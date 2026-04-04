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

// Rotates the specified motor theta degrees
void motor_set(uint8_t motor, uint8_t theta);

#ifdef	__cplusplus
}
#endif

#endif	/* MOTOR_H */