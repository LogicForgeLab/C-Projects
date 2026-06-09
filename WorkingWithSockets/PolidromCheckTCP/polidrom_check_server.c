#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int isPolidrom(char *str)
{
    int left = 0;
    int right = strlen(str) - 1;

    while (left < right)
    {
        if (str[left] != str[right])
        {
            return 0;
        }
        else{
            left++;
            right--;
        }
    }
    
    return 1;
}

void* handleClient(void* arg)
{
    int client_fd = *(int *)arg;
    free(arg);

    char buffer[BUFFER_SIZE];
    char response[50];

    int n = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);

    if (n <= 0)
    {
        close(client_fd);
        return NULL;
    }
    
    buffer[n] = '\0';
    buffer[strcspn(buffer, "\n")] = '\0';

    if (isPolidrom(buffer))
    {
        strcpy(response, "Polidrome");
    }else{
        strcpy(response, "Not polidrome");
    }
    
    if(send(client_fd, response, strlen(response), 0) < 0)
    {
        perror("Send failed");
        exit(1);
    }

    close(client_fd);
    return NULL;
}

int main()
{
    int server_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        perror("Sock failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("bind failed");
        exit(1);
    }
    
    if (listen(server_fd, 5) < 0)
    {
        perror("listen failed");
        exit(1);
    }

    printf("Server is waiting\n");

    while (1)
    {
        int *client_fd = malloc(sizeof(int));
        if (client_fd == NULL)
        {
            perror("memory alocation failed");
            exit(1);
        }
        
        addr_size = sizeof(client_addr);
        
        *client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_size);

        pthread_t th;

        pthread_create(&th, NULL, handleClient, client_fd);

        pthread_detach(th);
    }
    
    close(server_fd);
    return 0;
}