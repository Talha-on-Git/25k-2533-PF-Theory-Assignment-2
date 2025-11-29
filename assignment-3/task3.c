#include <stdio.h>
#include <string.h>

typedef struct
{
    int employeeID;
    char name[40];
    char designation[40];
    int salary;
} Employee;

void addEmployees(int *numOfEmployees, Employee employees[])
{
    int n;
    printf("\nHow many employee records do yo want to add?: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("\nEnter employee id for employee %d: ", i + 1);
        scanf("%d", &employees[*numOfEmployees + i].employeeID);
        while (getchar() != '\n')
            ;
        printf("\nEnter Name for employee %d:  ", i + 1);
        fgets(employees[*numOfEmployees + i].name, 40, stdin);
        employees[*numOfEmployees + i].name[strcspn(employees[*numOfEmployees + i].name, "\n")] = '\0';

        printf("\nEnter Designation for employee %d: ", i + 1);
        fgets(employees[*numOfEmployees + i].designation, 40, stdin);
        employees[*numOfEmployees + i].designation[strcspn(employees[*numOfEmployees + i].designation, "\n")] = '\0';

        printf("\nEnter Salary for employee %d: ", i + 1);
        scanf("%d", &employees[*numOfEmployees + i].salary);

        while (getchar() != '\n');
    }
    *numOfEmployees += n;
}

void displayEmployees(int numOfEmployees, Employee employees[])
{
    if (numOfEmployees == 0)
    {
        printf("\nadd employees first");
    }
    else
    {
        printf("\nNo.\t Employee ID \t Name \t Designation \t Salary\n");
        for (int i = 0; i < numOfEmployees; i++)
        {
            printf("%-9d|%-14d|%-8s|%-14s|%d |\n", i + 1, employees[i].employeeID, employees[i].name, employees[i].designation, employees[i].salary);
            // printf("Employee %d ID: %d\n", i+1, employees[i].employeeID);
            // printf("Employee %d Name: %s\n",i+1, employees[i].name);
            // printf("Employee %d designation: %s\n",i+1, employees[i].designation);
            // printf("Employee %d Salary: %d\n",i+1, employees[i].salary);
            // printf("\n");
        }
    }
}

void findHighestSalary(int numOfEmployees, Employee employees[])
{
    if (numOfEmployees == 0)
    {
        printf("\nadd employees first");
    }
    else
    {
        int max = 0, maxIndex = 0;
        int i;
        for (i = 0; i < numOfEmployees; i++)
        {
            if (max < employees[i].salary)
            {
                max = employees[i].salary;
                maxIndex = i;
            }
        }
        printf("\nEmployee with Id: %d (%s, %s) has highest salary = %d", employees[maxIndex].employeeID, employees[maxIndex].name, employees[maxIndex].designation, employees[maxIndex].salary);
    }
}

void searchEmployeeById(int numOfEmployees, Employee employees[], int searchId)
{
    int found = 0;
    for (int i = 0; i < numOfEmployees; i++)
    {
        if (searchId == employees[i].employeeID)
        {
            found = 1;
            printf("\nNo.\t Employee ID \t Name \t Designation \t Salary\n");
            printf("%-9d|%-14d|%-8s|%-14s|%d |\n", i + 1, employees[i].employeeID, employees[i].name, employees[i].designation, employees[i].salary);
            break;
        }
    }
    if (!found)
    {
        printf("\nEmployee not found");
    }
}
void searchEmployeeByName(int numOfEmployees, Employee employees[], char searchName[])
{
    int found = 0;
    for (int i = 0; i < numOfEmployees; i++)
    {
        if (strcmp(searchName, employees[i].name) == 0)
        {
            found = 1;
             printf("\nNo.\t Employee ID \t Name \t Designation \t Salary\n");
            printf("%-9d|%-14d|%-8s|%-14s|%d |\n", i + 1, employees[i].employeeID, employees[i].name, employees[i].designation, employees[i].salary);
            break;
        }
    }
    if (!found)
    {

        printf("\nEmployee not found");
    }
}

void giveBonus(int numOfEmployees, Employee employees[])
{
    if (numOfEmployees == 0)
    {
        printf("\nadd employees first");
    }
    else
    {
        for (int i = 0; i < numOfEmployees; i++)
        {
            if (employees[i].salary < 50000)
            {
                float bonus = employees[i].salary * 0.1;
                employees[i].salary += bonus;
                printf("\nEmployee with Id: %d (%s, %s) has got a bonus of %.2f. salary is now = %d", employees[i].employeeID, employees[i].name, employees[i].designation, bonus, employees[i].salary);
            }
            printf("\n");
        }
    }
}
int main()
{
    int numOfEmployees = 0;
    Employee employees[50];
    int choice;
    do
    {

        printf("\n\n======= ABC Technologies =======");
        printf("\n1. Add Employees");
        printf("\n2. Display Employees");
        printf("\n3. Find highest salary");
        printf("\n4. Search Employee");
        printf("\n5. Give bonus to employees (with salary<50000)");
        printf("\n6. Exit");
        printf("\nWhich operation do you want to perform?: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            char addMoreEmployees;
            do
            {
                addEmployees(&numOfEmployees, employees);
                printf("\nDo you want to add more employees? (Y/N): ");
                scanf(" %c", &addMoreEmployees);
            } while (addMoreEmployees == 'Y' || addMoreEmployees == 'y');
            break;
        case 2:
            displayEmployees(numOfEmployees, employees);
            break;
        case 3:
            findHighestSalary(numOfEmployees, employees);
            break;
        case 4:
            char findAnotherEmployee;
            if (numOfEmployees == 0)
            {
                printf("\nadd employees first befor finding");
                break;
            }
            else
            {
                do
                {
                    char find;
                    printf("\n1. Find Employee by ID");
                    printf("\n2. Find Employee by Name");
                    printf("\nWhich operation do you want to perform?: ");
                    scanf("%d", &find);
                    switch (find)
                    {
                    case 1:
                        int findID;
                        printf("\nEnter ID of Employee you want to find: ");
                        scanf("%d", &findID);
                        searchEmployeeById(numOfEmployees, employees, findID);
                        break;
                    case 2:
                        char findName[40];
                        while (getchar() != '\n')
                            ;
                        printf("\nEnter Name of Employee you want to find: ");
                        fgets(findName, 40, stdin);
                        findName[strcspn(findName, "\n")] = '\0';
                        searchEmployeeByName(numOfEmployees, employees, findName);
                        break;
                    default:
                        printf("\nInvalid choice!");
                        break;
                    }
                    printf("\nDo you want to find another employee? (Y/N): ");
                    scanf(" %c", &findAnotherEmployee);
                } while (findAnotherEmployee == 'Y' || findAnotherEmployee == 'y');
                break;
            }
        case 5:
            giveBonus(numOfEmployees, employees);
            break;
        case 6:
            printf("\nGoodbye!");
            return 0;
            break;
        default:
            break;
        }
    } while (choice != 6);
}