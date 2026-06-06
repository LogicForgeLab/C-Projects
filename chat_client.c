#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void* sendMessige(void *);
void* recvMessige(void *);

int main()
{
    int sock;
    struct sockaddr_in server_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("Socket");
        exit(1);
    }
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));

    pthread_t send_thread, recv_thread;

    pthread_create(&send_thread, NULL, sendMessige, &sock);
    pthread_create(&recv_thread, NULL, recvMessige, &sock);

    pthread_join(send_thread, NULL);
    pthread_join(recv_thread, NULL);

    close(sock);

    return 0;
}

void* sendMessige(void *arg)
{
    int sock = *(int *)arg;
    char buffer[BUFFER_SIZE];

    while (1)
    {
        fgets(buffer, BUFFER_SIZE, stdin);

        send(sock, buffer, strlen(buffer), 0);
    }
    
    return NULL;
}

void *recvMessige(void* arg)
{
    int sock = *(int*)arg;
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

        printf("%s", buffer);
    }
    
    return NULL;
}
