#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ERROR_VALUE -9999999.0

void printMenu();
double division(double,double);
double modulus(int,int);

int main()
{
    int choice;
    double num1,num2,result;

    printf("-------------------------------\n");
    printf("Welcome to Simple Calculator");

    while(1){
        printMenu();
        printf("Now Enter Your Choice:");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        if (choice == 7){
            printf("\nExit Successfully....");
            break;
        }

        if (choice < 1 || choice > 7) {
            printf("Invalid choice! Please select 1-7.\n");
            continue;
        }

        printf("\nEnter Your First Number: ");
        if (scanf("%lf", &num1) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        printf("Enter Your Second Number: ");
        if (scanf("%lf", &num2) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch(choice){
        case 1://Add
            result= num1 + num2;
            break;
        case 2://Subtract
            result= num1 - num2;
            break;
        case 3://Multiply
            result= num1 * num2;
            break;
        case 4://Divide
            result= division(num1,num2);
            break;
        case 5://Modulus
            result= modulus(num1,num2);
            break;
        case 6://Power
            result= pow(num1,num2);
            break;
        default:
            printf("Unexpected error!\n");
            continue;
        }
    if (result == ERROR_VALUE) {
            printf("Operation failed due to invalid arguments.\n");
        } else {
            printf("Result of operation is %.2f\n", result);
        }
    }
    return 0;
}

void printMenu(){
    printf("\n\nChoose one of the following options:\n");
        printf("1.Add\n");
        printf("2.Subtract\n");
        printf("3.Multiply\n");
        printf("4.Divide\n");
        printf("5.Modulus\n");
        printf("6.Power\n");
        printf("7.Exit\n\n");
}

double division(double a, double b){
    if (b==0){
        fprintf(stderr,"Invalid Argument for Division.\n");
        return ERROR_VALUE;
    }
    return a/b;
}

double modulus(int a, int b){
    if (b==0){
        fprintf(stderr,"Invalid Argument for Modulus.\n");
        return ERROR_VALUE;
    }
    return a % b;
}

