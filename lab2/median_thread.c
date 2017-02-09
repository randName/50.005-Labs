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

int main (int argc, const char * argv[])
{
    // TODO: read data from external file and store it in an array
    // Note: you should pass the file as a first command line argument at runtime.

    // define number of threads
    int number_of_threads = atoi(argv[2]);

    // TODO: partition the array list into N sub-arrays, where N is the number of threads


    // TODO: create a list of threads using pthread_t that sorts sub-arrays.  E.g.,
    pthread_t workers[number_of_threads];

    // TODO: start recording time

    // TODO: start threads by passing the sub-array they need to sort and the function they execute
    for (int i = 0; i < number_of_threads; i++) {
        pthread_create(&workers[i], NULL, sorter, sub-array[i]);
    }

    /* now wait for the threads to finish */
    for (int i = 0; i < number_of_threads; i++) {
        pthread_join(workers[i], NULL);
    }

    // TODO: establish the merger thread
    pthread_t merging_thread;

    pthread_create(&merging_thread, NULL, merger, data1);

    // wait for the final mean computing thread to finish
    pthread_join(merging_thread, NULL);

    // TODO: establish the median computing thread
    pthread_t median_thread;

    pthread_create(&median_thread, NULL, find_median, data2);

    // wait for the median computing thread to finish
    pthread_join(merging_thread, NULL);


    // TODO: stop recording time and compute the elapsed time

    // TODO: printout the final sorted array

    // TODO: printout median

    return 0;
}


// You can use any sorting algorithm
void *sorter(void *params) {

    pthread_exit(NULL);
}

// You can use any merging algorithm
void *merger(void *params) {

    pthread_exit(NULL);
}

void *find_median(void *params) {

    pthread_exit(NULL);
}
