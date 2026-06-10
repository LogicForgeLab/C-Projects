#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define THREAD_COUNT 10

int glob = 0;
pthread_mutex_t mutex;

void *add_hunter(void *arg)
{
    pthread_mutex_lock(&mutex);

    glob += 100;

    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main()
{
    pthread_t thread[THREAD_COUNT];
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < THREAD_COUNT; i++)
    {
        pthread_create(&thread[i], NULL, add_hunter, NULL);
    }
    
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        pthread_join(thread[i], NULL);
    }
    
    printf("Final Value: %d\n", glob);

    return 0;
}