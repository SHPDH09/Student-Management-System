#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LENGTH 50
#define SECTION_LENGTH 10
#define COURSE_LENGTH 50
#define BRANCH_LENGTH 50
#define MAX_SEMESTERS 6
#define FILE_NAME "students.dat"

typedef struct {
    int id;
    char rollNumber[15];
    char name[NAME_LENGTH];
    int age;
    float gpa;
    char section[SECTION_LENGTH];
    char course[COURSE_LENGTH];
    char branch[BRANCH_LENGTH];
    int semester;
    float cgpa[MAX_SEMESTERS];
    int attendance; // Percentage of attendance
} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

void saveToFile() {
    FILE *file = fopen(FILE_NAME, "wb");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    if (fwrite(&studentCount, sizeof(int), 1, file) != 1) {
        printf("Error writing student count to file.\n");
    }
    if (fwrite(students, sizeof(Student), studentCount, file) != studentCount) {
        printf("Error writing students to file.\n");
    }
    fclose(file);
}

void loadFromFile() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("No existing data file found. Starting fresh.\n");
        return;
    }
    if (fread(&studentCount, sizeof(int), 1, file) != 1) {
        printf("Error reading student count from file.\n");
        studentCount = 0;
        fclose(file);
        return;
    }
    if (fread(students, sizeof(Student), studentCount, file) != studentCount) {
        printf("Error reading students from file.\n");
        studentCount = 0;
    }
    fclose(file);
}

void generateRollNumber(Student *s) {
    char prefix[10];
    if (strcmp(s->course, "BCA") == 0) {
        strcpy(prefix, "BCA");
    } else if (strcmp(s->course, "MCA") == 0) {
        strcpy(prefix, "MCA");
    } else {
        strcpy(prefix, "UNKNOWN");
    }

    char branchCode[5];
    if (strcmp(s->branch, "AIDA") == 0) {
        strcpy(branchCode, "AIDA");
    } else if (strcmp(s->branch, "AIDS") == 0) {
        strcpy(branchCode, "AIDS");
    } else if (strcmp(s->branch, "AIML") == 0) {
        strcpy(branchCode, "AIML");
    } else {
        strcpy(branchCode, "GEN");
    }

    sprintf(s->rollNumber, "%s%s%03d", prefix, branchCode, s->id);
}

void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("Maximum student limit reached.\n");
        return;
    }

    Student s;
    s.id = studentCount + 1; // Automatic registration number generation

    printf("Select course:\n");
    printf("1. BCA\n");
    printf("2. MCA\n");
    int courseChoice;
    scanf("%d", &courseChoice);

    if (courseChoice == 1) {
        strcpy(s.course, "BCA");
        printf("Select branch:\n");
        printf("1. AIDA\n");
        printf("2. AIDS\n");
        int branchChoice;
        scanf("%d", &branchChoice);

        if (branchChoice == 1) {
            strcpy(s.branch, "AIDA");
        } else if (branchChoice == 2) {
            strcpy(s.branch, "AIDS");
        } else {
            printf("Invalid branch choice.\n");
            return;
        }
    } else if (courseChoice == 2) {
        strcpy(s.course, "MCA");
        printf("Select branch:\n");
        printf("1. AIML\n");
        int branchChoice;
        scanf("%d", &branchChoice);

        if (branchChoice == 1) {
            strcpy(s.branch, "AIML");
        } else {
            printf("Invalid branch choice.\n");
            return;
        }
    } else {
        printf("Invalid course choice.\n");
        return;
    }

    generateRollNumber(&s);

    printf("Enter name: ");
    scanf(" %[^\n]%*c", s.name);
    printf("Enter age: ");
    scanf("%d", &s.age);
    printf("Enter GPA: ");
    scanf("%f", &s.gpa);
    printf("Enter section: ");
    scanf(" %[^\n]%*c", s.section);
    printf("Enter semester: ");
    scanf("%d", &s.semester);

    for (int i = 0; i < MAX_SEMESTERS; i++) {
        s.cgpa[i] = 0.0; // Initialize CGPA for all semesters to 0
    }

    s.attendance = 0; // Initialize attendance to 0

    students[studentCount++] = s;
    saveToFile();
    printf("Student added successfully.\n");
}

void displayStudents() {
    if (studentCount == 0) {
        printf("No students to display.\n");
        return;
    }

    printf("\n--- Student List ---\n");
    for (int i = 0; i < studentCount; i++) {
        printf("ID: %d | Roll Number: %s | Name: %s | Age: %d | GPA: %.2f | Section: %s | Course: %s[%s] | Semester: %d | Attendance: %d%%\n",
               students[i].id, students[i].rollNumber, students[i].name, students[i].age, students[i].gpa, students[i].section,
               students[i].course, students[i].branch, students[i].semester, students[i].attendance);
        printf("CGPA per semester: ");
        for (int j = 0; j < students[i].semester; j++) {
            printf("\n%d Semester CGPA: %.2f", j + 1, students[i].cgpa[j]);
        }
        printf("\n");
    }
    printf("\n");
}

void modifyStudent() {
    int id;
    printf("Enter student ID to modify: ");
    scanf("%d", &id);

    if (id < 1 || id > studentCount) {
        printf("Invalid student ID.\n");
        return;
    }

    Student *s = &students[id - 1];
    printf("Enter new name: ");
    scanf(" %[^\n]%*c", s->name);
    printf("Enter new age: ");
    scanf("%d", &s->age);
    printf("Enter new GPA: ");
    scanf("%f", &s->gpa);
    printf("Enter new section: ");
    scanf(" %[^\n]%*c", s->section);
    printf("Enter new semester: ");
    scanf("%d", &s->semester);

    for (int i = 0; i < MAX_SEMESTERS; i++) {
        printf("Enter CGPA for semester %d: ", i + 1);
        scanf("%f", &s->cgpa[i]);
    }

    saveToFile();
    printf("Student record updated successfully.\n");
}

void deleteStudent() {
    int id;
    printf("Enter student ID to delete: ");
    scanf("%d", &id);

    if (id < 1 || id > studentCount) {
        printf("Invalid student ID.\n");
        return;
    }

    for (int i = id - 1; i < studentCount - 1; i++) {
        students[i] = students[i + 1];
    }
    studentCount--;
    saveToFile();

    printf("Student record deleted successfully.\n");
}

void updateAttendance() {
    int id, attendance;
    printf("Enter student ID to update attendance: ");
    scanf("%d", &id);

    if (id < 1 || id > studentCount) {
        printf("Invalid student ID.\n");
        return;
    }

    printf("Enter new attendance percentage: ");
    scanf("%d", &attendance);

    if (attendance < 0 || attendance > 100) {
        printf("Invalid attendance percentage. Must be between 0 and 100.\n");
        return;
    }

    students[id - 1].attendance = attendance;
    saveToFile();
    printf("Student attendance updated successfully.\n");
}

void searchStudent() {
    char searchRollNumber[15];
    printf("Enter roll number to search: ");
    scanf("%s", searchRollNumber);

    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].rollNumber, searchRollNumber) == 0) {
            printf("\n--- Student Details ---\n");
            printf("ID: %d\nRoll Number: %s\nName: %s\nAge: %d\nGPA: %.2f\nSection: %s\nCourse: %s[%s]\nSemester: %d\nAttendance: %d%%\n",
                   students[i].id, students[i].rollNumber, students[i].name, students[i].age, students[i].gpa, students[i].section,
                   students[i].course, students[i].branch, students[i].semester, students[i].attendance);
            printf("CGPA per semester: ");
            for (int j = 0; j < students[i].semester; j++) {
                printf("\n%d Semester CGPA: %.2f", j + 1, students[i].cgpa[j]);
            }
            printf("\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student with roll number %s not found.\n", searchRollNumber);
    }
}

void updateStudentDetails() {
    int id;
    printf("Enter student ID to update details: ");
    scanf("%d", &id);

    if (id < 1 || id > studentCount) {
        printf("Invalid student ID.\n");
        return;
    }

    Student *s = &students[id - 1];
    int choice;

    while (1) {
        printf("Select detail to update:\n");
        printf("1. Name\n");
        printf("2. Age\n");
        printf("3. GPA\n");
        printf("4. Section\n");
        printf("5. Semester\n");
        printf("6. CGPA for semesters\n");
        printf("7. Attendance\n");
        printf("8. Exit update\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter new name: ");
                scanf(" %[^\n]%*c", s->name);
                break;
            case 2:
                printf("Enter new age: ");
                scanf("%d", &s->age);
                break;
            case 3:
                printf("Enter new GPA: ");
                scanf("%f", &s->gpa);
                break;
            case 4:
                printf("Enter new section: ");
                scanf(" %[^\n]%*c", s->section);
                break;
            case 5:
                printf("Enter new semester: ");
                scanf("%d", &s->semester);
                break;
            case 6:
                for (int i = 0; i < MAX_SEMESTERS; i++) {
                    printf("Enter CGPA for semester %d: ", i + 1);
                    scanf("%f", &s->cgpa[i]);
                }
                break;
            case 7:
                printf("Enter new attendance percentage: ");
                scanf("%d", &s->attendance);
                if (s->attendance < 0 || s->attendance > 100) {
                    printf("Invalid attendance percentage. Must be between 0 and 100.\n");
                }
                break;
            case 8:
                saveToFile();
                printf("Student details updated successfully.\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

int main() {
    loadFromFile();

    int choice;
    while (1) {
        printf("Student Management System\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Modify Student\n");
        printf("4. Delete Student\n");
        printf("5. Update Attendance\n");
        printf("6. Search Student\n");
        printf("7. Update Student Details\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                modifyStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                updateAttendance();
                break;
            case 6:
                searchStudent();
                break;
            case 7:
                updateStudentDetails();
                break;
            case 8:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
