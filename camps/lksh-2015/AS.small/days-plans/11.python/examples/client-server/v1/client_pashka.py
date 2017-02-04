# -*- coding: utf-8 -*-

import socket, time

ip = '10.0.6.197'
port = 9090

sock = socket.socket()
sock.connect((ip, port))

# str(b, 'utf-8')   : bytes --> string
# bytes(s, 'utf-8') : string --> bytes

f = open('a.png', 'wb')
while True:
	data = sock.recv(1024)
	if not data:
		break
	f.write(data)
f.close()
sock.close()
