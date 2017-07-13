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
#include "triage.c"

int main()
{
    printf("Generating test reports from the testSample[1-4].txt files in the assets folder\n");

    triage("assets/testSample1.txt", "testReport1.txt\n");
    triage("assets/testSample2.txt", "testReport2.txt\n");
    triage("assets/testSample3.txt", "testReport3.txt\n");
    triage("assets/testSample4.txt", "testReport4.txt\n");

    printf("Done, the results are in the testReport[1-4].txt files\n");

    return 0;
}
