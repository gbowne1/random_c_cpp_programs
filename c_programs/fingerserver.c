// File:   fingerserver.c
// Author: Gregory K. Bowne
// Date:   9 SEPT 2020
// Time:   9:22:45
// Brief:  This program makes a finger server that runs on Port 79 and announces its details.

#ifdef _WIN32
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <io.h>
#include <fcntl.h>
#endif

#ifdef __linux__
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <signal.h>
#include <fcntl.h>
#include <netinet/tcp.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/wait.h>
#include <sys/un.h>
#endif

#ifdef __APPLE__
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/un.h>
#endif

#ifdef _POSIX_C_SOURCE
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/wait.h>
#include <sys/un.h>
#include <sys/param.h>
#include <sys/mman.h>
#endif

// Common Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#include <complex.h>
#include <assert.h>
#include <time.h>


#define BUFFER_SIZE 1024
#define PORT 79

void error(const char *msg) {
    perror(msg);
    fprintf(stderr, "Error: %s\n", msg);
    exit(EXIT_FAILURE);
}

char *generate_response(const char *input, struct sockaddr_in serv_addr) {
    size_t input_len = strlen(input);
    size_t response_len = input_len + 50; // Adjust size as needed
    char *response = (char *)malloc(response_len);
    if (response == NULL) {
        error("ERROR allocating memory for response");
    }
    snprintf(response, response_len, "Received input: %s\nServer details:\nPort: %d\nIP Address: %s\n", input, PORT, inet_ntoa(serv_addr.sin_addr));
    return response;
}

int main(int argc, char *argv[]) {
    int sockfd, newsockfd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
    }

    // Zero out the server address structure
    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);

    // Bind the socket to the address and port
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in)) < 0) {
        close(sockfd);
        error("ERROR on binding");
    }

    // Listen for incoming connections
    if (listen(sockfd, 5) < 0) {
        close(sockfd);
        error("ERROR on listen");
    }
    clilen = sizeof(cli_addr);

    printf("Finger server listening on port %d...\n", PORT);

    // Accept a connection
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0) {
        close(sockfd);
        error("ERROR on accept");
    }

    // Read data from the client
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    int n = read(newsockfd, buffer, BUFFER_SIZE - 1);
    if (n < 0) {
        close(newsockfd);
        close(sockfd);
        error("ERROR reading from socket");
    }
    buffer[n] = '\0';

    // Generate a response
    char *response = generate_response(buffer, serv_addr);

    // Send the response back to the client
    if (write(newsockfd, response, strlen(response)) < 0) {
        free(response);
        close(newsockfd);
        close(sockfd);
        error("ERROR writing to socket");
    }

    // Clean up
    free(response);
    close(newsockfd);
    close(sockfd);

    return EXIT_SUCCESS;
}
