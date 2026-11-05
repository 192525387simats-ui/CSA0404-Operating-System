
#include <stdio.h>

int main() {
    int n, i, time = 0, completed = 0;
    int at[20], bt[20], wt[20], tat[20], done[20] = {0};

    printf("Enter number of processes: ");
    scanf("%d", &n);

    if (n <= 0 || n > 20) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("Enter arrival time and burst time of P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);

        if (at[i] < 0 || bt[i] <= 0) {
            printf("Invalid input.\n");
            return 1;
        }
    }

    while (completed < n) {
        int k = -1;

        for (i = 0; i < n; i++) {
            if (!done[i] && at[i] <= time) {
                if (k == -1 || bt[i] < bt[k])
                    k = i;
            }
        }

        if (k == -1) {
            time++;
            continue;
        }

        wt[k] = time - at[k];
        time += bt[k];
        tat[k] = time - at[k];

        done[k] = 1;
        completed++;
    }

    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");

    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], wt[i], tat[i]);
    }

    return 0;
}


