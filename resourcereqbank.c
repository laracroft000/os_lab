#include <stdio.h>

#define MAX 10

int main() {
    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[MAX][MAX], max[MAX][MAX], need[MAX][MAX];
    int avail[MAX], work[MAX];
    int finish[MAX], safeSeq[MAX];

    printf("\nEnter Allocation Matrix:\n");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("\nEnter Maximum Matrix:\n");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("\nEnter Available Resources:\n");
    for(int i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    printf("\nNeed Matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }

    for(int i = 0; i < m; i++)
        work[i] = avail[i];

    for(int i = 0; i < n; i++)
        finish[i] = 0;

    int count = 0;

    while(count < n) {
        int found = 0;

        for(int i = 0; i < n; i++) {
            if(!finish[i]) {
                int j;

                for(j = 0; j < m; j++)
                    if(need[i][j] > work[j])
                        break;

                if(j == m) {
                    for(int k = 0; k < m; k++)
                        work[k] += alloc[i][k];

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(!found)
            break;
    }

    if(count == n) {
        printf("\nSystem is in SAFE state\nSafe Sequence: ");

        for(int i = 0; i < n; i++)
            printf("P%d ", safeSeq[i]);

        printf("\n");
    } else {
        printf("\nSystem is in UNSAFE state\n");
        return 0;
    }

    int reqProcess;
    int request[MAX];

    printf("\nEnter process number making request: ");
    scanf("%d", &reqProcess);

    printf("Enter request for each resource:\n");

    for(int i = 0; i < m; i++)
        scanf("%d", &request[i]);

    for(int i = 0; i < m; i++) {
        if(request[i] > need[reqProcess][i]) {
            printf("Error: Process exceeded maximum claim\n");
            return 0;
        }
    }

    for(int i = 0; i < m; i++) {
        if(request[i] > avail[i]) {
            printf("Resources not available. Process must wait\n");
            return 0;
        }
    }

    for(int i = 0; i < m; i++) {
        avail[i] -= request[i];
        alloc[reqProcess][i] += request[i];
        need[reqProcess][i] -= request[i];
    }

    printf("\nChecking for safe state after allocation...\n");

    for(int i = 0; i < m; i++)
        work[i] = avail[i];

    for(int i = 0; i < n; i++)
        finish[i] = 0;

    count = 0;

    while(count < n) {
        int found = 0;

        for(int i = 0; i < n; i++) {
            if(!finish[i]) {
                int j;

                for(j = 0; j < m; j++)
                    if(need[i][j] > work[j])
                        break;

                if(j == m) {
                    for(int k = 0; k < m; k++)
                        work[k] += alloc[i][k];

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(!found)
            break;
    }

    if(count == n) {
        printf("After allocation, system is SAFE\nNew Safe Sequence: ");

        for(int i = 0; i < n; i++)
            printf("P%d ", safeSeq[i]);

        printf("\n");
    } else {
        printf("After allocation, system becomes UNSAFE\n");
    }

    return 0;
}