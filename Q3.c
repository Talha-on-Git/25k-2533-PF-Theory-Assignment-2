#include <stdio.h>

void updateSectorStatus(int sectors[][3])
{
    int row, col;
    printf("\nEnter Sector row: ");
    scanf("%d", &row);
    printf("\nEnter Sector column: ");
    scanf("%d", &col);
    if (row < 0 || row > 2)
    {
        printf("\nPlease enter valid row number!");
    }
    else if (col < 0 || col > 2)
    {
        printf("\nPlease enter valid column number!");
    }
    else
    {
        int bit;
        printf("\nSelect the setting to change:");
        printf("\n0: Power Status (1 = ON, 0 = OFF)");
        printf("\n1: Overload Warning (1 = Overloaded, 0 = Normal)");
        printf("\n2: Maintenance Required (1 = Yes, 0 = No)");
        printf("\nEnter setting number (0–2): ");
        scanf("%d", &bit);

        if (bit < 0 || bit > 2)
        {
            printf("\nPlease select a valid option!");
        }
        else
        {
            int action;
            int mask = (1 << bit);
            printf("Enter action: 1 = SET the flag, 0 = CLEAR the flag: ");
            scanf("%d", &action);
            if (action < 0 || action > 1)
            {
                printf("\nPlease select a enetr a valid action!");
            }
            else if (action == 1)
            {
                sectors[row][col] |= mask;
                printf("\nSector %d %d Status Updated to 1!\n\n", row, col);
            }
            else
            {
                sectors[row][col] = ~(~sectors[row][col] | mask); 

                printf("\nSector %d %d Status Cleared to 0!\n\n", row, col);
            }
        }
        printf("\n-----GRID STATUS-----\n\n");
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                //Below prints the grid as decimal numbers
                printf("%d\t", sectors[i][j]);
            }
            printf("\n");
        }
    }
}

void querySectorStatus(int sectors[][3])
{
     int row, col;
    printf("\nEnter Sector row: ");
    scanf("%d", &row);
    printf("\nEnter Sector column: ");
    scanf("%d", &col);
    if (row < 0 || row > 2)
    {
        printf("\nPlease enter valid row number!");
    }
    else if (col < 0 || col > 2)
    {
        printf("\nPlease enter valid column number!");
    }
    else
    {
        int powerStatus = (sectors[row][col] >> 0) & 1;
        int overloadWarning = (sectors[row][col] >> 1) & 1;
        int maintenanceRequired = (sectors[row][col] >> 2) & 1;
        printf("\nSector %d %d Status:\n", row, col);

        // print statements below this will print the specified output like On, overloaded etc
        printf("\nPower Status: %s", powerStatus ? "ON" : "OFF");
        printf("\nOverload Warning: %s", overloadWarning ? "Overloaded" : "Normal");
        printf("\nMaintenance Required: %s", maintenanceRequired ? "Yes" : "No");
    }
}

void runSystemDiagnostic(int sectors[][3])
{
    int overloadCount = 0, maintenanceCount = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int overloadCheck = (sectors[i][j] >> 1) & 1;
            int maintenanceCheck = (sectors[i][j] >> 2) & 1;

            if (overloadCheck == 1)
            {
                overloadCount++;
            }

            if (maintenanceCheck == 1)
            {
                maintenanceCount++;
            }
        }
    }

    printf("\nTotal Num of Sectors OVERLOADED: %d\n", overloadCount);
    printf("Total Num of Sectors that NEED Maintenance: %d\n", maintenanceCount);
}
int main()
{
    int choice;
    int sectors[3][3] = {0};
    do
    {
        printf("\n============== IESCO Power Grid Monitoring System (Simulator) ==============\n");
        printf("\n1. Update Sector Status");
        printf("\n2. Query Power Grid Status");
        printf("\n3. Run System Diagnostic");
        printf("\n4. Exit");
        printf("\nWhat do you want to do?: ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choice)
        {
        case 1:
            updateSectorStatus(sectors);
            break;
        case 2:
            querySectorStatus(sectors);
            break;
        case 3:
            runSystemDiagnostic(sectors);
            break;
        case 4:
            printf("\nGoodbye!\n");
            return 0;
            break;
        default:
            printf("\nPlease select a valid option!\n");
            break;
        }
    } while (choice != 4);

    return 0;
}