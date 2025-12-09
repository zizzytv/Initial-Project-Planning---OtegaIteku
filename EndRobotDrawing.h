#ifndef END_ROBOT_DRAWING_H
#define END_ROBOT_DRAWING_H

#include <stdio.h>
#include <stdlib.h>
//#include <conio.h> // Uncomment when using serial
//#include <windows.h>
#include "rs232.h"
#include "serial.h"

// Shared buffer for G-code (defined once in main.c)
extern char buffer[100];

// Function prototypes (implemented in EndRobotDrawing.c)
void SendCommands(const char *buffer);
void EndRobotDrawing(void);

#endif // END_ROBOT_DRAWING_H