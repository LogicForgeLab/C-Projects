#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define BUFFER_SIZE 1024

typedef struct 
{
    int client_fd;
    int secret;
} client_data;

void* handleClient(void *arg)
{
    client_data *data = (client_data*)arg;
    int client_fd = data->client_fd;
    int secret = data->secret;

    free(data);

    char buffer[BUFFER_SIZE];

    printf("New Client conected. Secret = %d\n", secret);

    while (1)
    {
        int n = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
        if (n <= 0)
        {
            printf("client disconected\n");
            break;
        }
        buffer[n] = '\0';

        int guess = atoi(buffer);

        if (guess > secret)
        {
            send(client_fd, "Too high", strlen("Too high"), 0);
        }
        else if (guess < secret)
        {
            send(client_fd, "Too low", strlen("Too low"), 0);
        }else if (guess == secret)
        {
            send(client_fd, "Sucess", strlen("Sucess"), 0);
            break;
        }
    }
    close(client_fd);
    return NULL;    
}


int main ()
{
    srand(time(NULL));
    int server_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;

    int x = rand() % 100 + 1;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        perror("Sock failed");
        exit(1);
    }
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Bind failed");
        exit(1);
    }

    if(listen(server_fd, 5) < 0)
    {
        perror("Listen failed");
        exit(1);
    }

    printf("server is waiting....\n");

    while(1)
    {
        int *client_fd = malloc(sizeof(int));
        addr_size = sizeof(client_addr);

        *client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_size);
        if (*client_fd < 0)
        {
            perror("Accept failed");
            free(client_fd);
            continue;
        }

        client_data *data = malloc(sizeof(client_data));
        data->client_fd = *client_fd;

        data->secret = rand() % 100 + 1;

        free(client_fd);

        pthread_t th;

        pthread_create(&th, NULL, handleClient, data);
        pthread_detach(th);
    }

    close(server_fd);
    return 0;
}