#ifndef LOAD_FONT_MAP_H // Font map loading header guard to prevent multiple inclusions
#define LOAD_FONT_MAP_H

#include <stdio.h>

#define MAX_STROKES 1024  // max strokes per character AND max number of characters

struct PenData
{
    int Xoffset; // X coordinate of the stroke
    int Yoffset; // Y coordinate of the stroke
    int penState; // 1 = pen down, 0 = pen up
};

struct FontData 
{
    int ascii_id; // ASCII identifier for the character
    int numberOfStrokes; // Number of strokes for the character
    struct PenData strokes[MAX_STROKES]; // Array of stroke data
};

extern struct FontData FontMap[MAX_STROKES]; // Global font map array
extern int TotalCharsLoaded; // Total number of characters loaded into FontMap

int LoadFontMap(const char *filename); // Function prototype for loading font map

#endif // LOAD_FONT_MAP_H