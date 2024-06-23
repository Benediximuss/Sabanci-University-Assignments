#include <stdio.h>
#include <string.h>

#define MAX_NOTES 4
#define MAX_LENGTH 20
#define TARGET_COMMENT 1

void printAllNotes(const char arr[][MAX_LENGTH])
{
    for (int i = 0; i < MAX_NOTES; i++)
    {
        printf("Note %d : %s\n", i + 1, arr[i]);
    }
    printf("\n");
}

int main()
{
    char notes[MAX_NOTES][MAX_LENGTH] = {
        "750 TL",
        "Do CS437 LAB!",
        "Password: 1234",
        "Call UMUT for match",
    };

    printf("All Notes:\n");
    printAllNotes(notes);

    char addition[MAX_LENGTH];
    printf("Append to %d. note: ", TARGET_COMMENT);
    fgets(addition, sizeof(addition), stdin);
    printf("%s\n", addition);

    strcat(notes[TARGET_COMMENT], addition);

    printf("\nUpdated notes:\n");
    printAllNotes(notes);

    return 0;
}
