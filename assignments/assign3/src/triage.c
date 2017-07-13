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

int triage(char *inputFileName, char *outputFileName);
PriorityQueue *readTriageFile(char *fileName);
void writeTriageReport(char *fileName);
void destroyData(void *data);
void stripNewline(char *str);

int main(int argc, char *argv[]) {
    int result;
    if (argc != 2) {
        printf("Invalid arguments!\nUse \"%s [data file]\" to run\n", argv[0]);
        return -1;
    } else {
        printf("Running triage simulation using data file: %s\n", argv[1]);
        result = triage(argv[1], OUTPUT_FILE);
        printf("Results have been saved to: %s\n", OUTPUT_FILE);
        return result;
    }
}

int triage(char *inputFileName, char *outputFileName)
{
    PriorityQueue *queue = readTriageFile(inputFileName);

    if (queue == NULL) {
        printf("Unable to open %s, exiting...\n", inputFileName);
        return -2;
    }

    return 0;
}

PriorityQueue *readTriageFile(char *fileName)
{
    FILE *fp = fopen(fileName, "r");
    PriorityQueue *triageData = createPriorityQueue(0.5, 0, MAX_PRIORITY_QUEUE, destroyData, NULL);
    char *input = malloc(sizeof(char) * BUFFER_LENGTH);
    char *temp;
    int length = 0;

    if (fp == NULL) {
        return NULL;
    }

    while (fgets(input, BUFFER_LENGTH, fp) != NULL) {
        if (strlen(input) > 0) {
            /* prepare the data */
            PatiantData *data = malloc(sizeof(PatiantData));
            stripNewline(input);

            /* read in the patient ID */
            length = strchr(input, ' ') - input;
            data->id = malloc(sizeof(char) * (length + 1));
            strncpy(data->id, input, length);
            data->id[length] = 0;

            /* read in the priority and symptom code */
            temp = input + length + 1;
            data->symptom = malloc(sizeof(char) * 3);
            data->symptom[2] = 0;
            sscanf(temp, "%d %c%c", &data->priority, &data->symptom[0], &data->symptom[1]);

            /* add to the queue */
            pushPriorityQueue(triageData, data, data->priority);
        }
    }

    printf("All data read in\n");
    while (!isEmptyPriorityQueue(triageData)) {
        PatiantData *pd = popPriorityQueue(triageData);
        printf("removed patient: id = %s, priority = %d, symptom = %s\n", pd->id, pd->priority, pd->symptom);
    }

    free(input);

    return triageData;
}

void writeTriageReport(char *fileName)
{

}

void destroyData(void *data)
{

}

void stripNewline(char *str)
{
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = 0;
    }
}
