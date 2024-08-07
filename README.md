# 📚 Student Management System

This project is a comprehensive Student Management System implemented in C. The system allows users to manage student records efficiently, including functionalities to add, modify, delete, display, search, and update student details. The aim of this project is to provide a robust and user-friendly tool for managing student information in educational institutions.

## ✨ Features

- **Add Student**: Add new students with automatic roll number generation based on their course and branch.
- **Display Students**: Display the list of all students with their details.
- **Modify Student**: Modify existing student details.
- **Delete Student**: Delete student records.
- **Update Attendance**: Update student attendance percentage.
- **Search Student**: Search for students by their roll number.
- **Update Student Details**: Update specific details of students.

## 🛠 Data Structure

The student details are stored in a structure as follows:

```c
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
    int attendance;
} Student;
