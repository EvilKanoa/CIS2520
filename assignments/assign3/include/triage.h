/**
 * @file triage.c
 * @author Kanoa Haley - 0956712 - khaley@mail.uoguelph.ca
 * @date July 18, 2017
 * @brief File containing the definitions for the priority queue based triage
 *        application.
 */

#include <stdlib.h>

#include "PriorityQueueAPI.h"

#define OUTPUT_FILE "report.txt"
#define AGE_PRIORITY_SCALE 0.1
#define TOTAL_TIME 50
#define BUFFER_LENGTH 256

/** Struct to contain patient data while simulating */
typedef struct PatiantData {
    /* patient data */
    char *id;
    int priority;
    char *symptom;

    /* time data */
    int arrivalTime;
} PatiantData;

/**Function to use a priority queue to run the triage program
 *@param inputFileName sample file path
 *@param outputFileName report file path
 *@param randomArrival 1 to generate a random arrival time, 0 otherwise
 *@return 0 if the program run successfully, !=0 otherwise
 */
int triage(char *inputFileName, char *outputFileName, int randomArrival);

/**Function read in a triage file to a priority queue
 *@param fileName sample file path
 *@param randomArrival 1 to generate a random arrival time, 0 otherwise
 *@return the data from the sample file
 */
PriorityQueue *readTriageFile(char *fileName, int randomArrival);

/**Function to output a report of a triage queue
 *@param fileName report file path
 *@return 0 if the program run successfully, !=0 otherwise
 */
int writeTriageReport(char *fileName, PriorityQueue *queue);

/**Function to destory triage data
 *@param data a patient data struct
 */
void destroyData(void *data);

/**Function to remove a trailing newline from a string
 *@param str string to strip the newline from
 */
void stripNewline(char *str);
