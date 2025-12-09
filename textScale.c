#include <stdio.h>
#include "textScale.h"
double textScale(double userHeight) // Calculate scaling factor based on user-defined text height
{
    // Check if height is within 4mm to 10mm limits
    if (userHeight < 4.0 || userHeight > 10.0) {
        printf("Error: Text height %.2fmm is outside the required 4mm-10mm range. Defaulting to 10mm.\n", userHeight); // Debug message
        userHeight = 10.0;
    }
    // Divide user's input by unit number (18)
    return userHeight/18.0; 
}
