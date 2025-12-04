#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h> //errno.h for error handling

// Dynamic memory allocation is used throughout this program because
// the number of lines is NOT known at compile time. Using malloc,
// realloc, and free allows the program to allocate only the memory
// needed, instead of wasting memory with a large static array.

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

    // Here we realloc the pointer array dynamically to make space for the new line if array is already full.
    // This avoids allocating a giant fixed array in advance.
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

    // We allocate memory = strlen + 1, to account for line + the null terminator.
    // we allocate using malloc to only reserve space for the exact amount of memory needed.
    // This dynamic allocation reduces memory usage drastically.

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

    // memmove shifts only pointers at the meory location, not entire strings.
    // This is extremely efficient because each pointer is only 8 bytes,
    // whereas copying the whole strings would be slow and wasteful.

    int moveCount = (*size - index - 1); // number of pointers to move, -1 to only move one line
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

    while (getchar() != '\n') // clear buffer
        ;

    char buffer[1000];
    printf("Enter a line: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        perror("Error reading input");
        return;
    }
    buffer[strcspn(buffer, "\n")] = '\0';

    char *line = malloc(strlen(buffer) + 1);
    if (!line)
    {
        perror("Malloc failed in insertLine");
        return;
    }
    strcpy(line, buffer);

    // insertLine will shift pointers to make space for the new one.
    // We reallocate lines array to size+1 because insert always increases count.

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

    // shift pointers forward
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
        free(lines[index]); // old memory freed to avoid leaks

    char *line = malloc(strlen(buffer) + 1);
    if (!line)
    {
        perror("Malloc failed in editLine");
        return;
    }
    strcpy(line, buffer); // copying new line to dynamially allocated memory
    lines[index] = line;  // setting line[index] to new line

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

    // down to exactly the number of stored lines.
    // This ensures no unused pointer slots remain allocated.

    // This is important for memory efficiency when many deletions occur, because if too many lines are deleted,
    // The capoacity will remain the same and the program will have a lot of unused memory, which is not nice.

    char **newLines = realloc(*linesPtr, size * sizeof(char *));
    if (!newLines && size > 0)
    {
        perror("Realloc failed during shrinkToFit");
        return;
    }

    *linesPtr = newLines;
    *capacity = size;

    printf("ShrinkToFit applied: capacity is now %d.\n", *capacity);
}

void freeAll(char **lines, int size)
{
    // Every string was individually allocated,
    // so we must free each one to avoid memory leaks.

    for (int i = 0; i < size; i++)
    {
        free(lines[i]);
    }
    free(lines);
    printf("\nAll lines have been freed.\n");
}

void saveToFile(char **lines, int size)
{
    FILE *fp = fopen("lines.dat", "w");
    if (fp == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    // We write each line exactly as typed. Since each line has dynamically
    // allocated exact memory, we save only the real content, no extra lines
    for (int i = 0; i < size; i++)
    {
        fprintf(fp, "%s\n", lines[i]);
    }

    fclose(fp);
    printf("File saved successfully.\n");
}

void loadFromFile(char ***linesPtr, int *size, int *capacity)
{
    FILE *fp = fopen("lines.dat", "r");
    if (fp == NULL)
    {
        printf("File open failed!\n");
        return;
    }

    // free old data
    for (int i = 0; i < *size; i++)
    {
        free((*linesPtr)[i]);
    }
    free(*linesPtr);

    // reset
    *size = 0;
    *capacity = 2;
    *linesPtr = malloc(*capacity * sizeof(char *));

    char buffer[1000];

    while (fgets(buffer, sizeof(buffer), fp) != NULL) // read lines from file instead of user using fp instead of stdin
    {
        buffer[strcspn(buffer, "\n")] = '\0';

        if (*size == *capacity)
        {
            *capacity *= 2;
            char **newLines = realloc(*linesPtr, (*capacity) * sizeof(char *));
            if (newLines == NULL)
            {
                printf("Realloc failed while loading!\n");
                fclose(fp);
                return;
            }
            *linesPtr = newLines;
        }

        char *line = malloc(strlen(buffer) + 1);
        strcpy(line, buffer);
        (*linesPtr)[*size] = line;
        (*size)++;
    }

    fclose(fp);
    printf("File loaded successfully.\n");
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
        printf("\n6. Free all lines");
        printf("\n7. Save to file");
        printf("\n8. Load from file");
        printf("\n9. Exit\n");
        printf("\nWhat do you want to do?: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addLine(&lines, &size, &capacity);
            break;

        case 2:
            if (size == 0)
            {
                printf("No lines exist. Add a line first.\n");
                break;
            }
            deleteLine(&lines, &size);
            if (capacity >= size * 2)
            { // condition to only apply shrinkToFit if size is really small than capacity
                shrinkToFit(&lines, size, &capacity);
            }
            break;

        case 3:
            if (size == 0)
            {
                printf("No lines to display. Add a line first.\n");
                break;
            }
            printLines(lines, size);
            break;

        case 4:
            if (size == 0)
            {
                printf("No lines to edit. Add a line first.\n");
                break;
            }
            editLine(lines, size);
            break;

        case 5:
            if (size == 0)
            {
                printf("No lines exist. Use Add Line instead of Insert first.\n");
                break;
            }
            insertLine(&lines, &size);
            break;

        case 6:
            if (size == 0)
            {
                printf("Nothing to free. No lines exist.\n");
                break;
            }
            freeAll(lines, size);
            break;

        case 7:
            if (size == 0)
            {
                printf("Nothing to save. Add a line first.\n");
                break;
            }
            saveToFile(lines, size);
            break;

        case 8:
            if (size == 0)
            {
                printf("Nothing to save. Add a line first.\n");
                break;
            }
            loadFromFile(&lines, &size, &capacity);
            break;

        case 9:
            printf("\nGoodbye!\n");
            return 0;

        default:
            printf("Invalid choice.\n");
            break;
        }

    } while (choice != 9);

    for (int i = 0; i < size; i++)
    {
        free(lines[i]);
    }
    free(lines);

    return 0;
}
