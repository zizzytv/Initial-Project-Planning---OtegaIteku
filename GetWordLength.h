#include <stdio.h>
#include "textScale.h"
#include "ProcessTestFile.h"
#include "serial.h"
#include "WordIntoGCode.h"
#include "EndRobotDrawing.h"

int GetWordLength(FILE *file, double scale); // Function prototype