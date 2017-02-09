#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 524288

void *get_temporal_mean(void *params);  /* thread that computes mean values from the original array*/
void *get_global_mean(void *params);    /* thread that computes global mean from each sub mean*/

int array[SIZE] = {};

double globalMean = 0.0;                 /* final mean value for the whole array*/

int main (int argc, const char * argv[])
{
    // TODO: read data from external file and store it in an array
    // Note: you should pass the file as a first command line argument at runtime.

    // define number of threads
    int number_of_threads = atoi(argv[2]);

    // TODO: partition the array list into N sub-arrays, where N is the number of threads

    // TODO: create a list of threads using pthread_t that computes temporal means. E.g.,
    pthread_t workers[number_of_threads];

    // TODO: start recording time

    // TODO: start threads by passing the sub-array they need to process and the function they execute
    for (int i = 0; i < number_of_threads; i++) {
        pthread_create(&workers[i], NULL, get_temporal_mean, sub-array[i]);
    }

    /* now wait for the threads to finish */
    for (int i = 0; i < number_of_threads; i++) {
        pthread_join(workers[i], NULL);
    }

    // TODO: printout temporal mean values computed by each thread

    // TODO: establish the final mean computing thread
    pthread_t findMean;

    pthread_create(&findMean, NULL, get_global_mean, data1);

    // wait for the final mean computing thread to finish
    pthread_join(findMean, NULL);

    // TODO: stop recording time and compute the elapsed time

    // TODO: printout the global mean value

    // TODO: printout the execution time

    return 0;
}

//TODO: get temporal mean values of the sub arrays
void *get_temporal_mean(void *params) {
    // TODO: compute temporal mean values for each sub array of the original array with N threads

    // TODO: store the temporal mean values to another array, e.g., temp_array[]
}

//TODO: get global mean value
void *get_global_mean(void *params) {
    //TODO: compute the global mean from the temp_array[]
}
