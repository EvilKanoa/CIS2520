/**
 * @file triage.c
 * @author Kanoa Haley - 0956712 - khaley@mail.uoguelph.ca
 * @date July 12, 2017
 * @brief File containing the implemention for the priority queue based triage
 *        application including its main function.
 */

#include <stdio.h>
#include "PriorityQueueAPI.h"

#define OUTPUT_FILE "report.txt"

void triage(char *inputFileName, char *outputFileName);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Invalid arguments!\nUse \"%s [data file]\" to run\n", argv[0]);
        return -1;
    } else {
        printf("Running triage simulation using data file: %s\n", argv[1]);
        triage(argv[1], OUTPUT_FILE);
        printf("Results have been saved to: %s\n", OUTPUT_FILE);
        return 0;
    }
}

void triage(char *inputFileName, char *outputFileName)
{

}
