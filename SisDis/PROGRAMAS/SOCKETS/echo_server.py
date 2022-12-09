#!/usr/bin/env python3

import socket

HOST = '127.0.0.1'  # endereco ip
PORT = 4444        # numero de porta

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    conn, addr = s.accept()
    with conn:
        print('conectado por:', addr)
        while True:
            data = conn.recv(1024) #tamanho do buffer data
            if not data:
                break
            conn.sendall(data) #devolve o conteudo recebido em data ao cliente 
