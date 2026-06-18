# Import socket module
import socket

# Create a TCP socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# server is running on the same machine as the client, so we can use the loopback address
dest_ip = '127.0.0.1'
# The server is listening on port 12345, so we will connect to that port
dest_port = 12345
# Connect the socket to the server's address and port
s.connect((dest_ip, dest_port))

# ask the user for a message to send
msg = input("Message to send: ")
# Keep sending messages until the user types 'quit' (CHANGE: client quits by typing case insensitive 'quit')
while msg.lower() != 'quit':
    # encode the message as bytes and send it to the server
    s.send(bytes(msg, 'utf-8'))
    # Wait for the server to send a response
    data = s.recv(4096)
    # print the response from the server, decoding it from bytes to a string
    print("Server sent: ", data.decode('utf-8'))
    # ask the user for another message to send
    msg = input("Message to send: ")

# Close the socket when we're done
s.close()