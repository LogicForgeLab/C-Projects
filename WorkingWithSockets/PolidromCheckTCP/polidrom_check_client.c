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

    if(connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("connect failed");
        exit(1);
    }

    printf("Enter String:  ");
    fgets(buffer, BUFFER_SIZE, stdin);

    if(send(sock, buffer, strlen(buffer), 0) < 0)
    {
        perror("Send failed");
        exit(1);
    }

    int n = recv(sock, buffer, BUFFER_SIZE - 1, 0);
    if (n < 0)
    {
        perror("recv failed");
        exit(1);
    }

    if (n > 0)
    {
        buffer[n] = '\0';
        printf("server response %s\n", buffer);
    }
    
    close(sock);
    return 0;
}