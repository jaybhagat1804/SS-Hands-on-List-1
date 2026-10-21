#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

void *handle_client(void *arg)
{
    int client_fd = *(int *)arg;
    free(arg);

    char buffer[1024];

    printf("Thread %lu handling client.\n",
           (unsigned long)pthread_self());

    ssize_t n = recv(client_fd, buffer,
                     sizeof(buffer) - 1, 0);

    if (n > 0)
    {
        buffer[n] = '\0';

        printf("Client message: %s\n", buffer);

        const char *reply = "Handled by pthread server";

        if (send(client_fd, reply, strlen(reply), 0) == -1)
            perror("send");
    }
    else if (n == -1)
    {
        perror("recv");
    }

    close(client_fd);

    return NULL;
}

int main()
{
    int server_fd, client_fd;
    struct sockaddr_in server, client;
    socklen_t len;

    // Create TCP socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd == -1)
    {
        perror("socket");
        return 1;
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR,
               &opt, sizeof(opt));

    // Configure server address
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    if (bind(server_fd, (struct sockaddr *)&server,
             sizeof(server)) == -1)
    {
        perror("bind");
        close(server_fd);
        return 1;
    }

    // Listen for clients
    if (listen(server_fd, 5) == -1)
    {
        perror("listen");
        close(server_fd);
        return 1;
    }

    printf("Concurrent server using pthread_create() started.\n");

    while (1)
    {
        len = sizeof(client);

        // Accept client connection
        client_fd = accept(server_fd,
                           (struct sockaddr *)&client, &len);

        if (client_fd == -1)
        {
            perror("accept");
            continue;
        }

        // Allocate memory for the client socket descriptor
        int *arg = malloc(sizeof(int));

        if (arg == NULL)
        {
            perror("malloc");
            close(client_fd);
            continue;
        }

        *arg = client_fd;

        pthread_t tid;

        // Create a new thread for the client
        int ret = pthread_create(&tid, NULL,
                                 handle_client, arg);

        if (ret != 0)
        {
            fprintf(stderr, "pthread_create: %s\n",
                    strerror(ret));

            close(client_fd);
            free(arg);
            continue;
        }

        // Allow the thread to clean up automatically
        pthread_detach(tid);
    }

    close(server_fd);
    return 0;
}
