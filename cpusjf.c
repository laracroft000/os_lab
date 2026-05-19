#include <stdio.h>
#include <limits.h>

int main()
{
    int n, i, time = 0, completed = 0;
    int pid[10], at[10], bt[10], ct[10], tat[10], wt[10];
    int done[10] = {0};

    /* Gantt Chart arrays */
    int gantt_pid[20], gantt_time[20];
    int g = 0;

    float avg_wt = 0, avg_tat = 0;

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

    /* SJF Non-Preemptive Scheduling */
    while(completed < n)
    {
        int min_bt = INT_MAX;
        int index = -1;

        /* Select shortest job among arrived processes */
        for(i = 0; i < n; i++)
        {
            if(at[i] <= time && done[i] == 0 && bt[i] < min_bt)
            {
                min_bt = bt[i];
                index = i;
            }
        }

        if(index == -1)
        {
            time++;   /* CPU idle */
        }
        else
        {
            /* Gantt Chart entry */
            gantt_pid[g] = pid[index];
            gantt_time[g] = time;
            g++;

            time = time + bt[index];
            ct[index] = time;
            tat[index] = ct[index] - at[index];
            wt[index] = tat[index] - bt[index];

            avg_wt += wt[index];
            avg_tat += tat[index];

            done[index] = 1;
            completed++;
        }
    }

    gantt_time[g] = time;

    /* Output Table */
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", avg_wt / n);
    printf("Average Turnaround Time = %.2f\n", avg_tat / n);

    /* Gantt Chart Output */
    printf("\nGantt Chart:\n");

    for(i = 0; i < g; i++)
    {
        printf("|  P%d  ", gantt_pid[i]);
    }
    printf("|\n");

    for(i = 0; i <= g; i++)
    {
        printf("%-6d", gantt_time[i]);
    }
    printf("\n");

    return 0;
}