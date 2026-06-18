# Import socket library
from socket import socket, AF_INET, SOCK_DGRAM

# Create a UDP socket
s = socket(AF_INET, SOCK_DGRAM)

# Empty string for source IP to bind to all interfaces, and a port number
src_ip = ''
# Define the source port to bind the socket to
src_port = 12345
# Bind the socket to the specified source IP and port
s.bind((src_ip, src_port))

# Keep the server running to listen for incoming messages
while True:
    # Receive a message from a client, along with the sender's information (IP and port)
    data, sender_info = s.recvfrom(2048)
    print(data.decode('utf-8'))
    # IP and Port sent as a tuple, print it to the console
    print(sender_info)

    # Send a response back to the sender (CHANGE: with additional text)
    s.sendto(b"Echo: " + data.upper(), sender_info)