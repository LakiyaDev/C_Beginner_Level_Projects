#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_INVOICES 100
#define MAX_ITEMS 50
#define MAX_NAME_LEN 50

// Global arrays to store invoices
char customer_names[MAX_INVOICES][MAX_NAME_LEN];
char invoice_dates[MAX_INVOICES][20];
int invoice_item_counts[MAX_INVOICES];

char item_names[MAX_INVOICES][MAX_ITEMS][MAX_NAME_LEN];
float item_prices[MAX_INVOICES][MAX_ITEMS];
int item_quantities[MAX_INVOICES][MAX_ITEMS];

float invoice_subtotals[MAX_INVOICES];
float invoice_discounts[MAX_INVOICES];
float invoice_taxes[MAX_INVOICES];
float invoice_totals[MAX_INVOICES];

int invoice_count = 0;
int choice;

void getCurrentDate(char* buffer) {
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    strftime(buffer, 20, "%d-%m-%Y", tm_info);
}

void mainmenu() {
    printf("\n===== LakiyaDev Restaurant Billing System =====\n");
    printf("1. Generate Invoice\n");
    printf("2. Show All Invoices\n");
    printf("3. Search Invoice\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
}

void generateInvoice() {
    if (invoice_count >= MAX_INVOICES) {
        printf("Invoice storage is full!\n");
        return;
    }

    int i = invoice_count;
    invoice_subtotals[i] = 0;

    printf("Enter customer name: ");
    scanf(" %[^\n]%*c", customer_names[i]);

    printf("Enter number of items: ");
    scanf("%d", &invoice_item_counts[i]);

    for (int j = 0; j < invoice_item_counts[i]; j++) {
        printf("\nItem %d:\n", j + 1);

        printf("  Name: ");
        scanf(" %[^\n]%*c", item_names[i][j]);

        printf("  Unit Price: ");
        scanf("%f", &item_prices[i][j]);

        printf("  Quantity: ");
        scanf("%d", &item_quantities[i][j]);

        invoice_subtotals[i] += item_prices[i][j] * item_quantities[i][j];
    }

    invoice_discounts[i] = 0.05 * invoice_subtotals[i];
    float net = invoice_subtotals[i] - invoice_discounts[i];
    invoice_taxes[i] = 0.1 * net;
    invoice_totals[i] = net + invoice_taxes[i];

    getCurrentDate(invoice_dates[i]);

    printf("\n========== Invoice ==========\n");
    printf("Date: %s\n", invoice_dates[i]);
    printf("Customer: %s\n", customer_names[i]);
    printf("-----------------------------\n");
    printf("Item            Price  Qty   Total\n");

    for (int j = 0; j < invoice_item_counts[i]; j++) {
        float total = item_prices[i][j] * item_quantities[i][j];
        printf("%-15s %.2f  %3d   %.2f\n", item_names[i][j], item_prices[i][j], item_quantities[i][j], total);
    }

    printf("-----------------------------\n");
    printf("Subtotal   : %.2f\n", invoice_subtotals[i]);
    printf("Discount   : -%.2f\n", invoice_discounts[i]);
    printf("Tax        : +%.2f\n", invoice_taxes[i]);
    printf("Grand Total: %.2f\n", invoice_totals[i]);
    printf("==============================\n");

    invoice_count++;
}

void showAllInvoice() {
    if (invoice_count == 0) {
        printf("No invoices available.\n");
        return;
    }

    for (int i = 0; i < invoice_count; i++) {
        printf("\n========== Invoice %d ==========\n", i + 1);
        printf("Date: %s\n", invoice_dates[i]);
        printf("Customer: %s\n", customer_names[i]);
        printf("-----------------------------\n");
        printf("Item            Price  Qty   Total\n");

        for (int j = 0; j < invoice_item_counts[i]; j++) {
            float total = item_prices[i][j] * item_quantities[i][j];
            printf("%-15s %.2f  %3d   %.2f\n", item_names[i][j], item_prices[i][j], item_quantities[i][j], total);
        }

        printf("-----------------------------\n");
        printf("Subtotal   : %.2f\n", invoice_subtotals[i]);
        printf("Discount   : -%.2f\n", invoice_discounts[i]);
        printf("Tax        : +%.2f\n", invoice_taxes[i]);
        printf("Grand Total: %.2f\n", invoice_totals[i]);
        printf("==============================\n");
    }
}

void searchInvoice() {
    char name[50];
    int found = 0;

    printf("Enter customer name to search: ");
    scanf(" %[^\n]%*c", name);

    for (int i = 0; i < invoice_count; i++) {
        if (strcmp(customer_names[i], name) == 0) {
            found = 1;
            printf("\n========== Invoice Found ==========\n");
            printf("Date: %s\n", invoice_dates[i]);
            printf("Customer: %s\n", customer_names[i]);
            printf("-----------------------------\n");
            printf("Item            Price  Qty   Total\n");

            for (int j = 0; j < invoice_item_counts[i]; j++) {
                float total = item_prices[i][j] * item_quantities[i][j];
                printf("%-15s %.2f  %3d   %.2f\n", item_names[i][j], item_prices[i][j], item_quantities[i][j], total);
            }

            printf("-----------------------------\n");
            printf("Subtotal   : %.2f\n", invoice_subtotals[i]);
            printf("Discount   : -%.2f\n", invoice_discounts[i]);
            printf("Tax        : +%.2f\n", invoice_taxes[i]);
            printf("Grand Total: %.2f\n", invoice_totals[i]);
            printf("==============================\n");
        }
    }

    if (!found) {
        printf("No invoice found for customer: %s\n", name);
    }
}

int main() {
    while (1) {
        mainmenu();

        switch (choice) {
            case 1:
                generateInvoice();
                break;
            case 2:
                showAllInvoice();
                break;
            case 3:
                searchInvoice();
                break;
            case 4:
                printf("Exiting system. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
