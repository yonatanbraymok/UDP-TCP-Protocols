# Import the socket module
import socket

# Create a TCP socket
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# Empty string means listen on all network interfaces
server_ip = ''
# Port number clients will connect to
server_port = 12345
# Bind the socket to the chosen IP and port
server.bind((server_ip, server_port))
# Start listening
server.listen(5)

# Accept and handle clients forever
while True:
    # Block until a client connects; returns a new socket for that client
    client_socket, client_address = server.accept()
    # Show which client connected (IP and port)
    print('Connection from: ', client_address)
    # Read up to 1024 bytes from the connected client
    data = client_socket.recv(1024)
    # Keep exchanging messages until the client sends an empty string
    while not data.decode('utf-8') == '':
        # Print the message received from the client
        print('Received: ', data.decode('utf-8'))
        # Send the same message back in uppercase
        client_socket.send(data.upper())
        # Wait for the next message from the client
        data = client_socket.recv(1024)

    # Client sent empty string, so it is disconnecting
    print('Client disconnected')
    # Close the connection to this client
    client_socket.close()
