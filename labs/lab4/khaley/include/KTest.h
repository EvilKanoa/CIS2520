/**
 * @file KTest.h
 * @author Kanoa Haley - 0956712 - khaley@mail.uoguelph.ca
 * @date May 27, 2017
 * @brief File containing the definitions for an extermly basic testing suite for unit testing code
 */

#ifndef _KTEST_
#define _KTEST_

#define RED_COLOUR "\x1B[31m"
#define GREEN_COLOUR "\x1B[32m"
#define RESET_COLOUR "\x1B[0m"

/**
 * A context with the required variables for testing an application or a portion of an application
 */
typedef struct context {
    char *programName;
    char *section;
    int passCount;
    int failCount;
} TestingContext;

/**
 * Creates a new context for unit testing an application or module
 * @return newly created context for testing with all variables set to the correct defaults
 * @param programName name of the program (or module) that this context is testing
 */
TestingContext *newContext(char *programName);

/**
 * Updates information in the context and displays test information
 * @pre context should have already been created with newContext
 * @param context the current testing context
 */
void test(TestingContext *context, char *description, int result);

/**
 * Prints a new section header and updates the context
 * @pre context should have already been created with newContext
 * @param context the current testing context
 * @param section section of code or function being tested
 */
void section(TestingContext *context, char *section);

/**
 * Manually hook for running your own testing logic - called when a test passes
 * @pre context should have already been created with newContext
 * @param context the current testing context
 * @param describe simple description of the test
 */
void pass(TestingContext *context, char *describe);

/**
 * Manually hook for running your own testing logic - called when a test fails
 * @pre context should have already been created with newContext
 * @param context the current testing context
 * @param describe simple description of the test
 */
void fail(TestingContext *context, char *describe);

/**
 * Called to begin a testing session
 * @pre context should have already been created with newContext
 * @param context the current testing context
 */
void begin(TestingContext *context);

/**
 * Called when a testing session has been completed to display final statistics
 * @pre context should have already been created with newContext
 * @param context the current testing context
 */
void done(TestingContext *context);

/**
 * Prints a line of information related to the current tests
 * @pre context should have already been created with newContext
 * @param string the line of info to be printed
 */
void tprint(TestingContext *context, char *string);

#endif
