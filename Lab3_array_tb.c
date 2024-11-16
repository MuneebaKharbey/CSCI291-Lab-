#include <stdio.h>

int main (void)
{
    int balance = 1000;
    int initial_balance = 1000;
    int transactions[] = {-1500, -200, -400, -50, -200, 300};
    int length = sizeof(transactions) / sizeof(transactions[0]);
    int tobeprocessed[] = {};
    int tobeprocessed_count = 0;
    int b = 0;
    
    for (int i = 0; i < length; i++)
    {
        int current_transaction = transactions[i];

        if (current_transaction < 0 && current_transaction > initial_balance)
        {
            if (balance < 0)
            {
                int l = i;
                printf("\nNo Further Transactions can be processed\n");
                for (int k = tobeprocessed_count; k <= (length - i + 1); k++)
                {
                    tobeprocessed[k] = transactions[l];
                    l++;
                    b++;                   
                }
                break;
            printf("\nYour transaction of %d is an Invalid transaction\n", current_transaction);
            tobeprocessed[tobeprocessed_count] = current_transaction;
            tobeprocessed_count ++;
            continue;
        }
        else
        {
            balance = balance + current_transaction;
            int l = i;
            
            if (balance < 0)
            {
                printf("\nNo Further Transactions can be processed\n");
                for (int k = tobeprocessed_count; k <= (length - i + 1); k++)
                {
                    tobeprocessed[k] = transactions[l];
                    l++;
                    b++;                   
                }
                break;
            }
        }
    }

printf("\n");
printf("Final Balance: %d\n", balance);
printf("To be processed: {");
printf("%d", tobeprocessed[0]);
for (int a = 1; a < (tobeprocessed_count + b); a++)
{
    printf(" ,%d", tobeprocessed[a]);
}
printf("}");
}
