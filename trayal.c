#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
    int age;
    char grade[10];
    char address[100];
};

void addStudent();
void viewStudents();
void searchStudent();
// void updateStudent();
// void deleteStudent();
void menu();

int main() {
    menu();
    return 0;
}

void menu() {
    int choice;
    while (1) {
        printf("\n--- School Management System ---\n");
        printf("1. Add Student\n");
        printf("2. View All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: exit(0); break;
            default: printf("Invalid choice! Please try again.\n");
        }
    }
}

void addStudent() {
    struct Student s;
    FILE *fp = fopen("students.dat", "ab");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    printf("\nEnter ID: ");
    scanf("%d", &s.id);
    printf("Enter Name: ");
    getchar(); // clear newline buffer
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = 0; // Remove trailing newline
    printf("Enter Age: ");
    scanf("%d", &s.age);
    printf("Enter Grade: ");
    scanf("%s", s.grade);
    printf("Enter Address: ");
    getchar();
    fgets(s.address, sizeof(s.address), stdin);
    s.address[strcspn(s.address, "\n")] = 0;

    fwrite(&s, sizeof(struct Student), 1, fp);
    fclose(fp);
    printf("Student added successfully!\n");
}

void viewStudents() {
    struct Student s;
    FILE *fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }
    printf("\n--- All Students ---\n");
    while (fread(&s, sizeof(struct Student), 1, fp)) {
        printf("ID: %d, Name: %s, Age: %d, Grade: %s, Address: %s\n", s.id, s.name, s.age, s.grade, s.address);
    }
    fclose(fp);
}

void searchStudent() {
    struct Student s;
    int id, found = 0;
    FILE *fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }
    printf("\nEnter Student ID to search: ");
    scanf("%d", &id);
    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.id == id) {
            printf("ID: %d, Name: %s, Age: %d, Grade: %s, Address: %s\n", s.id, s.name, s.age, s.grade, s.address);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Student not found.\n");
    }
    fclose(fp);
}

// Add `updateStudent()` and `deleteStudent()` functions similarly.
