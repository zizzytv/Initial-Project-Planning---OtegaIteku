#include <stdio.h>
#include <stdlib.h>
//#include <conio.h> // Uncomment when using serial
//#include <windows.h>
#include "rs232.h"
#include "serial.h"
#include "textScale.h"
#include "LoadFontMap.h"
#include "ProcessTestFile.h"
#include "WordIntoGCode.h"

void WordIntoGcode(char letter, double textScale, double *currentX, double *currentY) // Generate G-code for a single character
{
    int foundIndex = -1; // Index of the character in FontMap
    extern char buffer[100];

    // Find the character in the loaded font map
    for (int i = 0; i < TotalCharsLoaded; i++) 
    {
        if (FontMap[i].ascii_id == (int)letter) 
        {
            foundIndex = i;
            break;
        }
    }

    // If character not found, skip with a warning
    if (foundIndex == -1) {
        printf("// Warning: Character '%c' (ASCII %d) not found in font. Skipping.\n", //Debug message
               letter, (int)letter);
        *currentX += 3.0 * textScale;
        return;
    }

    struct FontData *f = &FontMap[foundIndex];

    // For all strokes in the character
    for (int i = 0; i < f->numberOfStrokes; i++) {
        double targetX = *currentX + (f->strokes[i].Xoffset * textScale);
        double targetY = *currentY + (f->strokes[i].Yoffset * textScale);
        int penState = f->strokes[i].penState;

        if (penState == 1) // Pen down
        {
            SendCommands("S1000\n"); 
            sprintf(buffer, "G1 X%.2f Y%.2f\n", targetX, targetY); //Linear move to target position, this writes the words
            SendCommands(buffer);
        } else {
            SendCommands("S0\n"); //Move pen down
            sprintf(buffer, "G0 X%.2f Y%.2f\n", targetX, targetY); //Writes commands
            SendCommands(buffer);
        }
    }

    // Update X position for next character
    double lastStrokeX = f->strokes[f->numberOfStrokes - 1].Xoffset * textScale;
    *currentX += lastStrokeX;
}