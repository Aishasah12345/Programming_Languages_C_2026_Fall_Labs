
/*
 * week5_task3_student_management_system.c
 * Name: Aisha  Surname: Sah  Student ID: 260AIB131
 *
 * Task 3: Student management system with file persistence
 * Week 5 - Files & Modular Programming
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50
#define LINE_LEN 256
#define DATA_FILE "students.txt"

typedef struct Student {
  char name[NAME_LEN];
  int id;
  float gpa;
} Student;

int load_students(Student arr[], int max);
int save_students(const Student arr[], int count);
void add_student(Student arr[], int* count);
void list_students(const Student arr[], int count);
int read_line(const char* prompt, char* buf, size_t size);

int main(void) {
  Student students[MAX_STUDENTS];
  int count = 0;
  char input[LINE_LEN];
  int running = 1;

  count = load_students(students, MAX_STUDENTS);
  printf("Loaded %d student(s) from %s\n", count, DATA_FILE);

  while (running) {
    printf("\n=== Student Management System ===\n");
    printf("1. List students\n");
    printf("2. Add student\n");
    printf("3. Save and Exit\n");

    int choice;
    if (read_line("Select an option: ", input, sizeof input) != 0) {
      choice = 3;
    } else {
      char* end;
      long value = strtol(input, &end, 10);
      choice = (end != input && *end == '\0') ? (int)value : 0;
    }

    switch (choice) {
      case 1:
        list_students(students, count);
        break;
      case 2:
        add_student(students, &count);
        break;
      case 3:
        if (save_students(students, count) != 0) {
          fprintf(stderr, "Error saving student data.\n");
          return EXIT_FAILURE;
        }
        printf("Data saved. Goodbye!\n");
        running = 0;
        break;
      default:
        printf("Invalid option. Try again.\n");
    }
  }

  return EXIT_SUCCESS;
}

/* Read one line safely and remove its newline. */
int read_line(const char* prompt, char* buf, size_t size) {
  printf("%s", prompt);
  fflush(stdout);

  if (fgets(buf, (int)size, stdin) == NULL) {
    return -1;
  }

  size_t len = strcspn(buf, "\r\n");

  if (buf[len] == '\0' && len == size - 1) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
  }

  buf[len] = '\0';
  return 0;
}

/* Load valid student records from students.txt. */
int load_students(Student arr[], int max) {
  FILE* fp = fopen(DATA_FILE, "r");

  if (fp == NULL) {
    return 0;
  }

  char line[LINE_LEN];
  int count = 0;

  while (count < max && fgets(line, sizeof line, fp) != NULL) {
    Student student = {0};

    if (sscanf(line, "%49[^,],%d,%f", student.name, &student.id,
               &student.gpa) == 3) {
      if (student.name[0] != '\0' && strchr(student.name, ',') == NULL &&
          student.gpa >= 0.0f && student.gpa <= 4.0f) {
        arr[count] = student;
        count++;
      }
    }
  }

  fclose(fp);
  return count;
}

/* Save all student records, replacing the existing file. */
int save_students(const Student arr[], int count) {
  FILE* fp = fopen(DATA_FILE, "w");

  if (fp == NULL) {
    return -1;
  }

  for (int i = 0; i < count; i++) {
    if (fprintf(fp, "%s,%d,%.2f\n", arr[i].name, arr[i].id, arr[i].gpa) < 0) {
      fclose(fp);
      return -1;
    }
  }

  if (fclose(fp) != 0) {
    return -1;
  }

  return 0;
}

/* Validate and add one student. */
void add_student(Student arr[], int* count) {
  if (*count >= MAX_STUDENTS) {
    printf("Cannot add more students (limit reached).\n");
    return;
  }

  char name[LINE_LEN];
  char id_text[LINE_LEN];
  char gpa_text[LINE_LEN];

  if (read_line("Enter name: ", name, sizeof name) != 0 ||
      read_line("Enter ID: ", id_text, sizeof id_text) != 0 ||
      read_line("Enter GPA: ", gpa_text, sizeof gpa_text) != 0) {
    return;
  }

  if (name[0] == '\0' || strchr(name, ',') != NULL ||
      strlen(name) >= NAME_LEN) {
    printf("Invalid input. Student not added.\n");
    return;
  }

  char* end;
  long id = strtol(id_text, &end, 10);

  if (end == id_text || *end != '\0' || id < 0 || id > 2147483647L) {
    printf("Invalid input. Student not added.\n");
    return;
  }

  char* gpa_end;
  float gpa = strtof(gpa_text, &gpa_end);

  if (gpa_end == gpa_text || *gpa_end != '\0' || gpa < 0.0f || gpa > 4.0f) {
    printf("Invalid input. Student not added.\n");
    return;
  }

  Student student = {0};
  strcpy(student.name, name);
  student.id = (int)id;
  student.gpa = gpa;

  arr[*count] = student;
  (*count)++;

  printf("Student added successfully!\n");
}

/* Display all students. */
void list_students(const Student arr[], int count) {
  if (count == 0) {
    printf("No students found.\n");
    return;
  }

  printf("%-5s %-20s %s\n", "ID", "Name", "GPA");

  for (int i = 0; i < count; i++) {
    printf("%-5d %-20s %.2f\n", arr[i].id, arr[i].name, arr[i].gpa);
  }
}
