#include <stdio.h>

int main(void) {
    int balance = 1000; // Initial balance
    int transactions[] = {1500, -2000, -50, -200, 300, -3000, 600, -1150, 400, -300}; // List of transactions
    int length = sizeof(transactions) / sizeof(transactions[0]); // Number of transactions

    // Array to hold transactions that cannot be processed
    int tobeprocessed[length]; // Size should be at least the same as the number of transactions
    int tobeprocessed_count = 0; // Counter for the number of unprocessed transactions

    for (int i = 0; i < length; i++) {
        int current_transaction = transactions[i]; // Current transaction
        
        if (current_transaction >= 0) {
            // Deposit: add to balance
            balance = balance + current_transaction;
        } else if (current_transaction < 0) {
            // Withdrawal: check if balance is sufficient
            if (balance < (-current_transaction)) {
                // Insufficient balance: add transaction to "to be processed"
                printf("\nInvalid Transaction of %d\n", current_transaction);
                tobeprocessed[tobeprocessed_count] = current_transaction;
                tobeprocessed_count++;
            } else {
                // Sufficient balance: process transaction
                balance = balance + current_transaction;
            }
        }

        if (balance == 0) {
            // If balance reaches zero, stop further transactions
            printf("\nNo Further Transactions can be processed\n");

            // Add remaining transactions to "to be processed"
            for (int z = (i + 1); z < length; z++) {
                tobeprocessed[tobeprocessed_count] = transactions[z];
                tobeprocessed_count++;
            }
            break;
        }
    }

    // Print the final balance
    printf("\nFinal Balance: %d\n", balance);

    // Print the "to be processed" transactions
    printf("To be processed: {");
    if (tobeprocessed_count > 0) {
        printf("%d", tobeprocessed[0]);
        for (int a = 1; a < tobeprocessed_count; a++) {
            printf(", %d", tobeprocessed[a]);
        }
    }
    printf("}\n");

    return 0;
}
