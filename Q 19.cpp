#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

// Shared data
int shared_variable = 0;

// Mutex lock
pthread_mutex_t mutex_lock;

// Function executed by each thread
void *thread_function(void *arg) {
    int thread_id = *((int *)arg);

    // Lock the mutex before accessing the shared variable
    pthread_mutex_lock(&mutex_lock);

    // Access and modify the shared variable
    shared_variable++;
    printf("Thread %d: Shared variable = %d\n", thread_id, shared_variable);

    // Unlock the mutex
    pthread_mutex_unlock(&mutex_lock);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];
    int i;

    // Initialize mutex lock
    if (pthread_mutex_init(&mutex_lock, NULL) != 0) {
        printf("Mutex initialization failed\n");
        return 1;
    }

    // Create threads
    for (i = 0; i < NUM_THREADS; i++) {
        thread_args[i] = i;
        if (pthread_create(&threads[i], NULL, thread_function, (void *)&thread_args[i]) != 0) {
            printf("Thread creation failed\n");
            return 1;
        }
    }

    // Join threads
    for (i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            printf("Thread join failed\n");
            return 1;
        }
    }

    // Destroy mutex lock
    pthread_mutex_destroy(&mutex_lock);

    return 0;
}

