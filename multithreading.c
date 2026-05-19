#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

double mean = 0.0;
double median = 0.0;
double stddev = 0.0;

int *numbers;
int count;

void *calc_mean(void *arg) {
    double sum = 0.0;

    for(int i = 0; i < count; i++)
        sum += numbers[i];

    mean = sum / count;

    pthread_exit(NULL);
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void *calc_median(void *arg) {
    qsort(numbers, count, sizeof(int), compare);

    if(count % 2 == 0)
        median = (numbers[count/2 - 1] + numbers[count/2]) / 2.0;
    else
        median = numbers[count/2];

    pthread_exit(NULL);
}

void *calc_stddev(void *arg) {
    double variance_sum = 0.0;

    for(int i = 0; i < count; i++)
        variance_sum += pow(numbers[i] - mean, 2);

    stddev = sqrt(variance_sum / count);

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {

    if(argc < 2) {
        printf("Usage: %s <list of integers>\n", argv[0]);
        exit(1);
    }

    count = argc - 1;

    numbers = malloc(count * sizeof(int));

    for(int i = 1; i < argc; i++)
        numbers[i - 1] = atoi(argv[i]);

    pthread_t t1, t2, t3;

    pthread_create(&t1, NULL, calc_mean, NULL);
    pthread_create(&t2, NULL, calc_median, NULL);

    pthread_join(t1, NULL);

    pthread_create(&t3, NULL, calc_stddev, NULL);

    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("\nResults:\n");
    printf("Mean = %.2f\n", mean);
    printf("Median = %.2f\n", median);
    printf("Standard Deviation = %.2f\n", stddev);

    free(numbers);

    return 0;
}