#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

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
    
    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    if(connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Connect failed");
        exit(1);
    }

    printf("Enter string\n");
    fgets(buffer, BUFFER_SIZE, stdin);

    if (send(sock, buffer, BUFFER_SIZE, 0) < 0)
    {
        perror("Listen failed");
        exit(1);
    }

    memset(buffer, 0, BUFFER_SIZE);
    if(recv(sock, buffer, BUFFER_SIZE, 0) < 0)
    {
        perror("Listen failed");
        exit(1);
    }
    
    printf("Reversed String: %s\n", buffer);

    close(sock);
    return 0;
}