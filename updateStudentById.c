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

    FILE *tempFile = fopen("temp.dat", "w");
    if (tempFile == NULL) {
        printf("Error opening temporary file for writing!\n");
        fclose(file);
        return 1; // Exit if temp file cannot be opened
    }

    int updateID;
    struct P1 student;
    int found = 0;

    printf("Enter the ID of the student to update: ");
    scanf("%d", &updateID);

    // Read each record and update if necessary
    while (fscanf(file, "ID: %d\nName: %[^\n]\nAge: %d\nGrade: %[^\n]\nAddress: %[^\n]\n\n",
                  &student.id, student.name, &student.age, student.grade, student.address) != EOF) {
        if (student.id == updateID) {
            found = 1;
            printf("\nUpdating details for Student ID: %d\n", updateID);

            // Prompt the user for new details
            printf("Enter new name: ");
            getchar(); // Clear the newline character from the input buffer
            fgets(student.name, sizeof(student.name), stdin);
            student.name[strcspn(student.name, "\n")] = '\0'; // Remove trailing newline

            printf("Enter new age: ");
            scanf("%d", &student.age);

            printf("Enter new grade: ");
            scanf("%s", student.grade);

            printf("Enter new address: ");
            getchar(); // Clear the newline character
            fgets(student.address, sizeof(student.address), stdin);
            student.address[strcspn(student.address, "\n")] = '\0'; // Remove trailing newline

            printf("Student updated successfully!\n");
        }

        // Write the current (updated or unchanged) record to the temp file
        fprintf(tempFile, "ID: %d\n", student.id);
        fprintf(tempFile, "Name: %s\n", student.name);
        fprintf(tempFile, "Age: %d\n", student.age);
        fprintf(tempFile, "Grade: %s\n", student.grade);
        fprintf(tempFile, "Address: %s\n\n", student.address);
    }

    fclose(file);
    fclose(tempFile);

    // If the student ID was not found, notify the user
    if (!found) {
        printf("No student found with ID: %d\n", updateID);
        // Remove the temp file as no changes are needed
        remove("temp.dat");
    } else {
        // Replace the original file with the temporary file
        remove("students.dat");
        rename("temp.dat", "students.dat");
    }

    return 0;
}
