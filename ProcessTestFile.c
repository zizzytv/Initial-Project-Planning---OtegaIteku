#include <stdio.h>
#include "textScale.h"
#include "ProcessTestFile.h"
#include "serial.h"
#include "WordIntoGCode.h"
#include "EndRobotDrawing.h"
#include "GetWordLength.h"

#define DRAWING_LIMIT_MM 100.0

int ProcessTestFile(const char *filename, double userHeight) // Process the test file and convert text to G-code
{
    FILE *file = fopen(filename, "r"); // Open the test file for reading
    if (file == NULL)
    {
        printf("Could not open file %s\n", filename); // Error handling, debug message
        return 1;
    }

    double scale = textScale(userHeight); // Get scaling factor based on user height
    double lineSpacing = userHeight * 2.2; // distance between baselines
    double spaceWidth  = 7.0 * scale; // width of a space

    double currentX = 0.0; // variable to track current X position
    double currentY = 0.0; // variable to track current Y position
    int c; // character read from file
    extern char buffer[100];

    while ((c = fgetc(file)) != EOF)
    {
        // Safety check on drawing limits
        if (currentX > DRAWING_LIMIT_MM || currentY < -DRAWING_LIMIT_MM) //When lines exceed drawing limits
        {
            printf("\n--- GLOBAL BOUNDARY EXCEEDED (X or Y) ---\n"); // Debug message
            printf("// Further reading of text file aborted.\n");
            break;
        }

        if (c == '\n') // Handle new line
        {
            // NEW LINE
            currentX = 0.0;
            currentY -= lineSpacing;

            // Vertical limit check
            if (currentY < -DRAWING_LIMIT_MM) {
                printf("\n--- BOUNDARY ERROR: New line exceeds -%.2fmm limit ---\n",
                       DRAWING_LIMIT_MM);
                break;
            }

            SendCommands("S0\n");
            sprintf(buffer, "G0 X0.00 Y%.2f\n", currentY);
            SendCommands(buffer);
        }
        else if (c == ' ') // Handle space character
        {
            double nextWordLength = GetWordLength(file, scale); // Look ahead to get next word length

            // If next word does not fit on current line, create a new line
            if (currentX + spaceWidth + nextWordLength > DRAWING_LIMIT_MM) 
            {
                currentX = 0.0;
                currentY -= lineSpacing;

                SendCommands("S0\n");
                sprintf(buffer, "G0 X0.00 Y%.2f\n", currentY);
                SendCommands(buffer);
            }
            else
            {
                // Word fits on current line, adds space
                currentX += spaceWidth;

                SendCommands("S0\n");
                sprintf(buffer, "G0 X%.2f Y%.2f\n", currentX, currentY);
                SendCommands(buffer);
            }
        }

        else if (c != '\r') //ignore carriage return characters to prevent writing over words
        {
            // Printable character
            WordIntoGcode((char)c, scale, &currentX, &currentY);
        }
    }

    fclose(file);
    return 0;
}