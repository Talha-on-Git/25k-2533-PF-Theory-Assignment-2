#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct
{
    char studentID[10];       // Unique student ID (string)
    char fullName[100];
    char batch[20];
    char membershipType[10];
    char registrationDate[15];
    char dateOfBirth[15];
    char interest[10];
} Student;

// ------------------- GLOBAL VARIABLES -------------------
Student *students = NULL;
int size = 0;
int capacity = 2;

const char *FILENAME = "members.dat";

// ------------------- MEMORY MANAGEMENT -------------------
void ensureCapacity()
{
    if (size >= capacity)
    {
        capacity *= 2;
        Student *newStudents = realloc(students, capacity * sizeof(Student));
        if (!newStudents)
        {
            perror("Realloc failed in ensureCapacity");
            exit(1);
        }
        students = newStudents;
    }
}

// ------------------- FILE OPERATIONS -------------------
void loadDatabase()
{
    FILE *fp = fopen(FILENAME, "rb");
    if (!fp)
    {
        if (errno == ENOENT)
        {
            printf("No previous database found. Starting fresh.\n");
            return;
        }
        else
        {
            perror("Error opening file for reading");
            return;
        }
    }

    if (students)
    {
        free(students);
    }
    students = malloc(capacity * sizeof(Student));
    if (!students)
    {
        perror("Initial malloc failed");
        fclose(fp);
        exit(1);
    }

    size = 0;
    while (fread(&students[size], sizeof(Student), 1, fp) == 1)
    {
        size++;
        ensureCapacity();
    }

    fclose(fp);
    printf("%d student records loaded from file.\n", size);
}

void saveDatabase()
{
    FILE *fp = fopen(FILENAME, "wb");
    if (!fp)
    {
        perror("Error opening file for writing");
        return;
    }

    fwrite(students, sizeof(Student), size, fp);

    fclose(fp);
    printf("Database saved successfully.\n");
}

// ------------------- UTILITY FUNCTIONS -------------------
int findStudentIndex(char studentID[])
{
    for (int i = 0; i < size; i++)
    {
        if (strcmp(students[i].studentID, studentID) == 0)
            return i;
    }
    return -1;
}

void printStudent(Student s)
{
    printf("\n---------------------------------------------\n");
printf("| %-12s : %-20s |\n", "ID", s.studentID);
printf("| %-12s : %-20s |\n", "Name", s.fullName);
printf("| %-12s : %-20s |\n", "Batch", s.batch);
printf("| %-12s : %-20s |\n", "Membership", s.membershipType);
printf("| %-12s : %-20s |\n", "Reg Date", s.registrationDate);
printf("| %-12s : %-20s |\n", "DOB", s.dateOfBirth);
printf("| %-12s : %-20s |\n", "Interest", s.interest);
printf("---------------------------------------------\n");
}

// ------------------- CRUD OPERATIONS -------------------
void addStudent()
{
    Student s;

    printf("\nEnter Student ID: ");
    fgets(s.studentID, sizeof(s.studentID), stdin);
    s.studentID[strcspn(s.studentID, "\n")] = '\0';

    if (findStudentIndex(s.studentID) != -1)
    {
        printf("Student ID already exists. Cannot add duplicate.\n");
        return;
    }

    printf("Enter Full Name: ");
    fgets(s.fullName, sizeof(s.fullName), stdin);
    s.fullName[strcspn(s.fullName, "\n")] = '\0';

    printf("Enter Batch (CS/SE/Cyber Security/AI): ");
    fgets(s.batch, sizeof(s.batch), stdin);
    s.batch[strcspn(s.batch, "\n")] = '\0';

    printf("Enter Membership Type (IEEE/ACM): ");
    fgets(s.membershipType, sizeof(s.membershipType), stdin);
    s.membershipType[strcspn(s.membershipType, "\n")] = '\0';

    printf("Enter Registration Date (YYYY-MM-DD): ");
    fgets(s.registrationDate, sizeof(s.registrationDate), stdin);
    s.registrationDate[strcspn(s.registrationDate, "\n")] = '\0';

    printf("Enter Date of Birth (YYYY-MM-DD): ");
    fgets(s.dateOfBirth, sizeof(s.dateOfBirth), stdin);
    s.dateOfBirth[strcspn(s.dateOfBirth, "\n")] = '\0';

    printf("Enter Interest (IEEE/ACM/Both): ");
    fgets(s.interest, sizeof(s.interest), stdin);
    s.interest[strcspn(s.interest, "\n")] = '\0';

    ensureCapacity();
    students[size] = s;
    size++;

    saveDatabase();
    printf("Student added successfully.\n");
}

void updateStudent()
{
    if (size == 0)
    {
        printf("No students in database. Add students first.\n");
        return;
    }

    char id[10];
    printf("\nEnter Student ID to update: ");
    while (getchar() != '\n');
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    int idx = findStudentIndex(id);
    if (idx == -1)
    {
        printf("Student ID not found.\n");
        return;
    }

    printf("Current Batch: %s\nEnter new Batch: ", students[idx].batch);
    fgets(students[idx].batch, sizeof(students[idx].batch), stdin);
    students[idx].batch[strcspn(students[idx].batch, "\n")] = '\0';

    printf("Current Membership: %s\nEnter new Membership Type: ", students[idx].membershipType);
    fgets(students[idx].membershipType, sizeof(students[idx].membershipType), stdin);
    students[idx].membershipType[strcspn(students[idx].membershipType, "\n")] = '\0';

    saveDatabase();
    printf("Student record updated.\n");
}

void deleteStudent()
{
    if (size == 0)
    {
        printf("No students in database. Add students first.\n");
        return;
    }

    char id[10];
    printf("\nEnter Student ID to delete: ");
    while (getchar() != '\n');
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    int idx = findStudentIndex(id);
    if (idx == -1)
    {
        printf("Student ID not found.\n");
        return;
    }

    for (int i = idx; i < size - 1; i++)
    {
        students[i] = students[i + 1];
    }

    size--;

    saveDatabase();
    printf("Student deleted successfully.\n");
}

void viewAllStudents()
{
    if (size == 0)
    {
        printf("No students to display.\n");
        return;
    }

    for (int i = 0; i < size; i++)
        printStudent(students[i]);
}

void generateBatchReport()
{
    if (size == 0)
    {
        printf("No students to display.\n");
        return;
    }

    char batch[50];
    char membership[10];

    printf("Enter Batch (CS/SE/Cyber Security/AI): ");
    while (getchar() != '\n');
    fgets(batch, sizeof(batch), stdin);
    batch[strcspn(batch, "\n")] = '\0';

    printf("Enter Membership (IEEE/ACM): ");
    fgets(membership, sizeof(membership), stdin);
    membership[strcspn(membership, "\n")] = '\0';

    int found = 0;
    for (int i = 0; i < size; i++)
    {
        if (strcmp(students[i].batch, batch) == 0 &&
            strcmp(students[i].membershipType, membership) == 0)
        {
            printStudent(students[i]);
            found = 1;
        }
    }

    if (!found)
        printf("No students found for given criteria.\n");
}

int main()
{
    students = malloc(capacity * sizeof(Student));
    if (!students)
    {
        perror("Initial malloc failed");
        return 1;
    }

    loadDatabase();
    int choice;

    do
    {
        printf("\n=======IEEE / ACM Membership Registration Manager=======\n");
        printf("1. Register a new student\n");
        printf("2. Update student info\n");
        printf("3. Delete a student\n");
        printf("4. View all students\n");
        printf("5. Generate batch-wise report\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            while (getchar() != '\n');
            addStudent();
            break;
        case 2:
            updateStudent();
            break;
        case 3:
            deleteStudent();
            break;
        case 4:
            viewAllStudents();
            break;
        case 5:
            generateBatchReport();
            break;
        case 6:
            printf("Exiting...\n");
            saveDatabase();
            break;
        default:
            printf("Invalid choice. Try again.\n");
        }

    } while (choice != 6);

    free(students);
    return 0;
}
