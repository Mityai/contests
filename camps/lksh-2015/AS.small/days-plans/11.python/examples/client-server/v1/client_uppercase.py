# -*- coding: utf-8 -*-

import socket, time

ip = '10.0.6.197'
port = 9090

sock = socket.socket()
sock.connect((ip, port))

# str(b, 'utf-8')   : bytes --> string
# bytes(s, 'utf-8') : string --> bytes

s = b'hello wolrd!'
while True:
	sock.send(s)
	data = sock.recv(1024)
print(str(data, 'utf-8'))
