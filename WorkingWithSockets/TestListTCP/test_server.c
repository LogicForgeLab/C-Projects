#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define TEST_COUNT 5
#define MAX_QUESTION 100

typedef struct {
    char question[256];
    char a[64], b[64], c[64], d[64];
    int correct;
} Test;

Test test[MAX_QUESTION];
int test_count = 0;

void load_question()
{
    FILE* fp = fopen("question.txt", "r");
    if(!fp)
    {
        perror("file error");
        exit(1);
    }

    while(test_count < MAX_QUESTION &&
        fscanf(fp,
        "%255[^|]|%63[^|]|%63[^|]|%63[^|]|%63[^|]|%d\n",
        test[test_count].question,
        test[test_count].a,
        test[test_count].b,
        test[test_count].c,
        test[test_count].d,
        &test[test_count].correct) == 6)
    {
        test_count++;
    }

    fclose(fp);
}

void format_question(char* buffer, Test t)
{
    sprintf(buffer,
        "%s\n1)%s\n2)%s\n3)%s\n4)%s\n",
        t.question, t.a, t.b, t.c, t.d);
}

void* handle_client(void *arg)
{
    int client = *(int *)arg;
    free(arg);

    int score = 0;
    int used[MAX_QUESTION] = {0};

    srand(time(NULL) ^ client);

    for (int i = 0; i < TEST_COUNT; i++)
    {
        int idx;

        do {
            idx = rand() % test_count;
        } while (used[idx]);

        used[idx] = 1;

        char buffer[512];
        format_question(buffer, test[idx]);

        send(client, buffer, strlen(buffer), 0);

        int answer = 0;
        recv(client, &answer, sizeof(answer), 0);

        if (answer == test[idx].correct)
            score++;
    }

    char result[128];
    sprintf(result, "Test finished! Score: %d/%d\n", score, TEST_COUNT);

    send(client, result, strlen(result), 0);
    close(client);

    printf("Client finished: %d/%d\n", score, TEST_COUNT);

    return NULL;
}

int main()
{
    int server_fd, *new_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;

    load_question();

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_fd, 5);

    printf("Server running...\n");

    while (1)
    {
        addr_size = sizeof(client_addr);
        new_sock = malloc(sizeof(int));

        *new_sock = accept(server_fd,
                           (struct sockaddr*)&client_addr,
                           &addr_size);

        printf("Client connected\n");

        pthread_t th;
        pthread_create(&th, NULL, handle_client, new_sock);
        pthread_detach(th);
    }
}