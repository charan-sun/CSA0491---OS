#include <stdio.h>
#include <stdlib.h>

// Structure to represent an employee record
struct Employee {
    int empID;
    char name[50];
    float salary;
};

// Function to add an employee record to the file
void addEmployee(FILE *file) {
    struct Employee emp;

    printf("Enter employee ID: ");
    scanf("%d", &emp.empID);
    printf("Enter employee name: ");
    scanf("%s", emp.name);
    printf("Enter employee salary: ");
    scanf("%f", &emp.salary);

    fseek(file, (emp.empID - 1) * sizeof(struct Employee), SEEK_SET);
    fwrite(&emp, sizeof(struct Employee), 1, file);
}

// Function to display an employee record from the file
void displayEmployee(FILE *file, int empID) {
    struct Employee emp;

    fseek(file, (empID - 1) * sizeof(struct Employee), SEEK_SET);
    fread(&emp, sizeof(struct Employee), 1, file);

    printf("Employee ID: %d\n", emp.empID);
    printf("Name: %s\n", emp.name);
    printf("Salary: %.2f\n", emp.salary);
}

// Function to update an employee record in the file
void updateEmployee(FILE *file, int empID) {
    struct Employee emp;

    fseek(file, (empID - 1) * sizeof(struct Employee), SEEK_SET);
    fread(&emp, sizeof(struct Employee), 1, file);

    printf("Enter new employee name: ");
    scanf("%s", emp.name);
    printf("Enter new employee salary: ");
    scanf("%f", &emp.salary);

    fseek(file, (empID - 1) * sizeof(struct Employee), SEEK_SET);
    fwrite(&emp, sizeof(struct Employee), 1, file);
}

// Function to delete an employee record from the file
void deleteEmployee(FILE *file, int empID) {
    struct Employee emp;
    emp.empID = -1; // Marking the record as deleted

    fseek(file, (empID - 1) * sizeof(struct Employee), SEEK_SET);
    fwrite(&emp, sizeof(struct Employee), 1, file);
}

int main() {
    FILE *file;
    int choice, empID;

    file = fopen("employees.dat", "r+");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    while (1) {
        printf("\nEmployee Management System\n");
        printf("1. Add Employee\n");
        printf("2. Display Employee\n");
        printf("3. Update Employee\n");
        printf("4. Delete Employee\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee(file);
                break;
            case 2:
                printf("Enter employee ID: ");
                scanf("%d", &empID);
                displayEmployee(file, empID);
                break;
            case 3:
                printf("Enter employee ID: ");
                scanf("%d", &empID);
                updateEmployee(file, empID);
                break;
            case 4:
                printf("Enter employee ID: ");
                scanf("%d", &empID);
                deleteEmployee(file, empID);
                break;
            case 5:
                fclose(file);
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}

