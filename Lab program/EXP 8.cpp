
#include <stdio.h>

int main() {
    int n, bt[20], rem[20], wt[20], tat[20];
    int quantum, time = 0, done;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    if (n <= 0 || n > 20) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter burst time of P%d: ", i + 1);
        scanf("%d", &bt[i]);

        if (bt[i] <= 0) {
            printf("Burst time must be positive.\n");
            return 1;
        }

        rem[i] = bt[i];
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    if (quantum <= 0) {
        printf("Invalid time quantum.\n");
        return 1;
    }

    do {
        done = 1;

        for (int i = 0; i < n; i++) {
            if (rem[i] > 0) {
                done = 0;

                if (rem[i] > quantum) {
                    time += quantum;
                    rem[i] -= quantum;
                } else {
                    time += rem[i];
                    rem[i] = 0;
                    tat[i] = time;
                    wt[i] = tat[i] - bt[i];
                }
            }
        }
    } while (!done);

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n",
               i + 1, bt[i], wt[i], tat[i]);
    }

    return 0;
}

