/**
 * @file triage.c
 * @author Kanoa Haley - 0956712 - khaley@mail.uoguelph.ca
 * @date July 18, 2017
 * @brief File containing the main function for the triage application.
 */

 #include <stdio.h>
 #include <string.h>
 #include "triage.h"

int main(int argc, char *argv[]) {
    int result;
    if (argc != 3) {
        printf("Invalid arguments!\n");
        printf("Use \"%s preserve [data file]\" to run without random arrival times\n", argv[0]);
        printf("Use \"%s random [data file]\" to run with random arrival times\n", argv[0]);
        return -1;
    } else {
        if (strcmp(argv[1], "preserve") == 0) {
            printf("Running triage simulation without random arrival times using data file: %s\n", argv[2]);
            result = triage(argv[2], OUTPUT_FILE, 0);
            return result;
        } else if (strcmp(argv[1], "random") == 0) {
            printf("Running triage simulation with random arrival times using data file: %s\n", argv[2]);
            result = triage(argv[2], OUTPUT_FILE, 1);
            return result;
        } else {
            printf("Invalid arguments!\n");
            printf("Use \"%s preserve [data file]\" to run without random arrival times\n", argv[0]);
            printf("Use \"%s random [data file]\" to run with random arrival times\n", argv[0]);
            return -1;
        }
    }
}
