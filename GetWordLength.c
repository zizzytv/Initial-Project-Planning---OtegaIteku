#include <stdio.h>
#include "textScale.h"
#include "ProcessTestFile.h"
#include "serial.h"
#include "WordIntoGCode.h"
#include "EndRobotDrawing.h"
#include "GetWordLength.h"

int GetWordLength(FILE *filename, double scale) 
    {
        long pos = ftell(filename); // save current file position
        int c; // character read from file
        int length = 0; //changed from double to int for pixel length

        while ((c = fgetc(filename)) != EOF && c != ' ' && c != '\n' && c != '\r') // Read until space, newline, or end of file
        {
            // Look up character width using font map
            int foundIndex = -1;
            for (int i = 0; i < TotalCharsLoaded; i++)
            {
                if (FontMap[i].ascii_id == c) // Match found
                {
                    foundIndex = i;
                    break;
                }
            }

            if (foundIndex != -1) 
            {
                struct FontData *f = &FontMap[foundIndex];
                int lastStrokeX = f->strokes[f->numberOfStrokes - 1].Xoffset * scale; //changed from double to int for pixel length
                length += lastStrokeX;
            }
        }

        fseek(filename, pos, SEEK_SET); // restore cursor
        return length; // return total length in pixels
    }
