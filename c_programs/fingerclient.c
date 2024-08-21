// File:   fingerclient.c
// Author: Gregory K. Bowne
// Date:   9 SEPT 2020
// Time:   11:19:49
// Brief:  This program makes a finger client that connects to the finger server.  ./fingerclient <hostname>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define BUFFER_SIZE 1024
#define PORT 79

void error(const char *msg) {
    perror(msg);
    fprintf(stderr, "Error: %s\n", msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    int sockfd;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[BUFFER_SIZE];

    if (argc < 2) {
        fprintf(stderr, "Usage: %s hostname\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("Error opening socket");
    }

    // Get server information
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr, "Error: No such host\n");
        exit(EXIT_FAILURE);
    }

    // Clear and set up server address structure
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
    serv_addr.sin_port = htons(PORT);

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        error("Error connecting");
    }

    // Get the username to query
    printf("Please enter the username to query: ");
    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
        error("Error reading input");
    }
    buffer[strcspn(buffer, "\n")] = '\0'; // Remove trailing newline

    // Send the query to the server
    if (send(sockfd, buffer, strlen(buffer), 0) < 0) {
        error("Error sending to socket");
    }

    // Clear the buffer and receive the response
    memset(buffer, 0, BUFFER_SIZE);
    int n = recv(sockfd, buffer, BUFFER_SIZE - 1, 0);
    if (n < 0) {
        error("Error receiving from socket");
    }
    buffer[n] = '\0';

    // Print the server's response
    printf("%s\n", buffer);

    // Close the socket
    close(sockfd);

    return EXIT_SUCCESS;
}
