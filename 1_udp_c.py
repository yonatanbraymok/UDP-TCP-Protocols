# Import socket library
from socket import socket, AF_INET, SOCK_DGRAM

# Create a UDP socket
s = socket(AF_INET, SOCK_DGRAM)

# Define the destination IP (server address)
dst_ip = '127.0.0.1'
# Define the destination port
dst_port = 12345

# Send a message to the server
s.sendto(b'Hello', (dst_ip,dst_port))

# Receive a response from the server
data, sender_info = s.recvfrom(2048)
# Decode the received bytes to a string and print it along with sender information
print(data.decode('utf-8'))
# Print the sender's information (which includes the sender's IP address and port number)
print(sender_info)

# Close the socket after communication is done
s.close()
