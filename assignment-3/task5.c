#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

void addLine(char ***linesPtr, int *size, int *capacity)
{
    while (getchar() != '\n')
        ;

    char buffer[1000];
    printf("\nEnter a line: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        perror("Error reading input");
        return;
    }
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) == 0)
        return;

    char **lines = *linesPtr;

    // Check if we need to reallocate memory to lines array
    if (*size == *capacity)
    {
        *capacity *= 2;

        char **newLine = realloc(lines, (*capacity) * sizeof(char *));
        if (newLine == NULL)
        {
            perror("Realloc failed in addLine");
            return;
        }

        lines = newLine;
        *linesPtr = lines;
    }

    // Allocate exact memory for the new string
    char *line = malloc((strlen(buffer) + 1) * sizeof(char));
    if (!line)
    {
        perror("Malloc failed in addLine");
        return;
    }
    strcpy(line, buffer);

    lines[*size] = line;
    (*size)++;
    printf("Line added successfully.\n");
}

void deleteLine(char ***linesPtr, int *size)
{
    char **lines = *linesPtr;
    printf("\nEnter the line number to delete: ");
    int lineNumber;
    scanf("%d", &lineNumber);

    if (lineNumber < 1 || lineNumber > *size)
    {
        printf("Invalid line number.\n");
        return;
    }

    int index = lineNumber - 1;

    if (lines[index] != NULL)
    {
        free(lines[index]);
        lines[index] = NULL;
    }

    int moveCount = (*size - index - 1);
    if (moveCount > 0)
        memmove(&lines[index], &lines[index + 1], moveCount * sizeof(char *));

    lines[*size - 1] = NULL;
    (*size)--;

    printf("Deleted line %d.\n", lineNumber);
}

void insertLine(char ***linesPtr, int *size)
{
    if (linesPtr == NULL || *linesPtr == NULL || size == NULL)
    {
        printf("Internal error.\n");
        return;
    }

    char **lines = *linesPtr;

    printf("\nEnter the line number to insert: ");
    int lineNumber;
    scanf("%d", &lineNumber);

    if (lineNumber < 1 || lineNumber > *size + 1)
    {
        printf("Invalid line number.\n");
        return;
    }

    while (getchar() != '\n')
        ;

    char buffer[1000];
    printf("Enter a line: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        perror("Error reading input");
        return;
    }
    buffer[strcspn(buffer, "\n")] = '\0';

    // Allocate memory for new string
    char *line = malloc(strlen(buffer) + 1);
    if (!line)
    {
        perror("Malloc failed in insertLine");
        return;
    }
    strcpy(line, buffer);

    char **newLines = realloc(lines, (*size + 1) * sizeof(char *));
    if (!newLines)
    {
        perror("Realloc failed in insertLine");
        free(line);
        return;
    }
    lines = newLines;
    *linesPtr = lines;

    int index = lineNumber - 1;

    int moveCount = (*size - index);
    if (moveCount > 0)
        memmove(&lines[index + 1], &lines[index], moveCount * sizeof(char *));

    lines[index] = line;
    (*size)++;

    printf("Inserted line %d.\n", lineNumber);
}

void editLine(char **lines, int size)
{
    printf("\nEnter the line number to edit: ");
    int lineNumber;
    scanf("%d", &lineNumber);

    if (lineNumber < 1 || lineNumber > size)
    {
        printf("Invalid line number.\n");
        return;
    }

    int index = lineNumber - 1;
    while (getchar() != '\n')
        ;

    char buffer[1000];
    printf("Enter a line: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        perror("Error reading input");
        return;
    }
    buffer[strcspn(buffer, "\n")] = '\0';

    if (lines[index] != NULL)
        free(lines[index]);

    char *line = malloc(strlen(buffer) + 1);
    if (!line)
    {
        perror("Malloc failed in editLine");
        return;
    }
    strcpy(line, buffer);
    lines[index] = line;

    printf("Edited line %d.\n", lineNumber);
}

void printLines(char **lines, int size)
{
    if (lines == NULL)
    {
        printf("No lines to print.\n");
        return;
    }

    for (int i = 0; i < size; i++)
        printf("Line %d: %s\n", i + 1, lines[i]);
}

void shrinkToFit(char ***linesPtr, int size, int *capacity)
{
    if (linesPtr == NULL || *linesPtr == NULL)
    {
        printf("Internal error: lines array is NULL.\n");
        return;
    }

    if (size == *capacity)
    {
        return;
    }

    char **lines = *linesPtr;

    char **newLines = realloc(lines, size * sizeof(char *));
    if (!newLines && size > 0)
    {
        perror("Realloc failed during shrinkToFit");
        return;
    }

    *linesPtr = newLines;
    *capacity = size;

    printf("ShrinkToFit applied: capacity is now %d.\n", *capacity);
}

int main()
{
    char **lines;
    int size = 0, capacity = 2;

    lines = malloc(capacity * sizeof(char *));
    if (!lines)
    {
        perror("Initial malloc failed");
        return 0;
    }

    int choice;
    do
    {
        printf("\n=======Line-Based Text Editor=======");
        printf("\n1. Add a line");
        printf("\n2. Delete a line");
        printf("\n3. Display all lines");
        printf("\n4. Edit a line");
        printf("\n5. Insert a line");
        printf("\n6. Exit\n");
        printf("\nWhat do you want to do?: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            addLine(&lines, &size, &capacity);
            break;
        }
        case 2:
        {
            deleteLine(&lines, &size);
            if (capacity >= size * 2)
            {
                shrinkToFit(&lines, size, &capacity);
            }
            break;
        }
        case 3:
        {
            printLines(lines, size);
            break;
        }
        case 4:
        {
            editLine(lines, size);
            break;
        }
        case 5:
        {
            insertLine(&lines, &size);
            break;
        }
        case 6:
        {
            printf("\nGoodbye!\n");
            return 0;
            break;
        }
        default:
        {
            printf("Invalid choice.\n");
            break;
        }
        }
    } while (choice != 6);

    for (int i = 0; i < size; i++)
    {
        free(lines[i]);
    }
    free(lines);

    return 0;
}
