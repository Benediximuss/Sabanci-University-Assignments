#include <stdio.h>
#include <stdlib.h>

#define MAX_ITEMS 10
#define MAX_DAYS 7

// Structure to represent a shopping item
struct ShoppingItem {
    char name[50];
    float price;
};

// Structure to represent a day's shopping list
struct ShoppingDay {
    struct ShoppingItem items[MAX_ITEMS];
    int itemCount;
};

// Function to add a shopping item to a day's list
void addItem(struct ShoppingDay *day, const char *name, float price) {
    if (day->itemCount < MAX_ITEMS) {
        struct ShoppingItem newItem;
        snprintf(newItem.name, sizeof(newItem.name), "%s", name);
        newItem.price = price;
        day->items[day->itemCount++] = newItem;
        printf("Item added successfully.\n");
    } else {
        printf("Error: Maximum number of items reached for the day.\n");
    }
}

// Function to display a day's shopping list
void displayDay(struct ShoppingDay *day, int dayNumber) {
    printf("Shopping list for Day %d:\n", dayNumber);
    for (int i = 0; i < day->itemCount; ++i) {
        printf("%d. %s - $%.2f\n", i + 1, day->items[i].name, day->items[i].price);
    }
    printf("\n");
}

int main() {
    struct ShoppingDay week[MAX_DAYS]; // Array to store shopping lists for each day

    for (int i = 0; i < MAX_DAYS; ++i) {
        week[i].itemCount = 0; // Initialize item count for each day
    }

    int choice, day;
    char itemName[50];
    float itemPrice;

    do {
        printf("1. Add item to a day's shopping list\n");
        printf("2. Display a day's shopping list\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the day number (1-7): ");
                scanf("%d", &day);
                if (day >= 1 && day <= MAX_DAYS) {
                    printf("Enter item name: ");
                    scanf("%s", itemName);
                    printf("Enter item price: ");
                    scanf("%f", &itemPrice);
                    addItem(&week[day - 1], itemName, itemPrice);
                } else {
                    printf("Error: Invalid day number.\n");
                }
                break;
            case 2:
                printf("Enter the day number (1-7): ");
                scanf("%d", &day);
                if (day >= 1 && day <= MAX_DAYS) {
                    displayDay(&week[day - 1], day);
                } else {
                    printf("Error: Invalid day number.\n");
                }
                break;
            case 3:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 3);

    return 0;
}
