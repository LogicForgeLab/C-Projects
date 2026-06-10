#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREAD_COUNT 4

pthread_mutex_t mutex;
int global_sum = 0;

struct Data
{
    int *arr;
    int start;
    int end;
};

void* sum_part (void* arg)
{
    struct Data *data = (struct Data*)arg;

    int local_sum = 0;

    for (int i = data->start; i < data->end; i++)
    {
        local_sum += data->arr[i];
    }
    
    pthread_mutex_lock(&mutex);
    global_sum += local_sum;
    pthread_mutex_unlock(&mutex);
    
    return NULL;

}

int main()
{   
    pthread_t thread[THREAD_COUNT];

    struct Data data[THREAD_COUNT];
    int size;

    do
    {
        printf("Enter Array size\n");
        scanf("%d", &size);
    } while (size < THREAD_COUNT);
    
    int *arr = (int*)malloc(size * sizeof(int));

    printf("Enter array elements\n");
    for (int i = 0; i < size; i++)
    {
        printf("Enter array elem %d -> ", i + 1);
        scanf("%d", &arr[i]);
    }
    
    pthread_mutex_init(&mutex, NULL);

    int part_size = size / THREAD_COUNT;

    for (int i = 0; i < THREAD_COUNT; i++)
    {
        data[i].arr = arr;
        data[i].start = i * part_size;

        if (i == THREAD_COUNT - 1)
        {
            data[i].end = size;
        }else{
            data[i].end = (i + 1) * part_size;
        }
         
        pthread_create(&thread[i], NULL, sum_part, &data[i]);
    }
    
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        pthread_join(thread[i], NULL);
    }
    
    printf("Total sum = %d\n", global_sum);

    pthread_mutex_destroy(&mutex);
    free(arr);

    return 0;
}