# -*- coding: utf-8 -*-

import socket

ip = '10.0.6.197'
port = 9090

sock = socket.socket()
sock.connect((ip, port))
data = sock.recv(1024)
print(data)
while True:
	sock.send(b'hello, world!')
	data = sock.recv(1024)
	print(data)
sock.close()

