#include <stdio.h>
#include <stdlib.h>

#define N 10

int main() {

    int req[N];
    int visited[N] = {0};

    int head;
    int total = 0;
    int cur;

    printf("Enter Initial Head Position: ");
    scanf("%d", &head);

    printf("Enter Disk Requests:\n");

    for(int i = 0; i < N; i++)
        scanf("%d", &req[i]);

    cur = head;

    printf("\nSSTF Path:\n%d", head);

    for(int k = 0; k < N; k++) {

        int min = 100000;
        int index = -1;

        for(int i = 0; i < N; i++) {

            if(!visited[i]) {

                int dist = abs(cur - req[i]);

                if(dist < min) {

                    min = dist;
                    index = i;
                }
            }
        }

        visited[index] = 1;

        total += min;

        cur = req[index];

        printf(" -> %d", cur);
    }

    printf("\nTotal Head Movement = %d\n", total);

    return 0;
}