
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

/*
 * Function to handle client connections.
 * Receives a filename from the client and sends the file content back.
 */
void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_read;

    // Read the filename from the client
    bytes_read = read(client_socket, buffer, sizeof(buffer) - 1);
    if (bytes_read < 0) {
        perror("Failed to read from socket");
        close(client_socket);
        return;
    }
    buffer[bytes_read] = '\0'; // Null-terminate the string

    // Open the requested file
    FILE *file = fopen(buffer, "r");
    if (file == NULL) {
        perror("File not found");
        close(client_socket);
        return;
    }

    // Send the file content to the client
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        write(client_socket, buffer, bytes_read);
    }

    fclose(file);
    close(client_socket);
}

/*
 * Main function to set up the server.
 * Listens for incoming connections and spawns a new thread for each client.
 */
int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up the server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    listen(server_socket, 5);

    printf("Server listening on port %d\n", PORT);

    // Accept and handle client connections
    while ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len)) >= 0) {
        handle_client(client_socket);
    }

    close(server_socket);
    return 0;
}

