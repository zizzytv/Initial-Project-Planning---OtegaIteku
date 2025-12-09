#ifndef PROCESS_TEST_FILE_H
#define PROCESS_TEST_FILE_H

#include <stdio.h>
#include "textScale.h"

#define MAX_UNIT_SIZE 45 // Maximum number of strokes per character

int ProcessTestFile(const char *filename, double userHeight); // Function prototype for processing test file

#endif // PROCESS_TEST_FILE_H