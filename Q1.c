#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void addNewBook(int isbns[], char titles[][50], float prices[], int quantities[], int *numOfBooks)
{
    if (*numOfBooks >= 100)
    {
        printf("Inventory is full\n");
        return;
    }
    else
    {
        int newIsbn;
        printf("Enter ISBN: ");
        scanf("%d", &newIsbn);
        for (int i = 0; i < *numOfBooks; i++)
        {
            if (isbns[i] == newIsbn)
            {
                printf("Book with this ISBN already exists\n");
                return;
            }
        }

        isbns[*numOfBooks] = newIsbn;
        printf("Enter Book Title: ");
        getchar();
        fgets(titles[*numOfBooks], 50, stdin);
        int index = strcspn(titles[*numOfBooks], "\n");
        titles[*numOfBooks][index] = '\0';

        // char ch;
        // int i = 0;

        // for (i = 0; i < 50 - 1; i++)
        // {
        //     ch = getchar();
        //     if (ch == '\n')
        //         break;
        //     titles[*numOfBooks][i] = ch;
        // }
        // titles[*numOfBooks][i] = '\0';
        printf("Enter Price: ");
        scanf("%f", &prices[*numOfBooks]);
        printf("Enter Quantity: ");
        scanf("%d", &quantities[*numOfBooks]);
        (*numOfBooks)++;

        printf("\nNew Book added successfully!\n\n");
    }
}

void processSale(int isbns[], int quantities[], int numOfBooks)
{

    if (numOfBooks == 0)
    {
        printf("No books in inventory.\n");
        return;
    }else{
        int findIsbn, numOfSoldCopies;
    printf("Enter ISBN of book to buy: ");
    scanf("%d", &findIsbn);
    printf("Enter number of copies to buy: ");
    scanf("%d", &numOfSoldCopies);

    int found  =0;
    for (int i = 0; i < numOfBooks; i++)
    {
        if (isbns[i] == findIsbn)
        {
            found = 1;
            if (quantities[i] >= numOfSoldCopies)
            {
                quantities[i] -= numOfSoldCopies;
                printf("Book bought successfully!\n");
                return;
            }
            else
            {
                printf("Not enough copies available!\n");
                return;
            }
        }
    }
    if(found == 0)
        {
            printf("Book with ISBN %d not found!\n", findIsbn);
        }
    }
    
}

void generateLowStockReport(int isbns[], char titles[][50], float prices[], int quantities[], int numOfBooks)
{
    if (numOfBooks == 0)
    {
        printf("No books in inventory.\n");
        return;
    } else{
        int found = 0;
    for (int i = 0; i < numOfBooks; i++)
    {
        if (quantities[i] < 5)
        {
            printf("ISBN: %d\n", isbns[i]);
            printf("Title: %s\n", titles[i]);
            printf("Price: %.2f\n", prices[i]);
            printf("Quantity: %d\n", quantities[i]);
            printf("\n");
            found = 1;
        }
    }
    if (found == 0)
    {
        printf("No books with low stock found!\n");
    }
    printf("\n low stock report generated successfully!\n");
    }
}

void displayInventory(int isbns[], char titles[][50], float prices[], int quantities[], int numOfBooks)
{
    if (numOfBooks == 0)
    {
        printf("No books in inventory.\n");
        return;
    }
    else
    {
        for (int i = 0; i < numOfBooks; i++)
        {
            printf("ISBN: %d\n", isbns[i]);
            printf("Title: %s\n", titles[i]);
            printf("Price: %.2f\n", prices[i]);
            printf("Quantity: %d\n", quantities[i]);
            printf("\n");
        }
    }
}
int main()
{
    int choice, numOfBooks = 0;
    int isbns[100] = {0};
    char titles[100][50] = {{0}};
    float prices[100] = {0};
    int quantities[100] = {0};
    do
    {
        printf("\n================ Liberty Books Chain Inventory Management system ================\n");
        
        printf("1. Add a new book\n");
        printf("2. Process a sale\n");
        printf("3. Generate Low-Stock Report\n");
        printf("4. Display Inventory\n");
        printf("5. Exit\n");
        printf("\nselect what you want to do: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            char addAnotherBook;
            do
            {
                addNewBook(isbns, titles, prices, quantities, &numOfBooks);
                printf("\nDo you want to add another book? (Y/N): ");
                scanf(" %c", &addAnotherBook);
            } while (addAnotherBook == 'Y' || addAnotherBook == 'y');
            break;
        case 2:
            processSale(isbns, quantities, numOfBooks);
            break;
        case 3:
            generateLowStockReport(isbns, titles, prices, quantities, numOfBooks);
            break;
        case 4:
            displayInventory(isbns, titles, prices, quantities, numOfBooks);
            break;
        case 5:
            printf("You chose to exit!\n");
            exit(0);
            break;
        default:
            printf("Invalid choice!... please pick a choice between 1-3\n");
            break;
        }
    } while (choice != 5);
    return 0;
}