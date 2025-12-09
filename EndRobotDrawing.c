#include <stdio.h>
#include <stdlib.h>
//#include <conio.h> // Uncomment when using serial
#include <windows.h>
#include "rs232.h"
#include "serial.h"
#include "EndRobotDrawing.h"

// Sends the command string to the robot and waits for confirmation.
void SendCommands(const char *buffer)
{
    PrintBuffer(buffer);
    WaitForDollar();
}

// End the drawing: pen up, go to (0,0)
void EndRobotDrawing(void)
{
    // 1. Pen up
    SendCommands("S0\n");

    // 2. Move back to origin
    sprintf(buffer, "G0 X0 Y0\n");
    SendCommands(buffer);

    printf("// Robot Drawing Concluded: Pen up and returned to (0,0).\n"); // Debug message
}