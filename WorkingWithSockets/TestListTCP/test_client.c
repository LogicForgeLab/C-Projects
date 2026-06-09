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
    int answer;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));

    while(1)
    {
        memset(buffer, 0, BUFFER_SIZE);

        int bytes = recv(sock, buffer, BUFFER_SIZE, 0);
        if(bytes <= 0) break;

        printf("\n%s\n", buffer);

        if(strstr(buffer, "Score"))
            break;

        printf("Your answer (1-4): ");
        scanf("%d", &answer);

        send(sock, &answer, sizeof(answer), 0);
    }

    close(sock);
    return 0;
}