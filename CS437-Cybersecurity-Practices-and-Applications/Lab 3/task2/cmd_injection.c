#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void convertAndWriteToFile(const char *input, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int length = strlen(input);
    for (int i = 0; i < length; i++) {
        fprintf(file, "%02x", input[i]);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <alphabetical_string> <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *inputString = argv[1];
    const char *outputFilename = argv[2];

    convertAndWriteToFile(inputString, outputFilename);

    // Use the system command to print the file content
    char command[100];
    snprintf(command, sizeof(command), "cat %s", outputFilename);
    system(command);

    return 0;
}
