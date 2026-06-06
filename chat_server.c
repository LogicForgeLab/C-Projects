#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 10

int clients[MAX_CLIENTS];
int client_count = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *handleClient(void *);
void broadcast(char *message, int sender);

int main ()
{   
    int server_fd, client_sock;
    struct sockaddr_in server_addr, client_addr; 
    socklen_t addrlen = sizeof(client_addr);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    int opt = 1;

    setsockopt(server_fd,
            SOL_SOCKET,
            SO_REUSEADDR,
            &opt,
            sizeof(opt));

    if(bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("bind");
        exit(1);
    }

    if (listen(server_fd, 5) < 0)
    {
        perror("listn");
        exit(1);
    }

    printf("server is waiting...");

    while (1)
    {
        client_sock = accept(server_fd, (struct sockaddr*)&client_addr, &addrlen);
        if(client_sock < 0){
            perror("connect");
            exit(1);
        }

        pthread_mutex_lock(&mutex);

        if (client_count < MAX_CLIENTS)
        {
            clients[client_count++] = client_sock;

            int *pclient = malloc(sizeof(int));
            *pclient = client_sock;

            pthread_t tid;
            pthread_create(&tid, NULL, handleClient, pclient);
            pthread_detach(tid);
        }
        
        pthread_mutex_unlock(&mutex);
    }
    
    close(server_fd);

    return 0;
}

void *handleClient(void *arg)
{
    int client_sock = *(int *)arg;

    char buffer[BUFFER_SIZE];

    while (1)
    {
        int n = recv(client_sock, buffer, BUFFER_SIZE - 1, 0);

        if (n <= 0)
        {
            break;
        }

        buffer[n] = '\0';
        
        broadcast(buffer, client_sock);
    }

    pthread_mutex_lock(&mutex);

    for (int i = 0; i < client_count; i++)
    {
        if (clients[i] == client_sock)
        {
            clients[i] = clients[client_count - 1];
            client_count--;
            break;
        }
    }

    pthread_mutex_unlock(&mutex);

    close(client_sock);

    free(arg);

    return NULL;
}

void broadcast(char* message, int sender)
{
    pthread_mutex_lock(&mutex);

    for (int i = 0; i < client_count; i++)
    {
        send(clients[i], message, strlen(message), 0);
    }

    pthread_mutex_unlock(&mutex);
}