#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], ct[n], tat[n], wt[n], done[n];
    for(int i = 0; i < n; i++) done[i] = 0;

    for(int i = 0; i < n; i++) {
        printf("Enter arrival time of P%d: ", i);
        scanf("%d", &at[i]);
        printf("Enter burst time of P%d: ", i);
        scanf("%d", &bt[i]);
    }

    int time = 0, completed = 0;
    float total_tat = 0, total_wt = 0;

    printf("\nGantt Chart:\n|");

    while(completed < n) {
        int idx = -1, min_bt = 9999;

        for(int i = 0; i < n; i++) {
            if(!done[i] && at[i] <= time && bt[i] < min_bt) {
                min_bt = bt[i];
                idx = i;
            }
        }

        if(idx == -1) {
            time++;
        } else {
            printf("  P%d  |", idx);

            time += bt[idx];
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            total_tat += tat[idx];
            total_wt += wt[idx];
            done[idx] = 1;
            completed++;
        }
    }

    printf("\n0");
    for(int i = 0; i < n; i++)
        printf("     %d", ct[i]);
    printf("\n");

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i, at[i], bt[i], ct[i], tat[i], wt[i]);

    printf("\nAverage TAT = %.2f", total_tat/n);
    printf("\nAverage WT  = %.2f\n", total_wt/n);

    return 0;
}
