#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("Sock failed");
        exit(1);
    }
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Connect failed");
        exit(1);
    }
    
    printf("Connect to server.\n");

    while (1)
    {
        printf("Enter Message:  ");
        fgets(buffer, BUFFER_SIZE, stdin);

        send(sock, buffer, strlen(buffer), 0);

        int n = recv(sock, buffer, BUFFER_SIZE - 1, 0);
        if (n < 0)
        {
            perror("Server Disconected");
            break;
        }
        
        buffer[n] = '\0';
        printf("Server: %s\n", buffer);
    }
    
    close(sock);
    return 0;
}