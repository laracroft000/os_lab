#include <stdio.h>

int main()
{
    int n, i, j;
    int pid[10], at[10], bt[10];
    int ct[10], tat[10], wt[10];
    int time = 0;

    /* Gantt chart arrays */
    int gantt_pid[10], gantt_time[11];

    float avg_wt = 0;
    float avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    /* Input Arrival Time and Burst Time */
    for(i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        printf("Enter Arrival Time of P%d: ", pid[i]);
        scanf("%d", &at[i]);
        printf("Enter Burst Time of P%d: ", pid[i]);
        scanf("%d", &bt[i]);
    }

    /* Sort processes by Arrival Time (FCFS rule) */
    for(i = 0; i < n - 1; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            if(at[i] > at[j])
            {
                int temp;
                temp = at[i]; at[i] = at[j]; at[j] = temp;
                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
                temp = pid[i]; pid[i] = pid[j]; pid[j] = temp;
            }
        }
    }

    /* FCFS Calculation */
    for(i = 0; i < n; i++)
    {
        if(time < at[i])
            time = at[i];   // CPU idle handling

        /* Gantt chart entry */
        gantt_pid[i] = pid[i];
        gantt_time[i] = time;

        time = time + bt[i];
        ct[i] = time;

        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    gantt_time[n] = time;

    /* Output table */
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", avg_wt / n);
    printf("Average Turnaround Time = %.2f\n", avg_tat / n);

    /* Gantt Chart */
    printf("\nGantt Chart:\n");

    for(i = 0; i < n; i++)
    {
        printf("|  P%d  ", gantt_pid[i]);
    }
    printf("|\n");

    for(i = 0; i <= n; i++)
    {
        printf("%-6d", gantt_time[i]);
    }
    printf("\n");

    return 0;
}