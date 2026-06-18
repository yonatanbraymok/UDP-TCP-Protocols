// Standard I/O, socket API, network address structures, and string utilities
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string>

using namespace std;

int main() {

    // Server address: localhost on port 5555
    const char* ip_address = "127.0.0.1";
    const int port_no = 5555;

    // Create a TCP socket for a connection-oriented client
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }

    // Build the server's address structure
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address);
    sin.sin_port = htons(port_no);

    // Connect to the server (TCP three-way handshake)
    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error connecting to server");
    }

    // Repeatedly send messages and read echoes until the user types 'quit'
    string msg;
    cout << "Message to send: ";
    getline(cin, msg);
    while (msg != "quit") {
        int sent_bytes = send(sock, msg.c_str(), msg.length(), 0);
        if (sent_bytes < 0) {
            perror("error sending to server");
            break;
        }

        char buffer[4096];
        int read_bytes = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (read_bytes == 0) {
            cout << "Server closed the connection" << endl;
            break;
        }
        else if (read_bytes < 0) {
            perror("error reading from server");
            break;
        }
        else {
            buffer[read_bytes] = '\0';
            cout << "Server sent: " << buffer << endl;
        }

        cout << "Message to send: ";
        getline(cin, msg);
    }

    close(sock);


    return 0;
}
