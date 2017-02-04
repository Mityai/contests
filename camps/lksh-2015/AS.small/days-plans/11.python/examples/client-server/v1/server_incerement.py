#!/usr/bin/env python
# -*- coding: utf-8 -*-

import socket

sock = socket.socket()
sock.bind(('localhost', 9090))
sock.listen(1)

while True:
	conn, addr = sock.accept()
	print('connected:', addr)
	while True:
		data = conn.recv(1024)
		if not data :
		  break
		print('data=' + data + '.')
		conn.send(str(int(data) + 1))
	conn.close()
