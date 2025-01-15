#include <stdio.h>
#include <stdlib.h>

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

    int deleteID;
    struct P1 student;
    int found = 0;

    printf("Enter the ID of the student to remove: ");
    scanf("%d", &deleteID);

    // Read each record and copy all except the one to be deleted
    while (fscanf(file, "ID: %d\nName: %[^\n]\nAge: %d\nGrade: %[^\n]\nAddress: %[^\n]\n\n",
                  &student.id, student.name, &student.age, student.grade, student.address) != EOF) {
        if (student.id == deleteID) {
            found = 1; // Mark that the student to delete is found
            printf("Student with ID %d removed successfully.\n", deleteID);
            continue; // Skip writing this record to the temp file
        }
        // Write the current record to the temporary file
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
        printf("No student found with ID: %d\n", deleteID);
        // Remove the temp file as no changes are needed
        remove("temp.dat");
    } else {
        // Replace the original file with the temporary file
        remove("students.dat");
        rename("temp.dat", "students.dat");
    }

    return 0;
}
