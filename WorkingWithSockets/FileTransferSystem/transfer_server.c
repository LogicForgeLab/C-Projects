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
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_aadr;
    socklen_t addr_size;
    char fillname[BUFFER_SIZE];
    char buffer[BUFFER_SIZE];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        perror("Sock faled");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("bind faled");
        exit(1);
    }

    if (listen(server_fd, 5) < 0)
    {
        perror("listen faled");
        exit(1);
    }
    
    printf("server is waiting\n");

    while(1)
    {
        addr_size = sizeof(client_aadr);
        client_fd = accept(server_fd, (struct sockaddr*)&client_aadr, &addr_size);
        if (client_fd < 0)
        {
            perror("accept faled");
            exit(1);
        }

        memset(fillname, 0, BUFFER_SIZE);

        int bytes = recv(client_fd, fillname, BUFFER_SIZE - 1, 0);

        if (bytes <= 0)
        {
            close(client_fd);
            continue;
        }

        fillname[bytes] = '\0';

        FILE *fp = fopen(fillname, "r");

        if (fp == NULL)
        {
            strcpy(buffer, "File not found");
            send(client_fd, buffer, strlen(buffer), 0); 
        }else {
            while (fgets(buffer, BUFFER_SIZE, fp) != NULL)
            {
                send(client_fd, buffer, strlen(buffer), 0);
            }
            fclose(fp);
        }
        close(client_fd);
    }

    close(server_fd);
    return 0;
}