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

// Function to get the last ID from the file
int getLastID() {
    FILE *fp = fopen("students.dat", "r");
    if (fp == NULL) {
        return 0; // If file doesn't exist, return 0 as the starting ID
    }

    struct P1 temp;
    int lastID = 0;

    // Read all records to find the last ID
    while (fscanf(fp, "ID: %d\nName: %[^\n]\nAge: %d\nGrade: %[^\n]\nAddress: %[^\n]\n\n",
                  &temp.id, temp.name, &temp.age, temp.grade, temp.address) != EOF) {
        lastID = temp.id;
    }

    fclose(fp);
    return lastID;
}

int main() {
    struct P1 s;

    // Get the next available ID
    int lastID = getLastID();
    s.id = lastID + 1;

    // Prompt user for the rest of the details
    printf("Enter Name: ");
    getchar(); // To consume the newline left by the previous input
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = 0; // Remove trailing newline
    printf("Enter Age: ");
    scanf("%d", &s.age);
    printf("Enter Grade: ");
    scanf("%s", s.grade);
    printf("Enter Address: ");
    getchar(); // To consume the newline left by scanf
    fgets(s.address, sizeof(s.address), stdin);
    s.address[strcspn(s.address, "\n")] = 0; // Remove trailing newline

    // Open the file in append mode
    FILE *fp = fopen("students.dat", "a");
    if (fp == NULL) {
        printf("Error opening file for writing!\n");
        return 1; // Exit if file cannot be opened
    }

    // Write the student record to the file
    fprintf(fp, "ID: %d\n", s.id);
    fprintf(fp, "Name: %s\n", s.name);
    fprintf(fp, "Age: %d\n", s.age);
    fprintf(fp, "Grade: %s\n", s.grade);
    fprintf(fp, "Address: %s\n\n", s.address); // Add an extra newline for separation

    fclose(fp);
    printf("Student record saved successfully with ID: %d\n", s.id);

    return 0;
}
