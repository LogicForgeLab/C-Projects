
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
    char filname[BUFFER_SIZE];
    char buffer[BUFFER_SIZE];
    int bytes;

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
        perror("Connect failed");
        exit(1);   
    }

    printf("Enter fillname");
    fgets(filname, BUFFER_SIZE, stdin);
    filname[strcspn(filname, "\n")] = '\0';

    if(send(sock, filname, strlen(filname), 0) < 0)
    {
        perror("Send failed");
        exit(1);
    }

    printf("File connect\n");

    
    while ((bytes = recv(sock, buffer, BUFFER_SIZE - 1, 0)) > 0)
    {
        buffer[bytes] = '\0';
        printf("%s", buffer);
    }

    printf("\n");
    close(sock);
    return 0;
}