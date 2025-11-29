#include <stdio.h>

typedef struct
{
    int bookID;
    int popularity;
    int lastAccessTime;
} Book;

Book shelf[100];
int capacity;
int shelfSize = 0;
int globalTimer = 0;

void addBook(int id, int popularity)
{
    globalTimer++;

    for (int i = 0; i < shelfSize; i++)
    {
        if (shelf[i].bookID == id)
        {
            shelf[i].popularity = popularity;
            shelf[i].lastAccessTime = globalTimer;
            return;
        }
    }

    if (shelfSize < capacity)
    {
        shelf[shelfSize].bookID = id;
        shelf[shelfSize].popularity = popularity;
        shelf[shelfSize].lastAccessTime = globalTimer;
        shelfSize++;
        return;
    }

    int leastRecentIndex = 0;
    for (int i = 1; i < shelfSize; i++)
    {
        if (shelf[i].lastAccessTime < shelf[leastRecentIndex].lastAccessTime)
        {
            leastRecentIndex = i;
        }
    }

    shelf[leastRecentIndex].bookID = id;
    shelf[leastRecentIndex].popularity = popularity;
    shelf[leastRecentIndex].lastAccessTime = globalTimer;
}

int accessBook(int id)
{
    globalTimer++;

    for (int i = 0; i < shelfSize; i++)
    {
        if (shelf[i].bookID == id)
        {
            shelf[i].lastAccessTime = globalTimer;
            return shelf[i].popularity;
        }
    }

    return -1;
}

int main()
{
    int numOfOperations;
    printf("\nEnter the capacity and number of operations: ");
    scanf("%d %d", &capacity, &numOfOperations);

    do
    {
        int choice;
        printf("\n\n==========25k-2533 Library Shelf System==========");
        printf("\n1. ADD Book");
        printf("\n2. ACCESS Book");
        printf("\n3. EXIT");
        printf("\nwhich operation do you want to perform?: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            int bookID, popularity;
            printf("\nEnter book ID and popularity: ");
            scanf("%d %d", &bookID, &popularity);
            addBook(bookID, popularity);
            break;
        }
        case 2:
        {
            int bookID;
            printf("\nEnter book ID: ");
            scanf("%d", &bookID);
            int result = accessBook(bookID);
            printf("%d\n", result);
            break;
        }
        case 3:
        {
            printf("\nGoodbye!\n");
            return 0;

        }
            break;
        default:
            printf("\nInvalid choice. Please try again.\n");
            break;
        }
        numOfOperations--;
    } while (numOfOperations != 0);
}
