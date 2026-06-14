#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define DB_FILE "db.dat"
#define NAME_LEN 50

typedef struct
{
    char name[NAME_LEN];
} Product;

pthread_mutex_t db_mutex = PTHREAD_MUTEX_INITIALIZER;

void handle_post(char *name, int client)
{
    name[strcspn(name, "\n")] = '\0';

    pthread_mutex_lock(&db_mutex);

    FILE *f = fopen(DB_FILE, "ab");
    if (!f)
    {
        pthread_mutex_unlock(&db_mutex);
        send(client, "ERROR\n", 6, 0);
        return;
    }

    Product p = {0};
    strncpy(p.name, name, NAME_LEN - 1);

    fwrite(&p, sizeof(Product), 1, f);

    fclose(f);

    pthread_mutex_unlock(&db_mutex);

    send(client, "ADDED\n", 6, 0);
}

void handle_get(char *name, int client)
{
    name[strcspn(name, "\n")] = '\0';

    pthread_mutex_lock(&db_mutex);

    FILE *f = fopen(DB_FILE, "rb");

    if (!f)
    {
        pthread_mutex_unlock(&db_mutex);
        send(client, "NOT FOUND\n", 10, 0);
        return;
    }

    Product p;
    int found = 0;

    while (fread(&p, sizeof(Product), 1, f))
    {
        if (strcmp(p.name, name) == 0)
        {
            send(client, p.name, strlen(p.name), 0);
            send(client, "\n", 1, 0);
            found = 1;
            break;
        }
    }

    fclose(f);

    pthread_mutex_unlock(&db_mutex);

    if (!found)
        send(client, "NOT FOUND\n", 10, 0);
}

void handle_get_all(int client)
{
    pthread_mutex_lock(&db_mutex);

    FILE *f = fopen(DB_FILE, "rb");

    if (!f)
    {
        pthread_mutex_unlock(&db_mutex);
        send(client, "EMPTY\n", 6, 0);
        return;
    }

    Product p;
    char response[4096] = {0};

    while (fread(&p, sizeof(Product), 1, f))
    {
        strcat(response, p.name);
        strcat(response, "\n");
    }

    fclose(f);

    pthread_mutex_unlock(&db_mutex);

    if (strlen(response) == 0)
        strcpy(response, "EMPTY\n");

    send(client, response, strlen(response), 0);
}

void *client_handler(void *arg)
{
    int client = *(int *)arg;
    free(arg);

    char buffer[1024];

    int n = recv(client, buffer, sizeof(buffer) - 1, 0);

    if (n <= 0)
    {
        close(client);
        return NULL;
    }

    buffer[n] = '\0';

    if (strncmp(buffer, "POST ", 5) == 0)
    {
        handle_post(buffer + 5, client);
    }
    else if (strncmp(buffer, "GET ", 4) == 0)
    {
        handle_get(buffer + 4, client);
    }
    else if (strcmp(buffer, "GET\n") == 0 ||
             strcmp(buffer, "GET") == 0)
    {
        handle_get_all(client);
    }
    else
    {
        send(client, "INVALID COMMAND\n", 16, 0);
    }

    close(client);

    return NULL;
}

int main()
{
    FILE *db = fopen(DB_FILE, "ab");
    if (db)
        fclose(db);

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd < 0)
    {
        perror("socket");
        return 1;
    }

    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd,
             (struct sockaddr *)&server_addr,
             sizeof(server_addr)) < 0)
    {
        perror("bind");
        return 1;
    }

    if (listen(server_fd, 10) < 0)
    {
        perror("listen");
        return 1;
    }

    printf("Server listening on port %d...\n", PORT);

    while (1)
    {
        struct sockaddr_in client_addr;
        socklen_t len = sizeof(client_addr);

        int client = accept(
            server_fd,
            (struct sockaddr *)&client_addr,
            &len);

        if (client < 0)
        {
            perror("accept");
            continue;
        }

        int *pclient = malloc(sizeof(int));
        *pclient = client;

        pthread_t tid;

        pthread_create(
            &tid,
            NULL,
            client_handler,
            pclient);

        pthread_detach(tid);
    }

    close(server_fd);

    return 0;
}