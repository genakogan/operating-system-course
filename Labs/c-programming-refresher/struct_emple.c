#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the employee structure

//struct Employee {
//    int id;
//    char name[100];
//    int age;
//    float salary;
//};


typedef struct  {
    int id;
    char name[100];
    int age;
    float salary;
}Employee;

int main() {
    int num_employees = 3; // Number of employees

    // Allocate memory for an array of Employee structures using calloc
    Employee *employees = (Employee *)calloc(num_employees, sizeof( Employee));

    // Check if the memory allocation was successful
    if (employees == NULL) {
        printf("Memory allocation failed\n");
        return 1; // Exit if memory allocation fails
    }

    // Assign values to the structure members for each employee
    for (int i = 0; i < num_employees; i++) {
        employees[i].id = i + 1;
        snprintf(employees[i].name, sizeof(employees[i].name), "Employee%d", i + 1);
        employees[i].age = 25 + i; // Just for example
        employees[i].salary = 50000.00 + (i * 5000); // Just for example
    }

    // Print the values to verify
    printf("Employee Details:\n");
    for (int i = 0; i < num_employees; i++) {
        printf("ID: %d\n", employees[i].id);
        printf("Name: %s\n", employees[i].name);
        printf("Age: %d\n", employees[i].age);
        printf("Salary: %.2f\n", employees[i].salary);
        printf("\n");
    }

    // Free the allocated memory
    free(employees);

    return 0;
}
