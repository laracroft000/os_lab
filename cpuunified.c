#include <stdio.h>
#include <limits.h>

#define MAX 10

float fcfs(int n, int at[], int bt[])
{
    int ct[MAX], tat[MAX], wt[MAX];
    int time = 0;
    int gantt_pid[MAX], gantt_time[MAX+1];
    float avg_wt = 0;

    for(int i = 0; i < n; i++)
    {
        if(time < at[i])
            time = at[i];

        gantt_pid[i] = i + 1;
        gantt_time[i] = time;

        time += bt[i];
        ct[i] = time;

        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        avg_wt += wt[i];
    }
    gantt_time[n] = time;

    printf("\nFCFS Gantt Chart:\n");
    for(int i = 0; i < n; i++)
        printf("| P%d ", gantt_pid[i]);
    printf("|\n");

    for(int i = 0; i <= n; i++)
        printf("%-4d", gantt_time[i]);
    printf("\n");

    return avg_wt / n;
}

float srtf(int n, int at[], int bt[])
{
    int rt[MAX], completed = 0, time = 0;
    int wt[MAX], tat[MAX], ct[MAX];
    int gantt_pid[50], gantt_time[50], g = 0;
    float avg_wt = 0;

    for(int i = 0; i < n; i++)
        rt[i] = bt[i];

    while(completed < n)
    {
        int min = INT_MAX, idx = -1;

        for(int i = 0; i < n; i++)
            if(at[i] <= time && rt[i] > 0 && rt[i] < min)
            {
                min = rt[i];
                idx = i;
            }

        if(idx == -1)
        {
            time++;
            continue;
        }

        if(g == 0 || gantt_pid[g-1] != idx+1)
        {
            gantt_pid[g] = idx + 1;
            gantt_time[g] = time;
            g++;
        }

        rt[idx]--;
        time++;

        if(rt[idx] == 0)
        {
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            avg_wt += wt[idx];
            completed++;
        }
    }
    gantt_time[g] = time;

    printf("\nSRTF Gantt Chart:\n");
    for(int i = 0; i < g; i++)
        printf("| P%d ", gantt_pid[i]);
    printf("|\n");

    for(int i = 0; i <= g; i++)
        printf("%-4d", gantt_time[i]);
    printf("\n");

    return avg_wt / n;
}


float priority_np(int n, int at[], int bt[], int pr[])
{
    int done[MAX] = {0}, completed = 0, time = 0;
    int wt[MAX], tat[MAX], ct[MAX];
    int gantt_pid[MAX], gantt_time[MAX+1], g = 0;
    float avg_wt = 0;

    while(completed < n)
    {
        int maxp = INT_MIN, idx = -1;

        for(int i = 0; i < n; i++)
            if(at[i] <= time && !done[i] && pr[i] > maxp)
            {
                maxp = pr[i];
                idx = i;
            }

        if(idx == -1)
        {
            time++;
            continue;
        }

        gantt_pid[g] = idx + 1;
        gantt_time[g++] = time;

        time += bt[idx];
        ct[idx] = time;
        tat[idx] = ct[idx] - at[idx];
        wt[idx] = tat[idx] - bt[idx];
        avg_wt += wt[idx];

        done[idx] = 1;
        completed++;
    }
    gantt_time[g] = time;

    printf("\nPriority (Non-Preemptive) Gantt Chart:\n");
    for(int i = 0; i < g; i++)
        printf("| P%d ", gantt_pid[i]);
    printf("|\n");

    for(int i = 0; i <= g; i++)
        printf("%-4d", gantt_time[i]);
    printf("\n");

    return avg_wt / n;
}


float round_robin(int n, int at[], int bt[])
{
    int rt[MAX], visited[MAX] = {0};
    int rq[50], front = 0, rear = 0;
    int time = 0, completed = 0;
    int wt[MAX], tat[MAX], ct[MAX];
    int gantt_pid[50], gantt_time[50], g = 0;
    float avg_wt = 0;
    int tq = 3;

    for(int i = 0; i < n; i++)
        rt[i] = bt[i];

    while(completed < n)
    {
        for(int i = 0; i < n; i++)
            if(at[i] <= time && !visited[i])
            {
                rq[rear++] = i;
                visited[i] = 1;
            }

        if(front == rear)
        {
            time++;
            continue;
        }

        int idx = rq[front++];

        gantt_pid[g] = idx + 1;
        gantt_time[g++] = time;

        if(rt[idx] > tq)
        {
            rt[idx] -= tq;
            time += tq;
        }
        else
        {
            time += rt[idx];
            rt[idx] = 0;
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            avg_wt += wt[idx];
            completed++;
        }

        for(int i = 0; i < n; i++)
            if(at[i] <= time && !visited[i])
            {
                rq[rear++] = i;
                visited[i] = 1;
            }

        if(rt[idx] > 0)
            rq[rear++] = idx;
    }
    gantt_time[g] = time;

    printf("\nRound Robin (Q=3) Gantt Chart:\n");
    for(int i = 0; i < g; i++)
        printf("| P%d ", gantt_pid[i]);
    printf("|\n");

    for(int i = 0; i <= g; i++)
        printf("%-4d", gantt_time[i]);
    printf("\n");

    return avg_wt / n;
}


int main()
{
    int n, at[MAX], bt[MAX], pr[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
    {
        printf("P%d AT BT PR: ", i+1);
        scanf("%d %d %d", &at[i], &bt[i], &pr[i]);
    }

    printf("\nAverage Waiting Times:\n");

    float fcfs_wt = fcfs(n, at, bt);
    printf("FCFS              = %.2f\n", fcfs_wt);

    float srtf_wt = srtf(n, at, bt);
    printf("SRTF              = %.2f\n", srtf_wt);

    float pr_wt = priority_np(n, at, bt, pr);
    printf("Priority (Non-P)  = %.2f\n", pr_wt);

    float rr_wt = round_robin(n, at, bt);
    printf("Round Robin (Q=3) = %.2f\n", rr_wt);

    float min = fcfs_wt;
    char best[20] = "FCFS";

    if(srtf_wt < min) { min = srtf_wt; sprintf(best, "SRTF"); }
    if(pr_wt < min)   { min = pr_wt; sprintf(best, "Priority"); }
    if(rr_wt < min)   { min = rr_wt; sprintf(best, "Round Robin"); }

    printf("\nBest Algorithm (Min Avg WT): %s\n", best);

    return 0;
}