#include <stdio.h>
#include <string.h>

#define linebreak printf("\n")

#define MAX_LENGTH 10
#define USER 1

void printAllUsers(const char arr[][MAX_LENGTH], size_t size)
{
    printf("All users:\n");
    for (size_t i = 0; i < size; i++)
    {
        printf("User %d : %s\n", i + 1, arr[i]);
    }
}

void printMenu()
{
    printf("MENU\n");
    printf("1-Show all users\n");
    printf("2-Change your username\n");
    printf("3-EXIT\n");
    printf("Choose an option: ");
}

int main()
{
    char usernames[][MAX_LENGTH] = {
        "ahmet699",
        "ugurpasa4",
        "muratti",
    };

    printf("Welcome %s!\n", usernames[USER]);

    int option = -1;

    while (option != 3)
    {
        printf("\n");
        printMenu();
        scanf("%d", &option);
        printf("%d\n\n", option);

        switch (option)
        {
        case 1:
            printAllUsers(usernames, sizeof(usernames) / sizeof(usernames[0]));
            break;
        case 2:
            printf("Enter new username: ");
            char new[100];
            scanf("%s", new);
            printf("%s\n", new);
            strncpy(usernames[USER], new, MAX_LENGTH - 1);
            usernames[USER][MAX_LENGTH - 1] = '\0';
            break;
        case 3:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid option!\n");
            break;
        }
    }

    return 0;
}
