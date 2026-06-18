// Import necessary libraries for socket programming and input/output operations
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int main() {

    // Define the IP address and port number of the server to which we want to send a message
    const char* ip_address = "127.0.0.1";
    // CHANGED port from 5555 to 6666
    const int port_no = 6666;

    // Create a UDP socket using the socket() system call
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }

    // Build server's address structure using sockaddr_in
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address);
    sin.sin_port = htons(port_no);

    // Define the message to be sent to the server and its length including the null terminator
    char data[] = "hello";
    int data_len = sizeof(data);

    // Send the message to the server using the sendto() system call
    int sent_bytes = sendto(sock, data, data_len, 0, (struct sockaddr *) &sin, sizeof(sin));
    if (sent_bytes < 0) {
        perror("error writing to socket");
    }

    // Wait for a response from the server and read it using the recvfrom() system call
    struct sockaddr_in from;
    unsigned int from_len = sizeof(struct sockaddr_in);
    char buffer[4096];
    int bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);
    if (bytes < 0) {
        perror("error reading from socket");
    }

    cout << "The server sent: " << buffer << endl;

    close(sock);

    return 0;
}