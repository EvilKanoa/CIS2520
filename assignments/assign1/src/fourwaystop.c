/**
 * @file fourwaystop.c
 * @author Kanoa Haley
 * @date June 2, 2017
 * @brief File containing the main program for simulating a four way stop sign
 *        using a queue ADT from an input file
 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/QueueAPI.h"
#include "../include/LinkedListAPI.h"

/**
 * Contains all the information for a car arriving at an intersection.
 */
typedef struct arrivalData {
    char road;
    char turn;
    int time;
} Arrival;

/**
 * Reads an input file of arrival data into a sorted linkedlist
 * @pre the file at filename must contain proper arrival data
 * @param filename file containing the arrival data
 * @return list of sorted by time arrival data
 */
List *readFile(char *filename);

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

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Invalid arguments!");
        printf("Use \"%s <filename>\" to run the simulation", argv[0]);
        return 1;
    }

    List *input = readFile(argv[1]);
    printForward(input);

     return 0;
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
        tempArrival->time = time;
        insertSorted(list, tempArrival);
    }

    fclose(in);
    return list;
}

void deleteArrival(void *arrival)
{
    free(arrival);
}

int compareArrivals(const void *first, const void *second)
{
    return ((Arrival *) first)->time - ((Arrival *) second)->time;
}

void printArrival(void *arrival)
{
    Arrival *data = (Arrival *) arrival;
    printf("%c %c %d\n", data->road, data->turn, data->time);
}
