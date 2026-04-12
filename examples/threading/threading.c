#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{

    // TODO: wait, obtain mutex, wait, release mutex as described by thread_data structure
    // hint: use a cast like the one below to obtain thread arguments from your parameter
    //struct thread_data* thread_func_args = (struct thread_data *) thread_param;
    struct thread_data* threadData = (struct thread_data *) thread_param;
    threadData->thread_complete_success = false;
    usleep(threadData->waitTime * 1000);

    int result = pthread_mutex_lock(threadData->mutex);
    if (result != 0) {
        ERROR_LOG("Failed to obtain mutex, error: %d", result);
        return thread_param;
    }

    usleep(threadData->holdTime * 1000);

    result = pthread_mutex_unlock(threadData->mutex);
    if (result != 0) {
        ERROR_LOG("Failed to unlock mutex, error: %d", result);
    }
    
    threadData->thread_complete_success = true;

    return thread_param;
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
    /**
     * TODO: allocate memory for thread_data, setup mutex and wait arguments, pass thread_data to created thread
     * using threadfunc() as entry point.
     *
     * return true if successful.
     *
     * See implementation details in threading.h file comment block
     */

    struct thread_data *threadData = (struct thread_data *) malloc(sizeof(struct thread_data));
    if (threadData == NULL) {
        ERROR_LOG("Failed to allocate memory for threadData");
        return false;
    }

    threadData->mutex   = mutex;
    threadData->waitTime = wait_to_obtain_ms;
    threadData->holdTime = wait_to_release_ms;
    threadData->thread_complete_success = false;

    int result = pthread_create(thread, NULL, threadfunc, threadData);
    
    if (result != 0) {
        ERROR_LOG("Failed to create thread, error: %d", result);
        free(threadData);
        return false;
    }

    return true;
}

