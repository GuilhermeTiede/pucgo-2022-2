#!/usr/bin/env python3

import socket

HOST = '127.0.0.1'  # endereco ip
PORT = 4444        # numero de porta

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    s.sendall(b'CMP1190, C01')
    data = s.recv(1024)

print('Received', repr(data))
