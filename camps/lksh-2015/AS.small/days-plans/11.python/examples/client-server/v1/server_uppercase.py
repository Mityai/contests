#!/usr/bin/env python
# -*- coding: utf-8 -*-

import socket

ip = '10.0.6.197'
port = 9090

sock = socket.socket()
sock.bind((ip, port))
sock.listen(1)

while True:
	conn, addr = sock.accept()
	print('connected:', addr)
	while True:
		data = conn.recv(1024)
		if not data:
			break
		conn.send(data.upper())
	conn.close()
