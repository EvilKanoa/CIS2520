/**
 * @file fourwaystop.c
 * @author Kanoa Haley
 * @date June 2, 2017
 * @brief File containing the main program for simulating a four way stop sign
 *        using a queue ADT from an input file
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "../include/QueueAPI.h"
#include "../include/LinkedListAPI.h"

#define FLOAT_CMP 0.01

/**
 * Contains all the information for a car arriving at an intersection.
 */
typedef struct arrivalData {
    char road;
    char turn;
    int intersectionTime; /* the time that is listed in the data file */
    float stopTime;       /* the time in which the car reaches the front of the queue */
    float departureTime;  /* the time when the car begins crossing the intersection */
} Arrival;

/**
 * Calculates which road has the car with the right of way
 * @param roads an array of four queues for each road which may have the right of way
 * @return the queue with the car that has the right of way
 */
Queue *rightOfWay(Queue **roads);

/**
 * Checks the ability of a queue's front car to turn relative to the car on it's
 * right hand side given a time
 * @param check the queue to check the status of the front car
 * @param right the queue of the cars to the right of the checked car
 * @param time the simulation counter
 * @return the ability of the car to turn: 0 is free to turn, 1 is not arrived, 2 is not have right of way, 3 is not exists
 */
int turnStatus(Queue *check, Queue *right, float time);

/**
 * Calculates the time it takes for a certain turn to occur
 * @param turn the type of turn, either 'F', 'L', or 'R'
 * @return the time the turn takes in seconds
 */
float timeForTurn(char turn);

/**
 * Reads an input file of arrival data into a sorted linkedlist
 * @pre the file at filename must contain proper arrival data
 * @param filename file containing the arrival data
 * @return list of sorted by time arrival data
 */
List *readFile(char *filename);

/**
 * Generates and outputs a report of a simulation
 * @param intersection the queue of all arrivals at the intersection
 */
void report(Queue *intersection);

/**
 * Generates a string representing the data within the arrival and outputs it to a gven stream
 * @param arrival the data to use to generate from
 * @param stream the output stream to send the arrival text too
 */
void serializeArrival(FILE *stream, Arrival *arrival);

/**
 * Displays the data contained in an arrival struct
 * @param arrival the data to display
 */
void printArrival(void *arrival);

/**
 * Deletes an arrival struct from memory
 * @param arrival struct to delete
 */
void deleteArrival(void *arrival);

/**
 * Compares two arrival structs by time
 * @param first arrival struct to compare
 * @param second arrival struct to compare
 * @return number representing how much more the first arrival is than the second.
 *         A number >0 means first is greater, <0 means second is greater.
 */
int compareArrivals(const void *first, const void *second);

/**
 * Prints a sting to stdout as well as a specified stream
 * @param file the second stream to print too before stdout
 * @param format string used to format output
 * @param ... list of arguments for the format string
 * @return the result of the print call for the file
 */
int duelPrint(FILE *file, const char *format, ...);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Invalid arguments!");
        printf("Use \"%s <filename>\" to run the simulation", argv[0]);
        return 1;
    }

    /* read file and sort input */
    Queue *input = queueFromList(readFile(argv[1]));
    Queue *roads[4];
    roads[0] = queueCreate(printArrival, deleteArrival);
    roads[1] = queueCreate(printArrival, deleteArrival);
    roads[2] = queueCreate(printArrival, deleteArrival);
    roads[3] = queueCreate(printArrival, deleteArrival);
    while (queueLength(input) > 0) {
        Arrival *curr = (Arrival *) dequeue(input);
        Queue *road;
        switch (curr->road) {
            case 'N': road = roads[0]; break;
            case 'E': road = roads[1]; break;
            case 'S': road = roads[2]; break;
            case 'W': road = roads[3]; break;
        }
        enqueue(road, curr);
        if (queueLength(road) == 1) {
            curr->stopTime = curr->intersectionTime;
        }
    }
    queueDestroy(input);

    /* begin the simulation */
    float time = 1;
    Queue *intersection = queueCreate(printArrival, deleteArrival);
    while (queueLength(roads[0]) + queueLength(roads[1]) + queueLength(roads[2]) +
            queueLength(roads[3]) > 0) {
        Queue *activeRoad = rightOfWay(roads);
        Arrival *activeCar = (Arrival *) queuePeak(activeRoad);
        if (activeCar != NULL && activeCar->stopTime <= time + FLOAT_CMP) {
            dequeue(activeRoad);
            activeCar->departureTime = time;
            enqueue(intersection, activeCar);
            if (queuePeak(activeRoad) != NULL) {
                if (((Arrival *) queuePeak(activeRoad))->intersectionTime <= time) {
                    ((Arrival *) queuePeak(activeRoad))->stopTime = time;
                } else {
                    ((Arrival *) queuePeak(activeRoad))->stopTime = ((Arrival *) queuePeak(activeRoad))->intersectionTime;
                }
            }
            time += timeForTurn(activeCar->turn);
        } else {
            time += 1;
        }
    }

    /* output the report and finish up */
    report(intersection);
    queueDestroy(intersection);
    queueDestroy(roads[0]);
    queueDestroy(roads[1]);
    queueDestroy(roads[2]);
    queueDestroy(roads[3]);

    return 0;
}

Queue *rightOfWay(Queue **roads)
{
    /* determine if there was a car that arrived first */
    Queue *ready;
    int carsReady[4];
    carsReady[0] = 0; carsReady[1] = 0; carsReady[2] = 0; carsReady[3] = 0;
    int carsReadyCount = 0;
    int i;
    for (i = 0; i < 4; i++) {
        if (queuePeak(roads[i]) == NULL) {
            continue;
        } else if (carsReadyCount == 0 ||
                ((Arrival *) queuePeak(roads[i]))->stopTime < ((Arrival *) queuePeak(ready))->stopTime) {
            carsReady[0] = 0; carsReady[1] = 0; carsReady[2] = 0; carsReady[3] = 0;
            carsReadyCount = 1;
            carsReady[i] = 1;
            ready = roads[i];
        } else if ((((Arrival *) queuePeak(roads[i]))->stopTime - ((Arrival *) queuePeak(ready))->stopTime) < FLOAT_CMP) {
            carsReady[i] = 1;
            carsReadyCount++;
        }
    }

    /* describes the location of the cars that are equal in arrival to the front of their queue time.
     * considers each car ready or not as a binary digit. */
    int carsReadyDescriptor = (carsReady[0] * 1) +
                              (carsReady[1] * 2) +
                              (carsReady[2] * 4) +
                              (carsReady[3] * 8);

    if (carsReadyCount == 1) {
        return ready;
    } else if (carsReadyCount == 2) {
        switch (carsReadyDescriptor) {
            case (1 * 1) + (1 * 2) + (0 * 4) + (0 * 8):
            case (1 * 1) + (0 * 2) + (1 * 4) + (0 * 8): return roads[0];
            case (1 * 1) + (0 * 2) + (0 * 4) + (1 * 8): return roads[3];
            case (0 * 1) + (1 * 2) + (1 * 4) + (0 * 8):
            case (0 * 1) + (1 * 2) + (0 * 4) + (1 * 8): return roads[1];
            case (0 * 1) + (0 * 2) + (1 * 4) + (1 * 8): return roads[2];
        }
    } else if (carsReadyCount == 3) {
        switch (carsReadyDescriptor) {
            case (1 * 1) + (1 * 2) + (1 * 4) + (0 * 8): return roads[0];
            case (1 * 1) + (1 * 2) + (0 * 4) + (1 * 8): return roads[3];
            case (1 * 1) + (0 * 2) + (1 * 4) + (1 * 8): return roads[2];
            case (0 * 1) + (1 * 2) + (1 * 4) + (1 * 8): return roads[1];
        }
    } else if (carsReadyCount == 4) {
        return roads[0];
    }

    /* if the right of way algorithm somehow fails this will choose some road which works */
    for (int i = 0; i < 4; i++) {
        if (queuePeak(roads[i]) != NULL) {
            return roads[i];
        }
    }
    return NULL;
}

float timeForTurn(char turn)
{
    switch (turn) {
        case 'F': return 2.0;
        case 'R': return 1.5;
        case 'L': return 3.5;
        default: return 0.0;
    }
}

List *readFile(char *filename)
{
    FILE *in = fopen(filename, "r");
    if (in == NULL) {
        return NULL;
    }

    List *list = initializeList(printArrival, deleteArrival, compareArrivals);
    char road;
    char turn;
    int time;

    while (!feof(in))
    {
        if (fscanf(in, "%c %c %8d\n", &road, &turn, &time) != 3) {
            break;
        }
        Arrival *tempArrival = malloc(sizeof(Arrival));
        tempArrival->road = road;
        tempArrival->turn = turn;
        tempArrival->intersectionTime = time;
        tempArrival->stopTime = -1;
        tempArrival->departureTime = -1;
        insertSorted(list, tempArrival);
    }

    fclose(in);
    return list;
}

void report(Queue *intersection)
{
    FILE *out = fopen("report.txt", "w");

    duelPrint(out, "********\nTimeline\n********\n");
    float maxWait = 0;
    float nTotalWait = 0, eTotalWait = 0, sTotalWait = 0, wTotalWait = 0;
    int nCount = 0, eCount = 0, sCount = 0, wCount = 0;

    Node *node = intersection->list->head;
    Arrival *arrival;
    while (node != NULL) {
        arrival = (Arrival *) node->data;
        serializeArrival(out, arrival);
        serializeArrival(stdout, arrival);
        float wait = arrival->departureTime - arrival->intersectionTime;
        if (wait > maxWait) {
            maxWait = wait;
        }
        switch (arrival->road) {
            case 'N':
                nTotalWait += wait;
                nCount++;
                break;
            case 'E':
                eTotalWait += wait;
                eCount++;
                break;
            case 'S':
                sTotalWait += wait;
                sCount++;
                break;
            case 'W':
                wTotalWait += wait;
                wCount++;
                break;
        }
        node = node->next;
    }

    duelPrint(out, "\n***********************\nMaximum Wait Time: %.2f\n***********************\n",
        maxWait);
    duelPrint(out, "\n***********************\nAverage Wait Time: %.2f\n***********************\n\n",
        maxWait / (nCount + eCount + sCount + wCount));
    duelPrint(out, "******************\nAverage Wait Times\n******************\n");
    duelPrint(out, "North: %.2f\n", nTotalWait / nCount);
    duelPrint(out, "East: %.2f\n",  eTotalWait / eCount);
    duelPrint(out, "South: %.2f\n", sTotalWait / sCount);
    duelPrint(out, "West: %.2f\n", wTotalWait / wCount);

    fclose(out);
}

void serializeArrival(FILE *stream, Arrival *arrival)
{
    fprintf(stream,
        "%c %c %d (Car on road %c arrived at %d and stopped at %.1f then turned %c at %.1f)\n",
        arrival->road, arrival->turn, arrival->intersectionTime, arrival->road,
        arrival->intersectionTime, arrival->stopTime, arrival->turn,
        arrival->departureTime);
}

void printArrival(void *arrival)
{
    serializeArrival(stdout, (Arrival *) arrival);
}

void deleteArrival(void *arrival)
{
    free(arrival);
}

int compareArrivals(const void *first, const void *second)
{
    return ((Arrival *) first)->intersectionTime - ((Arrival *) second)->intersectionTime;
}

int duelPrint(FILE *file, const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    int ret = vfprintf(file, format, ap);
    va_end(ap);
    va_start(ap, format);
    vprintf(format, ap);
    va_end(ap);
    return ret;
}
