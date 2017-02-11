#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 524288

void *get_temporal_mean(void *params);  /* thread that computes mean values from the original array*/
void *get_global_mean(void *params);    /* thread that computes global mean from each sub mean*/

int array[SIZE] = {};

double globalMean = 0.0;                 /* final mean value for the whole array*/

int ca = 0;
int *num_threads;
double *temp_array = 0;
struct sub_array { int *array; int size; };

int main (int argc, const char * argv[])
{
    if (argc < 3) {
        printf("usage: %s filename num_threads", argv[0]);
        return 1;
    }

    FILE *file; file = fopen(argv[1], "r");

    if (file == 0) {
        printf("Error: Could not open file %s\n", argv[1]);
        return 1;
    }

    // define number of threads
    int number_of_threads = atoi(argv[2]);

    if (number_of_threads < 1) {
        printf("Error: thread count invalid\n");
        return 1;
    }

    num_threads = &number_of_threads;
    temp_array = malloc(sizeof(double)*number_of_threads);

    int num_nums = 0;
    while (fscanf(file, "%d", &array[num_nums]) == 1){ num_nums++; };

    int skipn = num_nums / number_of_threads;
    int lastn = num_nums % skipn;
    struct sub_array sub_arrays[number_of_threads];
    for(int i = 0; i < number_of_threads; i++) {
        sub_arrays[i].array = array+i*skipn;
        sub_arrays[i].size = (i == number_of_threads-1 && lastn) ? lastn : skipn;
    }

    pthread_t workers[number_of_threads];

    clock_t start = clock();

    for (int i = 0; i < number_of_threads; i++) {
        pthread_create(&workers[i], NULL, get_temporal_mean, &sub_arrays[i]);
    }

    /* now wait for the threads to finish */
    for (int i = 0; i < number_of_threads; i++) {
        pthread_join(workers[i], NULL);
    }

    pthread_t findMean;

    pthread_create(&findMean, NULL, get_global_mean, temp_array);

    // wait for the final mean computing thread to finish
    pthread_join(findMean, NULL);

    clock_t end = clock();
    double duration = (long double)(end-start)/CLOCKS_PER_SEC;

    for (int i = 0; i < number_of_threads; i++) {
        printf("Mean %2d: %.2f\n", i, temp_array[i]);
    }

    printf("Global Mean: %.2f\n", globalMean);

    printf("Took %g seconds", duration);

    return 0;
}

void *get_temporal_mean(void *params) {
    struct sub_array *sub_arr = params;
    long sum = 0;
    for (int i = 0; i < sub_arr->size; i++) {
        sum += sub_arr->array[i];
    }
    temp_array[ca++] = (double)sum/sub_arr->size;
}

void *get_global_mean(void *params) {
    for (int i = 0; i < *num_threads; i++) {
        globalMean += *((double*)params+i);
    }
    globalMean /= (*num_threads);
}
