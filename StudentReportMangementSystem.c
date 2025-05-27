#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    int indexno;
    char name[50];
    int p_marks, c_marks, m_marks, e_marks, cs_marks;
    float per;
    char grade;
};

// function to check if index number already exists
int index_exists(int indexno, FILE *fptr) {
    struct student st;
    rewind(fptr);
    while (fread(&st, sizeof(st), 1, fptr) == 1) {
        if (st.indexno == indexno) {
            return 1; // Index number exists
        }
    }
    return 0; // Index number does not exist
}

// Helper function to read student data
void read_student(struct student *st, FILE *fptr) {
    printf("\nEnter Index Number: ");
    while (1) {
        if (scanf("%d", &st->indexno) != 1 || st->indexno <= 0) {
            printf("Invalid Index number. Enter a positive number: ");
            while (getchar() != '\n');
            continue;
        }
        if (fptr && index_exists(st->indexno, fptr)) {
            printf("Index number already exists. Enter a unique index number: ");
            while (getchar() != '\n');
            continue;
        }
        break;
    }
    while (getchar() != '\n'); // Clear newline
    printf("Enter name: ");
    fgets(st->name, sizeof(st->name), stdin);
    st->name[strcspn(st->name, "\n")] = '\0'; // Remove trailing newline

    printf("Enter marks in Physics (0-100): ");
    while (scanf("%d", &st->p_marks) != 1 || st->p_marks < 0 || st->p_marks > 100) {
        printf("Invalid marks. Enter between 0 and 100: ");
        while (getchar() != '\n');
    }
    printf("Enter marks in Chemistry (0-100): ");
    while (scanf("%d", &st->c_marks) != 1 || st->c_marks < 0 || st->c_marks > 100) {
        printf("Invalid marks. Enter between 0 and 100: ");
        while (getchar() != '\n');
    }
    printf("Enter marks in Maths (0-100): ");
    while (scanf("%d", &st->m_marks) != 1 || st->m_marks < 0 || st->m_marks > 100) {
        printf("Invalid marks. Enter between 0 and 100: ");
        while (getchar() != '\n');
    }
    printf("Enter marks in English (0-100): ");
    while (scanf("%d", &st->e_marks) != 1 || st->e_marks < 0 || st->e_marks > 100) {
        printf("Invalid marks. Enter between 0 and 100: ");
        while (getchar() != '\n');
    }
    printf("Enter marks in Computer Science (0-100): ");
    while (scanf("%d", &st->cs_marks) != 1 || st->cs_marks < 0 || st->cs_marks > 100) {
        printf("Invalid marks. Enter between 0 and 100: ");
        while (getchar() != '\n');
    }

    st->per = (st->p_marks + st->c_marks + st->m_marks + st->e_marks + st->cs_marks) / 5.0;
    if (st->per >= 60) st->grade = 'A';
    else if (st->per >= 50) st->grade = 'B';
    else if (st->per >= 33) st->grade = 'C';
    else st->grade = 'F';
}

// Helper function to display a single student record
void display_student_record(const struct student *st) {
    printf("Index Number: %d\n", st->indexno);
    printf("Name: %s\n", st->name);
    printf("Physics: %d\n", st->p_marks);
    printf("Chemistry: %d\n", st->c_marks);
    printf("Maths: %d\n", st->m_marks);
    printf("English: %d\n", st->e_marks);
    printf("Computer Science: %d\n", st->cs_marks);
    printf("Percentage: %.2f%%\n", st->per);
    printf("Grade: %c\n", st->grade);
    printf("--------------------------------\n");
}

// Display all or specific student by index number (-1 for all)
void display_student(int indexno) {
    struct student st;
    FILE *fptr = fopen("student.dat", "rb");
    if (!fptr) {
        printf("Error: Cannot open file!\n");
        return;
    }

    int found = 0;
    printf("\n=== Student Records ===\n");
    while (fread(&st, sizeof(st), 1, fptr) == 1) {
        if (indexno == -1 || st.indexno == indexno) {
            display_student_record(&st);
            found = 1;
            if (indexno != -1) break; // Stop after finding specific student
        }
    }
    fclose(fptr);
    if (!found && indexno != -1) printf("Record not found for index number %d\n", indexno);
    printf("Press Enter to continue...");
    while (getchar() != '\n');
}

// Write a new student record
void write_student() {
    struct student st;
    FILE *fptr = fopen("student.dat", "ab");
    if (!fptr) {
        printf("Error: Cannot open file!\n");
        return;
    }

    printf("\n=== Add New Student ===\n");
    read_student(&st, fptr);
    fwrite(&st, sizeof(st), 1, fptr);
    fclose(fptr);
    printf("Student record created successfully.\n");
    printf("Press Enter to continue...");
    while (getchar() != '\n');
}

// Modify an existing student record
void modify_student() {
    struct student st;
    int indexno, found = 0;
    printf("\n=== Modify Student Record ===\n");
    printf("Enter index number to modify: ");
    while (scanf("%d", &indexno) != 1 || indexno <= 0) {
        printf("Invalid index number. Enter a positive number: ");
        while (getchar() != '\n');
    }

    FILE *fptr = fopen("student.dat", "rb+");
    if (!fptr) {
        printf("Error: Cannot open file!\n");
        return;
    }

    while (fread(&st, sizeof(st), 1, fptr) == 1 && !found) {
        if (st.indexno == indexno) {
            printf("\nCurrent Record:\n");
            display_student_record(&st);
            printf("\nEnter New Details:\n");
            while (getchar() != '\n'); // Clear newline
            read_student(&st, NULL); // No duplicate check during modify
            fseek(fptr, -(long)sizeof(st), SEEK_CUR);
            fwrite(&st, sizeof(st), 1, fptr);
            printf("Record updated successfully.\n");
            found = 1;
        }
    }
    fclose(fptr);
    if (!found) printf("Record not found for index number %d\n", indexno);
    printf("Press Enter to continue...");
    while (getchar() != '\n');
}

// Delete a student record
void delete_student() {
    struct student st;
    int indexno;
    printf("\n=== Delete Student Record ===\n");
    printf("Enter index number to delete: ");
    while (scanf("%d", &indexno) != 1 || indexno <= 0) {
        printf("Invalid index number. Enter a positive number: ");
        while (getchar() != '\n');
    }

    FILE *fptr = fopen("student.dat", "rb");
    if (!fptr) {
        printf("Error: Cannot open file!\n");
        return;
    }
    FILE *fptr2 = fopen("Temp.dat", "wb");
    if (!fptr2) {
        printf("Error: Cannot create temporary file!\n");
        fclose(fptr);
        return;
    }

    int found = 0;
    while (fread(&st, sizeof(st), 1, fptr) == 1) {
        if (st.indexno != indexno) {
            fwrite(&st, sizeof(st), 1, fptr2);
        } else {
            found = 1;
        }
    }
    fclose(fptr);
    fclose(fptr2);
    remove("student.dat");
    rename("Temp.dat", "student.dat");
    printf(found ? "Record deleted successfully.\n" : "Record not found for index number %d\n", indexno);
    printf("Press Enter to continue...");
    while (getchar() != '\n');
}

// Display class result in tabular format
void class_result() {
    struct student st;
    FILE *fptr = fopen("student.dat", "rb");
    if (!fptr) {
        printf("Error: File not found. Create records first.\n");
        printf("Press Enter to continue...");
        while (getchar() != '\n');
        return;
    }

    printf("\n=== All Students Result ===\n");
    printf("Index Name       P   C   M   E   CS  %%age  Grade\n");
    printf("-----------------------------------------------\n");
    while (fread(&st, sizeof(st), 1, fptr) == 1) {
        printf("%-5d %-10s %-3d %-3d %-3d %-3d %-3d %-5.2f  %c\n",
               st.indexno, st.name, st.p_marks, st.c_marks, st.m_marks,
               st.e_marks, st.cs_marks, st.per, st.grade);
    }
    fclose(fptr);
    printf("Press Enter to continue...");
    while (getchar() != '\n');
}

// Result menu
void result_menu() {
    int choice, indexno;
    char cont;
    do {
        printf("\n=== Result Menu ===\n");
        printf("1. Class Result\n");
        printf("2. Student Report Card\n");
        printf("3. Back to Main Menu\n");
        printf("Enter choice (1-3): ");
        while (scanf("%d", &choice) != 1 || choice < 1 || choice > 3) {
            printf("Invalid choice. Enter 1-3: ");
            while (getchar() != '\n');
        }
        while (getchar() != '\n');

        if (choice == 1) {
            class_result();
        } else if (choice == 2) {
            do {
                printf("\nEnter index number: ");
                while (scanf("%d", &indexno) != 1 || indexno <= 0) {
                    printf("Invalid index number. Enter a positive number: ");
                    while (getchar() != '\n');
                }
                while (getchar() != '\n');
                display_student(indexno);
                printf("View another student? (y/n): ");
                scanf("%c", &cont);
                while (getchar() != '\n');
            } while (cont == 'y' || cont == 'Y');
        }
    } while (choice != 3);
}

// Entry/Edit menu
void entry_menu() {
    int choice;
    do {
        printf("\n\n=== Entry/Edit Menu ===\n\n");
        printf("1. Create Student Record\n");
        printf("2. Display All Records\n");
        printf("3. Search Student Record\n");
        printf("4. Modify Student Record\n");
        printf("5. Delete Student Record\n");
        printf("6. Back to Main Menu\n");
        printf("Enter choice (1-6): ");
        while (scanf("%d", &choice) != 1 || choice < 1 || choice > 6) {
            printf("Invalid choice. Enter 1-6: ");
            while (getchar() != '\n');
        }
        while (getchar() != '\n');

        switch (choice) {
            case 1: write_student(); break;
            case 2: display_student(-1); break;
            case 3: {
                int indexno;
                printf("Enter index number: ");
                while (scanf("%d", &indexno) != 1 || indexno <= 0) {
                    printf("Invalid index number. Enter a positive number: ");
                    while (getchar() != '\n');
                }
                while (getchar() != '\n');
                display_student(indexno);
                break;
            }
            case 4: modify_student(); break;
            case 5: delete_student(); break;
        }
    } while (choice != 6);
}

// Introduction screen
void intro() {
    printf("\n=== Student Report Card System ===\n");
    printf("\n\nDeveloped by: Sadeepa Lakshan\n");
    printf("Institution: Faculty of Technology, University of Sri Jayewardenepura\n");
    printf("Manage student records and grades efficiently.\n");
    printf("Press Enter to continue...");
    while (getchar() != '\n');
}

int main() {
    intro();
    int choice;
    do {
        printf("\n=== Main Menu ===\n");
        printf("1. Result Menu\n");
        printf("2. Entry/Edit Menu\n");
        printf("3. Exit\n");
        printf("Enter choice (1-3): ");
        while (scanf("%d", &choice) != 1 || choice < 1 || choice > 3) {
            printf("Invalid choice. Enter 1-3: ");
            while (getchar() != '\n');
        }
        while (getchar() != '\n');

        switch (choice) {
            case 1: result_menu(); break;
            case 2: entry_menu(); break;
            case 3: printf("Exiting...\n"); break;
        }
    } while (choice != 3);
    return 0;
}
