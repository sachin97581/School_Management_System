#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct P1 {
    int id;
    char name[50];
    int age;
    char grade[10];
    char address[100];
};

int main() {
    FILE *file = fopen("students.dat", "r");
    if (file == NULL) {
        printf("Error opening file for reading!\n");
        return 1; // Exit if file cannot be opened
    }

    int searchID;
    struct P1 student;
    int found = 0;

    printf("Enter the ID of the student to search: ");
    scanf("%d", &searchID);

    // Search for the student by ID
    while (fscanf(file, "ID: %d\nName: %[^\n]\nAge: %d\nGrade: %[^\n]\nAddress: %[^\n]\n\n",
                  &student.id, student.name, &student.age, student.grade, student.address) != EOF) {
        if (student.id == searchID) {
            found = 1;
            printf("\nStudent Found:\n");
            printf("ID: %d\n", student.id);
            printf("Name: %s\n", student.name);
            printf("Age: %d\n", student.age);
            printf("Grade: %s\n", student.grade);
            printf("Address: %s\n", student.address);
            break; // Exit loop after finding the record
        }
    }

    if (!found) {
        printf("\nNo student found with ID: %d\n", searchID);
    }

    fclose(file); // Close the file
    return 0;
}
