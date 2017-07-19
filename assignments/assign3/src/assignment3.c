/**
 * @file triage.c
 * @author Kanoa Haley - 0956712 - khaley@mail.uoguelph.ca
 * @date July 18, 2017
 * @brief File containing the main function for the triage application.
 */

 #include <stdio.h>
 #include "triage.h"

int main(int argc, char *argv[]) {
    int result;
    if (argc != 2) {
        printf("Invalid arguments!\nUse \"%s [data file]\" to run\n", argv[0]);
        return -1;
    } else {
        printf("Running triage simulation using data file: %s\n", argv[1]);
        result = triage(argv[1], OUTPUT_FILE, 1);
        return result;
    }
}
