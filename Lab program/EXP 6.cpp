
#include <stdio.h>

int main() {
    int n, i, time = 0, completed = 0;
    int at[20], bt[20], rem[20], pr[20];
    int wt[20], tat[20];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    if (n <= 0 || n > 20) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("Enter arrival time, burst time and priority of P%d: ",
               i + 1);
        scanf("%d %d %d", &at[i], &bt[i], &pr[i]);

        if (at[i] < 0 || bt[i] <= 0 || pr[i] < 0) {
            printf("Invalid input.\n");
            return 1;
        }

        rem[i] = bt[i];
    }

    while (completed < n) {
        int k = -1;

        for (i = 0; i < n; i++) {
            if (at[i] <= time && rem[i] > 0) {
                if (k == -1 || pr[i] < pr[k])
                    k = i;
            }
        }

        if (k == -1) {
            time++;
            continue;
        }

        rem[k]--;
        time++;

        if (rem[k] == 0) {
            completed++;
            tat[k] = time - at[k];
            wt[k] = tat[k] - bt[k];
        }
    }

    printf("\nProcess\tArrival\tBurst\tPriority\tWaiting\tTurnaround\n");

    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\n",
               i + 1, at[i], bt[i], pr[i], wt[i], tat[i]);
    }

    return 0;
}

5
