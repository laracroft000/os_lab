#include <stdio.h>
#include <stdlib.h>

#define N 10

void sort(int a[], int n) {

    int temp;

    for(int i = 0; i < n - 1; i++) {

        for(int j = 0; j < n - i - 1; j++) {

            if(a[j] > a[j + 1]) {

                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

int main() {

    int req[N];
    int a[N];

    int head;
    int total = 0;
    int cur;

    printf("Enter Initial Head Position: ");
    scanf("%d", &head);

    printf("Enter Disk Requests:\n");

    for(int i = 0; i < N; i++) {

        scanf("%d", &req[i]);

        a[i] = req[i];
    }

    sort(a, N);

    cur = head;

    printf("\nLOOK Path:\n%d", head);

    for(int i = 0; i < N; i++) {

        if(a[i] >= head) {

            total += abs(cur - a[i]);

            cur = a[i];

            printf(" -> %d", cur);
        }
    }

    for(int i = N - 1; i >= 0; i--) {

        if(a[i] < head) {

            total += abs(cur - a[i]);

            cur = a[i];

            printf(" -> %d", cur);
        }
    }

    printf("\nTotal Head Movement = %d\n", total);

    return 0;
}