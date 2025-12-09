#include <stdio.h>
#include "LoadFontMap.h"

// Define the global font map and counter
struct FontData FontMap[MAX_STROKES];
int TotalCharsLoaded = 0; 

int LoadFontMap(const char* filename) // Load font data from a file and store it in FontMap
{
    FILE *file = fopen(filename, "r"); // Open the font file for reading
    if (!file) {
        printf("Error: Could not open %s.\n", filename); // Error handling
        return -1;
    }

    int marker, ascii, lines; // Variables to read font data

    while (fscanf(file, "%d %d %d", &marker, &ascii, &lines) == 3) // Read until End of file
    {
        if (marker == 999) // Individual font character entry
        {
            if (TotalCharsLoaded >= MAX_STROKES) {
                printf("Warning: Max font characters reached.\n"); // Prevent overflow, debug message
                break;
            }

            int idx = TotalCharsLoaded; // Current index in FontMap
            FontMap[idx].ascii_id = ascii; // Store ASCII ID
            FontMap[idx].numberOfStrokes = lines; // Store number of strokes

            for (int i = 0; i < lines; i++)  // Read each stroke's data
            {
                if (fscanf(file, "%d %d %d",
                           &FontMap[idx].strokes[i].Xoffset,
                           &FontMap[idx].strokes[i].Yoffset,
                           &FontMap[idx].strokes[i].penState) != 3) // When file lines are greater/less than expected
                            {
                                printf("Error: malformed font file.\n"); // Error handling, debug message
                                fclose(file);
                                return -1;
                            }
            }
            TotalCharsLoaded++; // Increment total characters loaded
        }
    }
    fclose(file);
    printf("Debug: Font loaded. Total characters: %d\n", TotalCharsLoaded);
    return 0;
}