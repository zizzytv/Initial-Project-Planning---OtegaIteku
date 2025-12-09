#include <stdio.h>
#include <stdlib.h>
#include <windows.h>   // For Sleep on Windows
//#include <conio.h>   // Uncomment when using serial
#include "rs232.h"
#include "serial.h"
#include "EndRobotDrawing.h"
#include "textScale.h"
#include "LoadFontMap.h"
#include "ProcessTestFile.h"
#include "WordIntoGCode.h"

#define FONT_SIZE_DATA 1024
#define MAX_UNIT_SIZE 45

// Global G-code buffer used across modules
char buffer[100];

double textScale(double userHeight); // Function prototype for text scaling

int main(void)
{
    double userHeight; // User-defined text height in mm

    printf("Enter the text height between 4.0mm to 10.0mm: ");
    if (scanf("%lf", &userHeight) != 1) // Validate input, when input is not a number
    {
        printf("Invalid height input.\n"); // Error handling for invalid input, debug message
        return 1;
    }

    // Validate user height input
    (void)textScale(userHeight);

    const char *fontFile = "SingleStrokeFont.txt"; // Font file name stored as a variable
    LoadFontMap(fontFile); //Calls LoadFontMap

    // Abort opening COM port if it cannot be opened
    if (CanRS232PortBeOpened() == -1) {
        printf("\nUnable to open the COM port (specified in serial.h)\n"); // Debug message
        return 1;
    }

    printf("\nAbout to wake up the robot\n");

    // Wake up robot by sending a newline
    sprintf(buffer, "\n");
    PrintBuffer(buffer);
    Sleep(100);

    // Wait for '$' prompt from the robot
    WaitForDollar();

    printf("\nThe robot is now ready to draw\n");

    // Put robot into "ready to draw" mode
    sprintf(buffer, "G1 X0 Y0 F1000\n");
    SendCommands(buffer);
    SendCommands("M3\n");
    SendCommands("S0\n");

    // Draw the contents of test.txt
    if (ProcessTestFile("test.txt", userHeight) != 0) {
        printf("Error processing test file.\n");
    }

    EndRobotDrawing();

    // Before we exit the program we need to close the COM port
    CloseRS232Port();
    printf("Com port now closed\n");

    return 0;
}

