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

// Reflects the change of angle in degrees of a stepper motor after one pulse, 1.8 degrees * 1/8 setting
#define STEPPER_PULSE_DIST 0.225f

// Global variables holding current motor angles in degrees
extern float motorXTheta;
extern float motorXTheta;

// Motor numbers to words
enum{
    XMOTOR,
    YMOTOR
};

// Initializes Motors
void initMotors();

// Rotates the specified motor theta degrees
void motor_set(uint8_t motor, uint16_t theta);

// Rotates XMOTOR and YMOTOR motors allowing diagonal movement easily
//void motors_set(uint16_t theta1, uint16_t theta2);

#ifdef	__cplusplus
}
#endif

#endif	/* MOTOR_H */