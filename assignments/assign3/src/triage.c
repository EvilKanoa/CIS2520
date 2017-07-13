/**
 * @file triage.c
 * @author Kanoa Haley - 0956712 - khaley@mail.uoguelph.ca
 * @date July 12, 2017
 * @brief File containing the implemention for the priority queue based triage
 *        application including its main function.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "PriorityQueueAPI.h"

#define OUTPUT_FILE "report.txt"
#define BUFFER_LENGTH 256

typedef struct PatiantData {
    char *id;
    int priority;
    char *symptom;
} PatiantData;

void triage(char *inputFileName, char *outputFileName);
PriorityQueue *readTriageFile(char *fileName);
void writeTriageReport(char *fileName);
void destroyData(char *data);

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

PriorityQueue *readTriageFile(char *fileName)
{
    FILE *fp = fopen(fileName, "r");
    PriorityQueue *triageData = createPriorityQueue(0.5, 0, MAX_PRIORITY_QUEUE, destroyData, NULL);
    char input[BUFFER_LENGTH];
    int tempLength = 0;

    if (fp == NULL) {
        return NULL;
    }

    while (fgets(input, BUFFER_LENGTH, fp) != NULL) {
        if (strlen(input) > 0) {

        }
    }
}

void writeTriageReport(char *fileName)
{

}

void destroyData(char *data)
{

}
