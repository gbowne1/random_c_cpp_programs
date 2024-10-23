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
#include <arpa/inet.h>

#define BUFFER_SIZE 1024
#define PORT 79

void error(const char *msg) {
    perror(msg);
    fprintf(stderr, "Error: %s\n", msg);
    exit(EXIT_FAILURE);
}

int sockfd = -1;
char buffer[BUFFER_SIZE];

int main(int argc, char *argv[]) {
    struct addrinfo hints, *res, *p;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s hostname\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Initialize hints
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int gai_status = getaddrinfo(argv[1], NULL, &hints, &res);
    if (gai_status != 0) {
        fprintf(stderr, "Error: getaddrinfo failed: %s\n", gai_strerror(gai_status));
        freeaddrinfo(res);
        exit(EXIT_FAILURE);
    }

    // Iterate through the linked list of addresses
    for (p = res; p != NULL; p = p->ai_next) {
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (sockfd < 0) {
            perror("Error creating socket");
            continue; // try the next address
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == 0) {
            break; // Success
        }

        close(sockfd); // Clean up on failure
    }

    if (p == NULL) {
        fprintf(stderr, "Error: Unable to connect to host: %s\n", argv[1]);
        freeaddrinfo(res);
        exit(EXIT_FAILURE);
    }

    // Query input
    printf("Please enter the username to query: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        error("Error reading input");
    }
    size_t len = strcspn(buffer, "\n");
    if (len == BUFFER_SIZE - 1 && buffer[len] != '\n') {
        fprintf(stderr, "Error: Username too long\n");
        close(sockfd);
        freeaddrinfo(res);
        exit(EXIT_FAILURE);
    }
    buffer[len] = '\0'; // Remove trailing newline

    // Send query to server
    if (send(sockfd, buffer, strlen(buffer), 0) < 0) {
        error("Error sending to socket");
    }

    // Receive response
    memset(buffer, 0, BUFFER_SIZE);
    int n = recv(sockfd, buffer, BUFFER_SIZE - 1, 0);
    if (n < 0) {
        error("Error receiving from socket");
    }
    buffer[n] = '\0'; // Ensure null-termination

    // Print the response
    printf("%s\n", buffer);

    freeaddrinfo(res);
    close(sockfd);
    return EXIT_SUCCESS;
}
