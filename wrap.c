#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void usage() {
    printf("Flags:\n");
    printf("\t-r\tTo run file after successful compilation\n");
    printf("\t-w\tTo toggle -Wall -Wextra and -pedantic\n");
    printf("\t-d\tTo delete executable file\n");
}

int containsDot(char* str) {
    for (size_t i = 0; i < strlen(str); i++)
        if (str[i] == '.')
            return 1;

    return 0;
}

int main(int argc, char** argv) {
    // 1 cuz ./wrap counts
    if (argc == 1) {
        printf("\x1b[31;49;1mError: ");
        printf("\x1b[39;49mNothing provided to the wrapper\n");
        exit(1);
    }

    char fileName[254];
    strcpy(fileName, "");

    int toRun = 0;
    int fullWarnings = 0;
    int toDelete = 0;

    for (int i = 1; i < argc; i++) {
        char* arg = argv[i];

        // Checking if a flag, starts with '-'
        if (arg[0] == '-') {
            if (strcmp(arg, "-r") == 0)
                toRun = 1;
            else if (strcmp(arg, "-w") == 0)
                fullWarnings = 1;
            else if (strcmp(arg, "-d") == 0)
                toDelete = 1;
            else {
                usage();
                printf("\x1b[31;49;1mError: ");
                printf("\x1b[39;49mUnknown flag\n");
                exit(1);
            }
        }

        // Checking if arg is a file
        else if (containsDot(arg)) {
            // If arg is a file
            strcpy(fileName, strtok(arg, "."));
        } else {
            usage();
            printf("Unknown flag \"%s\"\n", arg);
            exit(1);
        }
    }

    if (strlen(fileName) == 0) {
        printf("\x1b[31;49;1mError: ");
        printf("\x1b[39;49mNo file is provided to wrapper\n");
        exit(1);
    }

    // gcc -g -o 255 -Wall -Wextra -pedantic 257
    char command[3 + 1 + 2 + 1 + 2 + 255 + 5 + 7 + 9 + 257];
    strcpy(command, "gcc -g -o");

    strcat(command, fileName);
    strcat(command, " ");

    char fullName[257];
    strcpy(fullName, fileName);
    strcat(fullName, ".c"); // fileName with extension

    strcat(command, fullName);

    if (fullWarnings) {
        strcat(command, " -Wall -Wextra -pedantic");
    }

    int exit_status = system(command); // Main command launch

    if (exit_status == 0) // Successful compilation
        printf("\x1b[32;49;1;3mSuccessful compilation\n");
    else {
        toRun = 0;
        toDelete = 0;
    }

    printf("\x1b[0m");

    if (toRun) {
        strcpy(command, "");
        strcat(command, "./");
        strcat(command, fileName);
        printf("\x1b[35;3;1mRunning \"\x1b[37m%s\x1b[35;3;1m\"\x1b[0m\x1b[31m.\x1b[32m.\x1b[34m.\n", fullName);
        printf("\x1b[0m\n");
        system(command);
    }

    if (toDelete) {
        strcpy(command, "");
        strcat(command, "rm ");
        strcat(command, fileName);
        system(command);
    }
}
