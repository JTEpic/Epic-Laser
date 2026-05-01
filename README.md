## Introduction
This is a laser vector display project designed for the PIC24FJ64GA002 along with two stepper motors and a laser connected to the following ports:

* RB6 (RP6 for single pulse OC) for the x motor stepping
* RB7 (RP7 for single pulse OC) for the y motor stepping
* RB8 for the x motor direction
* RB9 for the y motor direction
* RB10 for enabling both motors, active low
* RB5 for the laser
* RA1 Left
* RA2 Right
* RA3 Down
* RA4 Up

## Objects
Various objects can be designed in the display.c file

## Documentation
Check the docs directory. To generate run 'doxygen Doxyfile'. To convert to PDF, run 'make' in the docs/latex folder.