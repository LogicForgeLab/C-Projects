#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void* sendMessage(void *);
void* recvMessage(void *);

int main()
{
    int sock;
    struct sockaddr_in server_addr = {0};

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0)
    {
        perror("inet_pton");
        exit(1);
    }

    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("connect");
        exit(1);
    }

    pthread_t send_thread, recv_thread;

    pthread_create(&send_thread, NULL, sendMessage, &sock);
    pthread_create(&recv_thread, NULL, recvMessage, &sock);

    pthread_join(send_thread, NULL);
    pthread_join(recv_thread, NULL);

    close(sock);

    return 0;
}

void* sendMessage(void *arg)
{
    int sock = *(int *)arg;
    char buffer[BUFFER_SIZE];

    while (1)
    {
        fgets(buffer, BUFFER_SIZE, stdin);

        // remove newline
        buffer[strcspn(buffer, "\n")] = 0;

        if (send(sock, buffer, strlen(buffer), 0) < 0)
        {
            perror("send");
            break;
        }
    }

    return NULL;
}

void* recvMessage(void *arg)
{
    int sock = *(int *)arg;
    char buffer[BUFFER_SIZE];

    while (1)
    {
        int n = recv(sock, buffer, BUFFER_SIZE - 1, 0);

        if (n <= 0)
        {
            perror("recv");
            break;
        }

        buffer[n] = '\0';
        printf("%s\n", buffer);
    }

    return NULL;
}