// Standard I/O, socket API, network address structures, and string utilities
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <cctype>

using namespace std;

int main() {

    const int server_port = 5555;

    // Create a TCP socket (SOCK_STREAM = reliable byte stream)
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }

    // Set up the server address
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);

    // Bind the listening socket to the address
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
    }

    // Mark socket as passive (server); queue up to 5 pending connections
    if (listen(sock, 5) < 0) {
        perror("error listening to a socket");
    }

    // Accept one incoming connection; creates a new socket for this client
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int client_sock = accept(sock,  (struct sockaddr *) &client_sin,  &addr_len);

    if (client_sock < 0) {
        perror("error accepting client");
    }

    // Keep exchanging messages over the same TCP connection until disconnect
    char buffer[4096];
    int read_bytes = recv(client_sock, buffer, sizeof(buffer) - 1, 0);
    while (read_bytes > 0) {
        buffer[read_bytes] = '\0';

        // Empty message signals the client wants to disconnect
        if (strlen(buffer) == 0) {
            break;
        }

        cout << "Received: " << buffer << endl;

        // Echo the message back in uppercase (same behavior as the Python TCP server)
        for (int i = 0; i < read_bytes; i++) {
            buffer[i] = toupper(buffer[i]);
        }

        int sent_bytes = send(client_sock, buffer, read_bytes, 0);
        if (sent_bytes < 0) {
            perror("error sending to client");
            break;
        }

        read_bytes = recv(client_sock, buffer, sizeof(buffer) - 1, 0);
    }

    if (read_bytes < 0) {
        perror("error reading from client");
    }
    else {
        cout << "Client disconnected" << endl;
    }

    // Close the client connection and the listening socket
    close(client_sock);
    close(sock);


    return 0;
}
