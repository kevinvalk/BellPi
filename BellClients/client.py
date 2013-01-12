import socket
import sys
import time

HOST, PORT = "localhost", 8311
clientKey = 0xCAADBCB7
packet = [0x8B, 0xBE, 0xAD, 0xDE, 0, 2, 0, 0, 0]
packet2 = [0x8B, 0xBE, 0xAD, 0xDE, 0, 3, 0, 0, 0]

# Create a socket (SOCK_STREAM means a TCP socket)
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect to server and send data
sock.connect((HOST, PORT))

# Try first to ask something w/o reg
#sock.sendall(bytes(pInfo + "\n", "utf-8"))
#received = str(sock.recv(1024), "utf-8")
#print("Received: {}".format(received))

# Now reg
sock.sendall(bytearray(packet))
time.sleep(1)
#sock.sendall(bytearray(packet2))
#time.sleep(1)
received = str(sock.recv(1024), "utf-8")
print("Received: {}".format(received))

sock.close()


