# -*- coding: utf-8 -*-

import socket, time

sock = socket.socket()
sock.connect(('localhost', 9090))

# str(b, 'utf-8')   : bytes --> string
# bytes(s, 'utf-8') : string --> bytes

x = 10
while x < 100:
	sock.send(bytes(str(x), 'utf-8'))
	data = sock.recv(1024)
	print(str(data, 'utf-8'))
	x = int(data)
sock.close()
