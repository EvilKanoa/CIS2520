/**
 * @file testing.c
 * @author Kanoa Haley - 0956712 - khaley@mail.uoguelph.ca
 * @date July 7, 2017
 * @brief File containing tests for a priority queue
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "PriorityQueueAPI.h"
#include "triage.h"

int main()
{
    char result = 0;

    printf("Generating test reports without an arrival time from the testSample[1-4].txt files in the assets folder\n");

    result += triage("assets/testSample1.txt", "testReport1-noclock.txt", 0);
    result += triage("assets/testSample2.txt", "testReport2-noclock.txt", 0);
    result += triage("assets/testSample3.txt", "testReport3-noclock.txt", 0);
    result += triage("assets/testSample4.txt", "testReport4-noclock.txt", 0);

    if (result == 0) {
        printf("Done, the results are in the testReport[1-4]-noclock.txt files\n");
    } else {
        printf("Error while running triage program, exiting!\n");
        return result;
    }

    printf("Generating test reports with a randomly generated arrival time from the testSample[1-4].txt files in the assets folder\n");

    result += triage("assets/testSample1.txt", "testReport1-clock.txt", 1);
    result += triage("assets/testSample2.txt", "testReport2-clock.txt", 1);
    result += triage("assets/testSample3.txt", "testReport3-clock.txt", 1);
    result += triage("assets/testSample4.txt", "testReport4-clock.txt", 1);

    if (result == 0) {
        printf("Done, the results are in the testReport[1-4]-clock.txt files\n");
    } else {
        printf("Error while running triage program, exiting!\n");
        return result;
    }

    return 0;
}
