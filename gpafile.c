#include <stdio.h>
#include <stdlib.h> // Required for exit()

#define NUM_STUDENTS 3
#define NUM_SUBJECTS 7

int main() {
    int marks[NUM_STUDENTS][NUM_SUBJECTS];
    FILE *marks_fp = NULL;
    FILE *gpa_fp = NULL;

    printf("--- C Program: Student Marks and GPA Calculation ---\n");

    // 1. Take the marks of 3 students for 7 subjects using loop.
    printf("\n*** Enter Marks (out of 100) ***\n");
    for (int i = 0; i < NUM_STUDENTS; i++) { // Loop for students
        printf("--- Student %d ---\n", i + 1);
        for (int j = 0; j < NUM_SUBJECTS; j++) { // Loop for subjects
            printf("Enter marks for Subject %d: ", j + 1);
            // Assuming valid input as per your request
            if (scanf("%d", &marks[i][j]) != 1) {
                printf("Error: Invalid input. Exiting.\n");
                return 1;
            }
        }
    }

    // --- CSV File 1: Raw Marks Data ---
    marks_fp = fopen("marks_data.csv", "w");
    if (marks_fp == NULL) {
        perror("Error opening marks_data.csv");
        return 1;
    }

    // Write header for marks_data.csv
    fprintf(marks_fp, "Student_Number");
    for (int j = 0; j < NUM_SUBJECTS; j++) {
        fprintf(marks_fp, ",Subject_%d", j + 1);
    }
    fprintf(marks_fp, "\n");

    // Write raw marks data
    for (int i = 0; i < NUM_STUDENTS; i++) {
        fprintf(marks_fp, "%d", i + 1); // Student Number
        for (int j = 0; j < NUM_SUBJECTS; j++) {
            fprintf(marks_fp, ",%d", marks[i][j]);
        }
        fprintf(marks_fp, "\n");
    }

    fclose(marks_fp);
    printf("\nRaw marks data saved to: marks_data.csv\n");
    // ------------------------------------

    // --- CSV File 2: GPA Data ---
    gpa_fp = fopen("gpa_data.csv", "w");
    if (gpa_fp == NULL) {
        perror("Error opening gpa_data.csv");
        return 1;
    }

    // Write header for gpa_data.csv
    fprintf(gpa_fp, "Student_Number,GPA\n");

    // Calculate GPA and write data
    for (int i = 0; i < NUM_STUDENTS; i++) {
        int total_marks = 0;

        // Calculate total marks for the current student
        for (int j = 0; j < NUM_SUBJECTS; j++) {
            total_marks += marks[i][j];
        }

        // Calculate Average Mark
        double average_mark = (double)total_marks / NUM_SUBJECTS;

        // Calculate GPA: Average marks divided by 10
        double gpa = average_mark / 10.0;

        // Write student number and GPA (formatted to 2 decimal places)
        fprintf(gpa_fp, "%d,%.2f\n", i + 1, gpa);
    }

    fclose(gpa_fp);
    printf("GPA data saved to: gpa_data.csv\n");
    // ----------------------------

    printf("\nProgram finished successfully.\n");
    return 0;
}