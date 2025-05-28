#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME 20
#define C_PROGRAMMING_QUESTIONS 10

typedef struct {
    char question[100];
    char options[4][50];
    char correct;
} Question;

typedef struct {
    char name[MAX_NAME];
    int correct_answers;
} HighScore;

Question c_programming_questions[C_PROGRAMMING_QUESTIONS] = {
    {"What is the correct syntax for the main function in C?",
     {"A. void main()", "B. int main()", "C. main()", "D. start()"}, 'B'},
    {"Which keyword is used to define a constant in C?",
     {"A. const", "B. static", "C. final", "D. define"}, 'A'},
    {"What does the 'sizeof' operator return?",
     {"A. Address of a variable", "B. Size of a variable in bytes", "C. Value of a variable", "D. Type of a variable"}, 'B'},
    {"Which function is used to read a string from standard input?",
     {"A. scanf()", "B. gets()", "C. fgets()", "D. read()"}, 'C'},
    {"What is the purpose of the 'break' statement in a loop?",
     {"A. Skip to next iteration", "B. Exit the loop", "C. Restart the loop", "D. Pause the loop"}, 'B'},
    {"What is the output of 'printf(\"%d\", 5 / 2);'?",
     {"A. 2.5", "B. 2", "C. 3", "D. 0"}, 'B'},
    {"Which symbol is used for pointer dereferencing in C?",
     {"A. &", "B. *", "C. ->", "D. ."}, 'B'},
    {"What is the default return type of a function if not specified?",
     {"A. void", "B. int", "C. float", "D. char"}, 'B'},
    {"Which header file is required for dynamic memory allocation functions?",
     {"A. <stdio.h>", "B. <string.h>", "C. <stdlib.h>", "D. <ctype.h>"}, 'C'},
    {"What does the 'NULL' macro represent in C?",
     {"A. Zero value", "B. Invalid pointer", "C. Empty string", "D. Uninitialized variable"}, 'B'}
};

// Function prototypes
void display_menu();
void display_help();
void show_high_score();
void reset_high_score();
void save_high_score(const char *name, int correct_answers);
void play_game(char *player_name);

void get_safe_string(char *buffer, int size) {
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
}

void display_menu() {
    printf("\n---------- C PROGRAMMING QUIZ GAME ----------\n");
    printf("\nWELCOME TO THE GAME !\n");
    printf("> 1 - Start Game\n");
    printf("> 2 - View High Score\n");
    printf("> 3 - Reset High Score\n");
    printf("> 4 - Help\n");
    printf("> 5 - Quit\n");
    printf("Enter your choice (1-5): ");
}

void display_help() {
    printf("\n---------- HELP ----------\n");
    printf("\nC Programming Quiz Game\n");
    printf("- The game consists of 10 questions on C programming.\n");
    printf("- Select A, B, C, or D for each answer.\n");
    printf("- No negative marking for wrong answers.\n");
    printf("- Your score is the number of correct answers.\n");
    printf("\nBest of Luck!\n");
    printf("Press Enter to return to menu...");
    getchar();
}

void show_high_score() {
    FILE *f = fopen("score.txt", "r");
    if (!f) {
        printf("\nNo high score available.\n");
        return;
    }
    char name[MAX_NAME];
    int correct_answers;
    if (fscanf(f, "%19s %d", name, &correct_answers) == 2) {
        printf("\nHigh Score: %s - %d/10 correct\n", name, correct_answers);
    } else {
        printf("\nError reading high score.\n");
    }
    fclose(f);
    printf("\nPress Enter to return to menu...");
    getchar();
}

void reset_high_score() {
    FILE *f = fopen("score.txt", "w");
    if (!f) {
        printf("\nError resetting high score.\n");
        return;
    }
    fprintf(f, "Unknown 0\n");
    fclose(f);
    printf("\nHigh score reset.\n");
    printf("\nPress Enter to return to menu...");
    getchar();
}

void save_high_score(const char *name, int correct_answers) {
    FILE *f = fopen("score.txt", "r");
    int current_score = 0;
    char current_name[MAX_NAME] = "Unknown";
    if (f) {
        if (fscanf(f, "%19s %d", current_name, &current_score) != 2) {
            current_score = 0;
        }
        fclose(f);
    }
    if (correct_answers >= current_score) {
        f = fopen("score.txt", "w");
        if (f) {
            fprintf(f, "%s %d\n", name, correct_answers);
            fclose(f);
        }
    }
}

void play_game(char *player_name) {
    printf("\nWelcome %s to C Programming Quiz Game!\n", player_name);
    printf("\nInstructions:\n");
    printf("- Answer 10 questions on C programming by selecting A, B, C, or D.\n");
    printf("- No negative marking for wrong answers.\n");
    printf("- Your score is based on correct answers.\n");
    printf("Press Enter to start...");
    getchar();

    // Challenge Round
    int correct_answers = 0;
    for (int i = 0; i < C_PROGRAMMING_QUESTIONS; i++) {
        printf("\nQuestion %d: %s\n", i + 1, c_programming_questions[i].question);
        for (int j = 0; j < 4; j++) {
            printf("%s\n", c_programming_questions[i].options[j]);
        }
        printf("Your answer (A-D): ");
        char answer = toupper(getchar());
        while (answer != 'A' && answer != 'B' && answer != 'C' && answer != 'D') {
            printf("Invalid input! Please enter A, B, C, or D: ");
            answer = toupper(getchar());
        }
        getchar(); // Clear newline
        if (answer == c_programming_questions[i].correct) {
            printf("Brilliant! Onward to the next question!\n");
            correct_answers++;
        } else {
            printf("Sorry, that's incorrect. Correct answer: %c\n", c_programming_questions[i].correct);
        }
        printf("Press Enter to continue...");
        getchar();
    }

    // Display score
    printf("\nGame Complete!\n");
    printf("You answered %d/%d questions correctly.\n", correct_answers, C_PROGRAMMING_QUESTIONS);
    if (correct_answers == C_PROGRAMMING_QUESTIONS) {
        printf("Perfect score! You're a C programming champion!\n");
    } else if (correct_answers >= C_PROGRAMMING_QUESTIONS / 2) {
        printf("Great job! Solid C programming skills!\n");
    } else {
        printf("Nice try! Keep studying C to improve your score!\n");
    }
    save_high_score(player_name, correct_answers);
    printf("\nPress Enter to return to menu...");
    getchar();
}

int main() {
    char player_name[MAX_NAME];
    int choice;

    while (1) {
        display_menu();
        if (scanf("%d", &choice) != 1 || choice < 1 || choice > 5) {
            printf("\nInvalid choice! Choose 1-5.\n");
            while (getchar() != '\n'); // Clear input buffer
            printf("Press Enter to continue...");
            getchar();
            continue;
        }
        getchar(); // Clear newline

        switch (choice) {
            case 1:
                printf("Enter your name: ");
                get_safe_string(player_name, MAX_NAME);
                if (strlen(player_name) == 0) strcpy(player_name, "Player");
                play_game(player_name);
                break;
            case 2:
                show_high_score();
                break;
            case 3:
                reset_high_score();
                break;
            case 4:
                display_help();
                break;
            case 5:
                printf("\nThanks for playing!\n");
                return 0;
        }
    }
    return 0;
}
