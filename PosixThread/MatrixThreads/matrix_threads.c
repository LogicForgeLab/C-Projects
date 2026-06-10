#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int **mtx;
    int size;
} Matrix;

Matrix* createMatrix(int n)
{
    Matrix *m = (Matrix*)malloc(sizeof(Matrix));
    m->size = n;

    m->mtx = (int**)malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++)
    {
        m->mtx[i] = (int*)malloc(n * sizeof(int));
    }

    return m;
}

void fillMatrix(Matrix *m)
{
    for (int i = 0; i < m->size; i++)
    {
        for (int j = 0; j < m->size; j++)
        {
            printf("Enter [%d][%d]: ", i + 1, j + 1);
            scanf("%d", &m->mtx[i][j]);
        }
    }
}

typedef struct {
    Matrix *m;
} ThreadData;

void* find_max(void *arg)
{
    ThreadData *d = (ThreadData*)arg;

    int max = d->m->mtx[0][0];

    for (int i = 0; i < d->m->size; i++)
        for (int j = 0; j < d->m->size; j++)
            if (d->m->mtx[i][j] > max)
                max = d->m->mtx[i][j];

    printf("Max: %d\n", max);
    return NULL;
}

void* find_min(void *arg)
{
    ThreadData *d = (ThreadData*)arg;

    int min = d->m->mtx[0][0];

    for (int i = 0; i < d->m->size; i++)
        for (int j = 0; j < d->m->size; j++)
            if (d->m->mtx[i][j] < min)
                min = d->m->mtx[i][j];

    printf("Min: %d\n", min);
    return NULL;
}

void* print_diagonals(void *arg)
{
    ThreadData *d = (ThreadData*)arg;

    printf("Main diagonal: ");
    for (int i = 0; i < d->m->size; i++)
        printf("%d ", d->m->mtx[i][i]);

    printf("\nSecondary diagonal: ");
    for (int i = 0; i < d->m->size; i++)
        printf("%d ", d->m->mtx[i][d->m->size - i - 1]);

    printf("\n");

    return NULL;
}

void* calc_avg(void *arg)
{
    ThreadData *d = (ThreadData*)arg;

    int sum = 0;

    for (int i = 0; i < d->m->size; i++)
        for (int j = 0; j < d->m->size; j++)
            sum += d->m->mtx[i][j];

    printf("Average: %.2f\n",
           (double)sum / (d->m->size * d->m->size));

    return NULL;
}

void freeMatrix(Matrix *m)
{
    for (int i = 0; i < m->size; i++)
        free(m->mtx[i]);

    free(m->mtx);
    free(m);
}

int main()
{
    int n;

    do {
        printf("Enter matrix size: ");
        scanf("%d", &n);
    } while (n <= 0);

    Matrix *m = createMatrix(n);
    fillMatrix(m);

    ThreadData data = { m };

    pthread_t t1, t2, t3, t4;

    pthread_create(&t1, NULL, find_max, &data);
    pthread_create(&t2, NULL, find_min, &data);
    pthread_create(&t3, NULL, print_diagonals, &data);
    pthread_create(&t4, NULL, calc_avg, &data);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);

    freeMatrix(m);

    return 0;
}