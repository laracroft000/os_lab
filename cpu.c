#include <stdio.h>
#include <limits.h>

int main()
{
    int n, i, time = 0, completed = 0;
    int pid[10], at[10], bt[10], rt[10];
    int ct[10], tat[10], wt[10];

    /* Gantt chart */
    int gantt_pid[50], gantt_time[50];
    int g = 0;

    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    /* Input */
    for(i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        printf("Enter Arrival Time of P%d: ", pid[i]);
        scanf("%d", &at[i]);
        printf("Enter Burst Time of P%d: ", pid[i]);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];   // remaining time
    }

    /* SRTF Scheduling */
    while(completed < n)
    {
        int min_rt = INT_MAX;
        int index = -1;

        /* Select process with shortest remaining time */
        for(i = 0; i < n; i++)
        {
            if(at[i] <= time && rt[i] > 0 && rt[i] < min_rt)
            {
                min_rt = rt[i];
                index = i;
            }
        }

        if(index == -1)
        {
            time++;   // CPU idle
        }
        else
        {
            /* Gantt chart entry (only when process changes) */
            if(g == 0 || gantt_pid[g-1] != pid[index])
            {
                gantt_pid[g] = pid[index];
                gantt_time[g] = time;
                g++;
            }

            rt[index]--;   // execute for 1 unit
            time++;

            /* If process completes */
            if(rt[index] == 0)
            {
                ct[index] = time;
                tat[index] = ct[index] - at[index];
                wt[index] = tat[index] - bt[index];

                avg_wt += wt[index];
                avg_tat += tat[index];

                completed++;
            }
        }
    }

    gantt_time[g] = time;

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