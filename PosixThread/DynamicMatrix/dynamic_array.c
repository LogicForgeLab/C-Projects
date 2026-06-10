#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct Data
{
    int *arr;
    int range;
};

struct Data data;

int is_prime(int n)
{
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0)
            return 0;
    return 1;
}

void* generate_primes(void* arg)
{
    int n = *(int*)arg;

    int count = 0;

    for (int i = 2; i <= n; i++)
        if (is_prime(i)) count++;

    data.range = count;
    data.arr = malloc(count * sizeof(int));

    int j = 0;

    for (int i = 2; i <= n; i++)
        if (is_prime(i))
            data.arr[j++] = i;

    return NULL;
}

void* print_and_free(void *arg)
{
    pthread_t *th1 = (pthread_t*)arg;

    pthread_join(*th1, NULL);

    printf("Prime Numbers:\n");

    for (int i = 0; i < data.range; i++)
        printf("%d ", data.arr[i]);

    printf("\n");

    free(data.arr);

    return NULL;
}

int main()
{
    pthread_t th1, th2;
    int range;

    do
    {
        printf("Enter array range: ");
        scanf("%d", &range);
    } while (range < 2);

    pthread_create(&th1, NULL, generate_primes, &range);
    pthread_create(&th2, NULL, print_and_free, &th1);

    pthread_join(th2, NULL);

    return 0;
}