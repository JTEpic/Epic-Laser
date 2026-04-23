/**
 * File:   AsmLib.h
 * Author: JTEpic
 *
 * Created on February 6, 2026
 *
 * @file AsmLib.h
 * @brief Contains asm functions allowing delays
 */

#ifndef ASMLIB_H
#define	ASMLIB_H

#ifdef	__cplusplus
extern "C" {
#endif

/**
 * Delays 100u
 */
void delay100u(void);

/**
 * Delays 1m
 */
void delay1m(void);

#ifdef	__cplusplus
}
#endif

#endif	/* ASMLIB_H */