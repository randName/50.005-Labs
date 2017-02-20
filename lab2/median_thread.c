#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define SIZE    524288
//#define NUMBER_OF_THREADS 128

void *sorter(void *params);   /* thread that performs sorting for subthread*/
void *merger(void *params);   /* thread that performs merging for final result */
void *find_median(void *params);  /* thread that computes median of the sorted array */

int array[SIZE] = {};

double median = 0.0;

int num_nums = 0;
int *num_threads;
struct sub_array { int *array; int size; };
int sorted_array[SIZE] = {};

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
    while (fscanf(file, "%d", &array[num_nums]) == 1){ num_nums++; };

    // define number of threads
    int number_of_threads = atoi(argv[2]);
    if (number_of_threads < 1) {
        printf("Error: thread count invalid\n");
        return 1;
    }

    num_threads = &number_of_threads;

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
        pthread_create(&workers[i], NULL, sorter, &sub_arrays[i]);
    }

    /* now wait for the threads to finish */
    for (int i = 0; i < number_of_threads; i++) {
        pthread_join(workers[i], NULL);
    }

    pthread_t merging_thread;

    pthread_create(&merging_thread, NULL, merger, sub_arrays);

    // wait for the merger thread to finish
    pthread_join(merging_thread, NULL);

    pthread_t median_thread;

    pthread_create(&median_thread, NULL, find_median, sorted_array);

    // wait for the median computing thread to finish
    pthread_join(median_thread, NULL);

    clock_t end = clock();
    double duration = (long double)(end-start)/CLOCKS_PER_SEC;

    // TODO: printout the final sorted array

    printf("Median: %.2f\n", median);

    printf("Took %g seconds", duration);

    return 0;
}

int cmpfunc (const void * a, const void * b)
{
   return *(int*)a - *(int*)b;
}

void *sorter(void *params) {
    struct sub_array *sub_arr = params;
    qsort(sub_arr->array, sub_arr->size, sizeof(int), cmpfunc);

    pthread_exit(NULL);
}

// You can use any merging algorithm
void *merger(void *params) {
    struct sub_array *arrs = params;
    int n, i, idx[*num_threads];
    int min = arrs->array[0], min_n = 0;

    for (n = 0; n < *num_threads; n++) { idx[n] = 0; }
    for (i = 0; i < SIZE; i++) {
        for (n = 0; n < *num_threads; n++) {
            if ( idx[n] < (arrs+n)->size && (arrs+n)->array[idx[n]] <= min )
            {
                min = (arrs+n)->array[idx[n]];
                min_n = n;
            }
        }
        sorted_array[i] = min;
        min = (arrs+min_n)->array[idx[min_n]+1];
        idx[min_n]++;
    }
    pthread_exit(NULL);
}

void *find_median(void *params) {
    int *arr = params;
    if (num_nums % 2) {
        median = arr[num_nums/2];
    } else {
        median = (arr[num_nums/2] + arr[num_nums/2+1])/2;
    }

    pthread_exit(NULL);
}
