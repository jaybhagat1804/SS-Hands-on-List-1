#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main()
{
    int sockfd;
    struct sockaddr_in server;
    char buffer[1024];

    // Create TCP socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1)
    {
        perror("socket");
        return 1;
    }

    // Configure server address
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);

    // Use server's IP address
    if (inet_pton(AF_INET, "10.0.2.15",
                  &server.sin_addr) != 1)
    {
        printf("Invalid IP address\n");
        close(sockfd);
        return 1;
    }

    // Connect to server
    if (connect(sockfd, (struct sockaddr *)&server,
                sizeof(server)) == -1)
    {
        perror("connect");
        close(sockfd);
        return 1;
    }

    printf("Connected to server.\n");

    // Send message
    const char *message = "Hello from client!";

    if (send(sockfd, message, strlen(message), 0) == -1)
    {
        perror("send");
        close(sockfd);
        return 1;
    }

    // Receive reply
    ssize_t n = recv(sockfd, buffer, sizeof(buffer) - 1, 0);

    if (n > 0)
    {
        buffer[n] = '\0';
        printf("Message from server: %s\n", buffer);
    }
    else if (n == -1)
    {
        perror("recv");
    }
    else
    {
        printf("Server closed the connection.\n");
    }

    close(sockfd);

    return 0;
}
