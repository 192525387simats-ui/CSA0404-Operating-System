
#include <stdio.h>

int main()
{
    int block[10], process[10];
    int allocation[10];
    int m, n, i, j, choice;
    int best, worst;

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);

    printf("Enter size of each block:\n");
    for (i = 0; i < m; i++)
        scanf("%d", &block[i]);

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter size of each process:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &process[i]);

    printf("\n1. First Fit\n2. Best Fit\n3. Worst Fit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    for (i = 0; i < n; i++)
        allocation[i] = -1;

    if (choice == 1)
    {
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < m; j++)
            {
                if (block[j] >= process[i])
                {
                    allocation[i] = j;
                    block[j] -= process[i];
                    break;
                }
            }
        }
    }
    else if (choice == 2)
    {
        for (i = 0; i < n; i++)
        {
            best = -1;
            for (j = 0; j < m; j++)
            {
                if (block[j] >= process[i] &&
                    (best == -1 || block[j] < block[best]))
                    best = j;
            }

            if (best != -1)
            {
                allocation[i] = best;
                block[best] -= process[i];
            }
        }
    }
    else if (choice == 3)
    {
        for (i = 0; i < n; i++)
        {
            worst = -1;
            for (j = 0; j < m; j++)
            {
                if (block[j] >= process[i] &&
                    (worst == -1 || block[j] > block[worst]))
                    worst = j;
            }

            if (worst != -1)
            {
                allocation[i] = worst;
                block[worst] -= process[i];
            }
        }
    }
    else
    {
        printf("Invalid choice.\n");
        return 0;
    }

    printf("\nProcess Size\tAllocated Block\n");

    for (i = 0; i < n; i++)
    {
        printf("%d\t\t", process[i]);

        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }

    return 0;
}

