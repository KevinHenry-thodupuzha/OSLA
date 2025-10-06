

#include <stdio.h>

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], ct[n], tat[n], wt[n];

    for(int i = 0; i < n; i++) {
        printf("Enter arrival time of P%d: ", i);
        scanf("%d", &at[i]);
        printf("Enter burst time of P%d: ", i);
        scanf("%d", &bt[i]);
    }

    // Sort by arrival time
    for(int i = 0; i < n-1; i++) {
        for(int j = i+1; j < n; j++) {
            if(at[i] > at[j]) {
                int temp;
                temp = at[i]; at[i] = at[j]; at[j] = temp;
                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
            }
        }
    }

    int time = 0;
    for(int i = 0; i < n; i++) {
        if(time < at[i]) time = at[i];  // idle time
        ct[i] = time + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        time = ct[i];
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", i, at[i], bt[i], ct[i], tat[i], wt[i]);

    // Gantt chart
    printf("\nGantt Chart:\n|");
    for(int i = 0; i < n; i++) printf("  P%d  |", i);
    printf("\n0");
    for(int i = 0; i < n; i++) printf("     %d", ct[i]);
    printf("\n");

    return 0;
}
