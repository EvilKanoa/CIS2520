/**
 * @file KTest.c
 * @author Kanoa Haley
 * @date May 27, 2017
 * @brief File containing the implementations for an extermly basic testing suite for unit testing code
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "KTest.h"

TestingContext *newContext(char *programName)
{
    TestingContext *context = malloc(sizeof(TestingContext));
    context->programName = programName;
    context->section = "";
    context->passCount = 0;
    context->failCount = 0;
    return context;
}

void test(TestingContext *context, char *description, int result)
{
    if (result) {
        pass(context, description);
    } else {
        fail(context, description);
    }
}

void section(TestingContext *context, char *section)
{
    int i;
    context->section = section;
    printf("\n");
    for (i = 0; i < (strlen(section) * 2); i++) {
        printf("*");
    }
    printf("\nTesting %s...\n", context->section);
    for (i = 0; i < (strlen(section) * 2); i++) {
        printf("*");
    }
    printf("\n\n");
}

void pass(TestingContext *context, char *describe)
{
    context->passCount++;
    printf("Test #%d (%s %s) %spassed%s...\n", context->passCount + context->failCount, context->section, describe, GREEN_COLOUR, RESET_COLOUR);
}

void fail(TestingContext *context, char *describe)
{
    context->failCount++;
    printf("Test #%d (%s %s) %sfailed%s...\n", context->passCount + context->failCount, context->section, describe, RED_COLOUR, RESET_COLOUR);
}

void begin(TestingContext *context)
{
    printf("Testing %s...\n", context->programName);
}

void done(TestingContext *context)
{
    printf("\n----- Results -----\n");
    printf("Testing finished running %d tests...\n", context->passCount + context->failCount);
    printf("%d tests passed.\n", context->passCount);
    printf("%d tests failed.\n", context->failCount);
    printf("%.1f%% passed.\n", (context->passCount * 100.0) / (context->passCount + context->failCount));
}

void tprint(TestingContext *context, char *string)
{
    printf("INFO: (%s) %s\n", context->section, string);
}
