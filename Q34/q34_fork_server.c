#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <signal.h>

int main()
{
    int server_fd, client_fd;
    struct sockaddr_in server, client;
    socklen_t len;
    char buffer[1024];

    // Automatically reap terminated child processes
    signal(SIGCHLD, SIG_IGN);

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

    printf("Concurrent server using fork() started.\n");

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

        // Create a child process
        pid_t pid = fork();

        if (pid == -1)
        {
            perror("fork");
            close(client_fd);
            continue;
        }

        if (pid == 0)
        {
            // Child process handles the client
            close(server_fd);

            printf("Child process %d handling client.\n",
                   getpid());

            ssize_t n = recv(client_fd, buffer,
                             sizeof(buffer) - 1, 0);

            if (n > 0)
            {
                buffer[n] = '\0';

                printf("Client message: %s\n", buffer);

                const char *reply = "Handled by fork server";

                send(client_fd, reply, strlen(reply), 0);
            }

            close(client_fd);
            exit(0);
        }
        else
        {
            // Parent continues accepting clients
            close(client_fd);
        }
    }

    close(server_fd);
    return 0;
}
