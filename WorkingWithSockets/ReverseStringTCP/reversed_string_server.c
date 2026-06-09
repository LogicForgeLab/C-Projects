#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void reverseString(char* str);

int main()
{
    int client_sock, server_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Bind failed");
        exit(1);
    }
    if(listen(server_fd, 5) < 0)
    {
        perror("Listen failed");
        exit(1);
    }

    printf("Server is waiting...\n");

    while (1)
    {
        client_sock = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
        if (client_sock < 0)
        {
            perror("accept failed");
            exit(1);
        }

        memset(buffer, 0, BUFFER_SIZE);
        
        if(recv(client_sock, buffer, BUFFER_SIZE, 0) < 0)
        {
            perror("Listen failed");
            continue;
        }

        printf("Recevied: %s\n", buffer);   

        reverseString(buffer);

        if(send(client_sock, buffer, strlen(buffer), 0) < 0)
        {
            perror("Listen failed");
            continue;
        }

        close(client_sock);
    }
    
    return 0;
}

void reverseString(char* str)
{
    int len = strlen(str);

    if (str[len - 1] == '\n')
    {
        str[len - 1] = '\0';
        len--;
    }
    
    for (int i = 0; i < len / 2; i++)
    {
        int tmp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = tmp;
    }
}
