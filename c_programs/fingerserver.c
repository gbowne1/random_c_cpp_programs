// File:   fingerserver.c
// Author: Gregory K. Bowne
// Date:   9 SEPT 2020
// Time:   9:22:45
// Brief:  This program implements a finger server on port 79.

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <io.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define PORT 79

void error(const char *msg) {
    perror(msg);
    fprintf(stderr, "Error: %s\n", msg);
    exit(EXIT_FAILURE);
}

char *generate_response(const char *input, struct sockaddr_in serv_addr) {
    size_t input_len = strlen(input);
    size_t response_len = input_len + 100;
    char *response = (char *)malloc(response_len);
    if (!response) {
        error("ERROR allocating memory for response");
    }
    snprintf(response, response_len,
             "Received input: %s\nServer details:\nPort: %d\nIP Address: %s\n",
             input, PORT, inet_ntoa(serv_addr.sin_addr));
    return response;
}

int main(void) {
#ifdef _WIN32
    WSADATA wsaData;
    int wsaerr = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsaerr != 0) {
        fprintf(stderr, "WSAStartup failed with error: %d\n", wsaerr);
        return EXIT_FAILURE;
    }
#endif

    int sockfd, newsockfd;
    struct sockaddr_in serv_addr, cli_addr;
#ifdef _WIN32
    int clilen;
#else
    socklen_t clilen;
#endif

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
#ifdef _WIN32
        closesocket(sockfd);
#else
        close(sockfd);
#endif
        error("ERROR on binding");
    }

    if (listen(sockfd, 5) < 0) {
#ifdef _WIN32
        closesocket(sockfd);
#else
        close(sockfd);
#endif
        error("ERROR on listen");
    }

    clilen = sizeof(cli_addr);
    printf("Finger server listening on port %d...\n", PORT);

    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0) {
#ifdef _WIN32
        closesocket(sockfd);
#else
        close(sockfd);
#endif
        error("ERROR on accept");
    }

    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
#ifdef _WIN32
    int n = recv(newsockfd, buffer, BUFFER_SIZE - 1, 0);
#else
    int n = recv(newsockfd, buffer, BUFFER_SIZE - 1, 0);
#endif
    if (n < 0) {
#ifdef _WIN32
        closesocket(newsockfd);
        closesocket(sockfd);
#else
        close(newsockfd);
        close(sockfd);
#endif
        error("ERROR receiving from socket");
    }
    buffer[n] = '\0';

    char *response = generate_response(buffer, serv_addr);

#ifdef _WIN32
    if (send(newsockfd, response, strlen(response), 0) < 0) {
#else
    if (send(newsockfd, response, strlen(response), 0) < 0) {
#endif
        free(response);
#ifdef _WIN32
        closesocket(newsockfd);
        closesocket(sockfd);
#else
        close(newsockfd);
        close(sockfd);
#endif
        error("ERROR sending to socket");
    }

    free(response);
#ifdef _WIN32
    closesocket(newsockfd);
    closesocket(sockfd);
    WSACleanup();
#else
    close(newsockfd);
    close(sockfd);
#endif

    return EXIT_SUCCESS;
}
