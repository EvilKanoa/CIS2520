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

/**
 * Contains all the information for a car arriving at an intersection.
 */
typedef struct arrivalData {
    char road;
    char turn;
    int intersectionTime;
    float stopTime;
    float departureTime;
} Arrival;

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
 * Generates a string representing the data within the arrival
 * @param arrival the data to use to generate from
 * @return string representation of the arrival struct
 */
char *serializeArrival(Arrival *arrival);

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

    // read file and sort input
    Queue *input = queueFromList(readFile(argv[1]));
    Queue *north = queueCreate(printArrival, deleteArrival);
    Queue *east = queueCreate(printArrival, deleteArrival);
    Queue *south = queueCreate(printArrival, deleteArrival);
    Queue *west = queueCreate(printArrival, deleteArrival);
    Arrival *curr;
    while (queueLength(input) > 0) {
        curr = (Arrival *) dequeue(input);
        switch (curr->road) {
            case 'N': enqueue(north, curr); break;
            case 'E': enqueue(east, curr); break;
            case 'S': enqueue(south, curr); break;
            case 'W': enqueue(west, curr); break;
        }
    }
    queueDestroy(input);

    // begin the simulation
    float time = 1;
    Queue *intersection = queueCreate(printArrival, deleteArrival);
    Arrival *arrival;
    while (queueLength(north) + queueLength(east) + queueLength(south) +
            queueLength(west) > 0) {
        if (turnStatus(north, east, time) == 0) {
            arrival = dequeue(north);
            arrival->stopTime = arrival->stopTime == -1 ? time : arrival->stopTime;
            arrival->departureTime = time;
            time += timeForTurn(arrival->turn);
            enqueue(intersection, arrival);
        } else if (turnStatus(east, south, time) == 0) {
            arrival = dequeue(east);
            arrival->stopTime = arrival->stopTime == -1 ? time : arrival->stopTime;
            arrival->departureTime = time;
            time += timeForTurn(arrival->turn);
            enqueue(intersection, arrival);
        } else if (turnStatus(south, west, time) == 0) {
            arrival = dequeue(south);
            arrival->stopTime = arrival->stopTime == -1 ? time : arrival->stopTime;
            arrival->departureTime = time;
            time += timeForTurn(arrival->turn);
            enqueue(intersection, arrival);
        } else if (turnStatus(west, north, time) == 0) {
            arrival = dequeue(west);
            arrival->stopTime = arrival->stopTime == -1 ? time : arrival->stopTime;
            arrival->departureTime = time;
            time += timeForTurn(arrival->turn);
            enqueue(intersection, arrival);
        }
    }

    // output the report and finish up
    report(intersection);
    free(intersection);
    free(north);
    free(east);
    free(south);
    free(west);

    return 0;
}

// 0 is free to turn, 1 is not arrived, 2 is not have right of way, 3 is not exists
int turnStatus(Queue *check, Queue *right, float time)
{
    Arrival *checkArrival = (Arrival *) queuePeak(check);
    Arrival *blockArrival = (Arrival *) queuePeak(right);
    if (checkArrival == NULL) {
        return 3;
    } else if (checkArrival->intersectionTime > time) {
        return 1;
    } else if (blockArrival != NULL &&
            blockArrival->intersectionTime <= checkArrival->intersectionTime) {
        checkArrival->stopTime = time;
        return 2;
    } else {
        return 0;
    }
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
    Arrival *tempArrival;

    while (!feof(in))
    {
        if (fscanf(in, "%c %c %d\n", &road, &turn, &time) != 3) {
            break;
        }
        tempArrival = malloc(sizeof(Arrival));
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
    float wait;
    Arrival *arrival;
    while (node != NULL) {
        arrival = (Arrival *) node->data;
        duelPrint(out, "%s", serializeArrival(arrival));
        wait = arrival->departureTime - arrival->intersectionTime;
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

char *serializeArrival(Arrival *arrival)
{
    char *string = malloc(sizeof(char) * 101);
    sprintf(string,
        "%c %c %d (Car on road %c arrived at %d and stopped at %.1f then turned %c at %.1f)\n",
        arrival->road, arrival->turn, arrival->intersectionTime, arrival->road,
        arrival->intersectionTime, arrival->stopTime, arrival->turn,
        arrival->departureTime);
    return string;
}

void printArrival(void *arrival)
{
    printf("%s", serializeArrival((Arrival *) arrival));
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
