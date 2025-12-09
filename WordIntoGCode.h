#ifndef WORD_INTO_GCODE_H
#define WORD_INTO_GCODE_H

#include "rs232.h"
#include "serial.h"
#include "EndRobotDrawing.h"
#include "textScale.h"
#include "LoadFontMap.h"
#include "ProcessTestFile.h"

#define MAX_UNIT_SIZE 45

double textScale(double userHeight);

extern struct FontData FontMap[MAX_STROKES];

void WordIntoGcode(char letter, double textScale, double *currentX, double *currentY);

#endif // WORD_INTO_GCODE_H