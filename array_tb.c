#include <stdio.h>

int main (void)
{
    int balance = 1000;
    int transactions[] = {2000, 1500, -1001, -400, -50, -200, 300};
    int length = sizeof(transactions) / sizeof(transactions[0]);
    int tobeprocessed[] = {};
    int tobeprocessed_count = 0;

    for (int i = 0; i < length; i++)
    {
        int current_transaction = transactions[i];

        if (current_transaction > balance)
        {
            printf("\nInvalid transaction\n");
            int len_tbp = sizeof(tobeprocessed) / sizeof(tobeprocessed[0]);
            tobeprocessed[tobeprocessed_count] = current_transaction;
            
            for (int j = 0; j<= tobeprocessed_count; j++)
            {
                printf("%d, ", tobeprocessed[j]);
            }
            tobeprocessed_count ++;
            continue;
        }
        //continue;
        else
        {
            balance = balance + current_transaction;
            if (balance < 0)
            {
                printf("\nNo Further Transactions can be processed\n");
                for (int k = tobeprocessed_count; k < (length - i); k++)
                {
                    tobeprocessed[k] = transactions[length - i]
                }
                break;
            }
        }
    }


}