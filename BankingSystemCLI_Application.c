#include <stdio.h>
#include <stdlib.h>

int main() {
    float withdraw = 0, deposit = 0, transfer = 0;
    char name[24];
    float balance = 5000;
    int account, account2;
    int transaction = 1;

    // Welcome message
    printf("\n---WELCOME TO OUR LakiyaDEV BANKING SYSTEM---\n\n");;

    // Input user details
    printf("Enter your name: ");
    scanf("%s", name);
    printf("Please enter your account no.: ");
    scanf("%d", &account);

    // Main transaction loop
    while (transaction == 1) {
        int option;
        printf("\nChoose what you want to do :\n");
        printf("  1 - Balance Inquiry\n");
        printf("  2 - Deposit\n");
        printf("  3 - Withdraw\n");
        printf("  4 - Transfer\n");
        printf("Enter Your Option:");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("\n---*BALANCE INQUIRY*---\n");
                printf("\nYour current balance is: %.2fRs .\n", balance);
                break;

            case 2:
                printf("\n---*DEPOSIT AMOUNT*---\n");
                printf("\nHow much money do you want to deposit?: ");
                scanf("%f", &deposit);
                if (deposit > 0 && deposit <= 100000) {
                    printf("Your %.2fRs deposited in your account.\n", deposit);
                    balance += deposit;
                    printf("Your current balance is: %.2fRs .\n", balance);
                } else if (deposit > 100000) {
                    printf("You can't deposit that much amount at one time.\n");
                    deposit = 0; // Reset deposit for receipt
                } else {
                    printf("Invalid deposit amount.\n");
                    deposit = 0; // Reset deposit for receipt
                }
                break;

            case 3:
                printf("\n---*WITHDRAW AMOUNT*---\n");
                printf("\nHow much money do you want to withdraw?:");
                scanf("%f", &withdraw);
                if (withdraw <= balance && withdraw <= 100000 && withdraw > 0) {
                    printf("You just withdrew %.2fRs\n", withdraw);
                    balance -= withdraw;
                    printf("Your current balance is: %.2fRs .\n", balance);
                } else if (withdraw > 100000) {
                    printf("You can't withdraw that much amount at one time.\n");
                    withdraw = 0; // Reset withdraw for receipt
                } else if (withdraw > balance) {
                    printf("You don't have enough money.\n");
                    withdraw = 0; // Reset withdraw for receipt
                } else {
                    printf("Invalid withdraw amount.\n");
                    withdraw = 0; // Reset withdraw for receipt
                }
                break;

            case 4:
                printf("\n---*TRANSFER AMOUNT*---\n");
                printf("\nAccount you want to transfer to: ");
                scanf("%d", &account2);
                printf("How much amount?: ");
                scanf("%f", &transfer);
                if (transfer > 0 && balance >= transfer && transfer <= 100000) {
                    printf("Your %.2fRs successfully transferred\n", transfer);
                    balance -= transfer;
                    printf("Your current balance is: %.2fRs .\n", balance);
                } else if (transfer > balance) {
                    printf("You do not have sufficient balance\n");
                    transfer = 0; // Reset transfer for receipt
                } else if (transfer > 100000) {
                    printf("You can't transfer that much amount at one time.\n");
                    transfer = 0; // Reset transfer for receipt
                } else {
                    printf("Invalid transfer amount\n");
                    transfer = 0; // Reset transfer for receipt
                }
                break;

            default:
                printf("Invalid transaction\n");
                break;
        }

        // Ask for another transaction
        transaction = 0;
        while (transaction != 1 && transaction != 2) {
            printf("\nDo you want to do another transaction?\n");
            printf("  1. Yes   2. No\n");
            scanf("%d", &transaction);
            if (transaction != 1 && transaction != 2) {
                printf("Invalid choice.Choose between 1 and 2 only\n");
            }
        }
    }

    // Clear screen simulation
    printf("\n\n");

    // Print receipt
    printf("\n---*LakiyaDEV BANK LIMITED*---\n");
    printf("\nYour name: %s", name);
    printf("\nYour account no: %d", account);

    if (deposit > 0 && deposit <= 100000) {
        printf("\n*You've deposited %.2fRs.", deposit);
    } else {
        printf("\n*You've deposited 0Rs.");
    }

    if (withdraw > 0 && withdraw <= 100000 && withdraw <= balance + withdraw) {
        printf("\n*You've withdrawn %.2fRs.", withdraw);
    } else {
        printf("\nYou've withdrawn 0Rs.");
    }

    if (transfer > 0 && transfer <= 100000 && transfer <= balance + transfer) {
        printf("\nYou've transferred %.2fRs.", transfer);
    } else {
        printf("\nYou've transferred 0Rs.");
    }

    printf("\n\n---*Thank you for transact with us!*--- \n");
    printf("---*www.LakiyaDEVBankingSystem.com*---\n");

    // Pause before exit (replacing getch())
    printf("\nPress Enter to exit...");
    getchar(); // Clear input buffer
    getchar(); // Wait for Enter key

    return 0;
}
