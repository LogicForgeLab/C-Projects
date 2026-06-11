#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

struct Data {
    int* arr;
    int size;
};

int type = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *even_index(void* arg)
{
    struct Data *data = (struct Data*)arg;

    for (int i = 0; i < data->size; i += 2)
    {
        pthread_mutex_lock(&mutex);

        while (type != 0)
        {
            pthread_cond_wait(&cond, &mutex);
        }
        printf("even index: %d\n", data->arr[i]);

        type = 1;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
    
    return NULL;
}

void *odd_index(void *arg)
{
    struct Data *data = (struct Data*)arg;

    for (int i = 1; i < data->size; i += 2)
    {
        pthread_mutex_lock(&mutex);

        while (type != 1)
        {
            pthread_cond_wait(&cond, &mutex);
        }
        printf("odd index: %d\n", data->arr[i]);

        type = 0;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
    
    return NULL;
}

int main ()
{
    struct Data data;
    pthread_t th1, th2;

    do
    {
        printf("Enter Array size\n");
        scanf("%d", &data.size);
    } while (data.size <= 0);
    
    data.arr = (int*)malloc(data.size * sizeof(int));
    if(data.arr == NULL)
    {
        perror("memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < data.size; i++)
    {
        printf("Enter ayyays elements %d -> ", i + 1);
        scanf("%d", &data.arr[i]);
    }
    
    pthread_create(&th1, NULL, even_index, &data);
    pthread_create(&th2, NULL, odd_index, &data);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    free(data.arr);
    return 0;
}