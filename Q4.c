#include <stdio.h>

#define MAX 10

void push(int stack[], int *size, int value) {
    if (*size == MAX) {
        printf("\nStack Overflow\n");
        return;
    }
    stack[*size] = value;
    // for (int i = *size; i > 0; i--) {
    //     stack[i] = stack[i - 1];
    // }

    // stack[0] = value;
    (*size)++;
    printf("\n%d pushed to stack.\n", value);
}

void pop(int stack[], int *size) {
    if (*size == 0) {
        printf("\nStack Underflow!\n");
        printf("Please add elements to the stack before popping!.\n");
        return;
    }

     int poppedVal = stack[*size - 1]; 
    (*size)--;
    printf("\nPopped element: %d\n", poppedVal);

    // for (int i = 0; i < *size - 1; i++) {
    //     stack[i] = stack[i + 1];
    // }

}

void peek(int stack[], int size) {
    if (size == 0) {
        printf("\nStack is empty!\n");
    } else {
        printf("\nTop element: %d\n", stack[size - 1]);
    }
}

void display(int stack[], int size) {
    if (size == 0) {
        printf("\nStack is empty!\n");
        return;
    }

    printf("\nStack elements (top to bottom):\n ");
    for (int i = size-1; i >= 0; i--) {
        printf("%d\n ", stack[i]);
    }
    printf("\n");
}

int main() {
    int stack[MAX];
    int size = 0;
    int choice, value;

    printf("\nThe stack is currently empty, please PUSH elements into it before performing any actions!\n");

    do {
        printf("\n--- Stack Menu ---\n");
        printf("1. PUSH\n");
        printf("2. POP\n");
        printf("3. PEEK\n");
        printf("4. DISPLAY\n");
        printf("5. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
            char ans;
            do
            {
                printf("Enter value to PUSH into stack: ");
                scanf("%d", &value);
                push(stack, &size, value);
                printf("\nDo you want to add another element? (Y = Yes, N = No): ");
                scanf(" %c", &ans);
            } while (ans == 'Y' || ans == 'y');
                break;
            case 2:
                pop(stack, &size);
                break;
            case 3:
                peek(stack, size);
                break;
            case 4:
                display(stack, size);
                break;
            case 5:
                printf("\nExiting program.\n");
                break;
            default:
                printf("\nInvalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}
