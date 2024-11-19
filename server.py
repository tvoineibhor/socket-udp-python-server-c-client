import socket
import struct
import numpy as np

def send_int_array(conn, arr):
    # Send array size
    size = len(arr)
    conn.sendall(struct.pack('!I', size))
    
    # Send array data
    conn.sendall(arr.tobytes())

# Set up server
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(('localhost', 12345))
server_socket.listen(1)

print("Server listening on port 12345")

while True:
    conn, addr = server_socket.accept()
    print(f"Connected by {addr}")
    
    # Example array to send
    int_array = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9, 0], dtype=np.int32)
    
    send_int_array(conn, int_array)
    print(f"Sent array: {int_array}")
    
    conn.close()