#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

struct Data {
    int* arr;
    int size;
};

void* max3_value(void* arg)
{
    struct Data *data = (struct Data*)arg;

    int max1 = INT_MIN;
    int max2 = INT_MIN;
    int max3 = INT_MIN;

    for (int i = 0; i < data->size; i++)
    {
        int x = data->arr[i];

        if (x > max1)
        {
            max3 = max2;
            max2 = max1; 
            max1 = data->arr[i];
        }
        else if (x > max2 && x != max1)
        {
            max3 = max2;
            max2 = x;
        }
        else if (x > max3 && x != max2 && x != max1)
        {
            max3 = x;
        }
    }

    if (max3 == INT_MIN)
    {
        printf("Third largest value does not exist\n");
        return NULL;
    }
    
    int *result = (int*)malloc(sizeof(int));
    *result = max3;

    return result;
}

int main()
{
    pthread_t th;
    struct Data data;

    do
    {
        printf("Enter array size\n");
        scanf("%d", &data.size);

    } while (data.size < 3);

    data.arr = (int*)malloc(data.size * sizeof(int));
    if (data.arr == NULL)
    {
        perror("Memory alocation failed");
        return 1;
    }

    for (int i = 0; i < data.size; i++)
    {
        printf("Enter array elem: %d -> ", i + 1);
        scanf("%d", &data.arr[i]);
    }
    
    
    pthread_create(&th, NULL, max3_value, &data);

    int *result;

    pthread_join(th, (void **)&result);

    if (result == NULL)
    {
        free(data.arr);
        return 0;
    }
    
    printf("Third largest value is %d\n", *result);

    free(data.arr);
    free(result);
    return 0;
}