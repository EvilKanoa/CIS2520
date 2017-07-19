/**
 * @file triage.c
 * @author Kanoa Haley - 0956712 - khaley@mail.uoguelph.ca
 * @date July 12, 2017
 * @brief File containing the implemention for the priority queue based triage
 *        application.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "PriorityQueueAPI.h"
#include "triage.h"

int triage(char *inputFileName, char *outputFileName, int randomArrival)
{
    PriorityQueue *queue = readTriageFile(inputFileName, randomArrival);
    int result;

    if (queue == NULL) {
        printf("Error while opening %s, exiting...\n", inputFileName);
        return -2;
    }

    result = writeTriageReport(outputFileName, queue);
    destroyPriorityQueue(queue);
    if (result == 0) {
        printf("Results have been saved to: %s\n", outputFileName);
    } else {
        printf("Error while opening %s, exiting...\n", outputFileName);
        return -3;
    }

    return 0;
}

PriorityQueue *readTriageFile(char *fileName, int randomArrival)
{
    FILE *fp = fopen(fileName, "r");
    PriorityQueue *triageData = createPriorityQueue(AGE_PRIORITY_SCALE, 0, MAX_PRIORITY_QUEUE, destroyData, NULL);
    char *input = malloc(sizeof(char) * BUFFER_LENGTH);
    char *temp;
    int length = 0;

    if (fp == NULL || triageData == NULL) {
        return NULL;
    }

    if (randomArrival == 1) {
        /* seed the random generator */
        srand(time(NULL));
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
            if (randomArrival == 1) {
                data->arrivalTime = (rand() % TOTAL_TIME) + 1;
                triageData->tickCount = data->arrivalTime - TOTAL_TIME;
            } else {
                data->arrivalTime = -1;
            }
            pushPriorityQueue(triageData, data, data->priority);
        }
    }

    triageData->tickCount = TOTAL_TIME;

    free(input);
    fclose(fp);

    return triageData;
}

int writeTriageReport(char *fileName, PriorityQueue *queue)
{
    FILE *fp = fopen(fileName, "w");
    PatiantData *node;
    int prevTime = 0;
    int waitTime;
    int count;
    int totalWait = 0;

    if (fp == NULL || queue == NULL) {
        return -1;
    }

    count = queue->heap->size;

    while (!isEmptyPriorityQueue(queue)) {
        node = popPriorityQueue(queue);
        if (node->arrivalTime == -1) {
            fprintf(fp, "%s, %s, %d\n", node->id, node->symptom, node->priority);
        } else {
            waitTime = prevTime - node->arrivalTime;
            prevTime = node->arrivalTime + 1;
            if (waitTime < 0) {
                waitTime = 0;
            }
            totalWait += waitTime;
            fprintf(fp, "%s, %s, %d, %d, %d\n", 
                node->id,
                node->symptom,
                node->priority,
                node->arrivalTime,
                waitTime);
            
            if (isEmptyPriorityQueue(queue)) {
                fprintf(fp, "Total Time: %d, Average Wait Time: %.2f\n", TOTAL_TIME, (double) totalWait / (double) count);
            }
        }
        destroyData(node);
    }

    fclose(fp);

    return 0;
}

void destroyData(void *data)
{
    PatiantData *pd = (PatiantData *) data;
    free(pd->id);
    free(pd->symptom);
    free(pd);
}

void stripNewline(char *str)
{
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = 0;
    }
}
