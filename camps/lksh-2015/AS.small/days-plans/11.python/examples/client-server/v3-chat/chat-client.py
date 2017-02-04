# -*- coding: utf-8 -*-

import sys, socket, threading

fconfig = open('config.txt', 'r')
ip = fconfig.readline().strip()
port = int(fconfig.readline().strip())

sock = socket.socket()
sock.connect((ip, port))
inf = sock.makefile('r', encoding='utf-8')
outf = sock.makefile('w', encoding='utf-8')

def flush():
	sys.stdout.flush()
	sys.stderr.flush()
def log(s):
	print(s)
	flush()
def push(data):
	log("write: " + data)
	print(data, file=outf)
	outf.flush()
def get():
	data = inf.readline().strip()
	log("get: " + data)
	return data
def read():
	return sys.stdin.readline().strip()

while True:
	com = read()
	if com == "quit":
		push(com)
		get()
		break
	elif com == "name":
		push(com)
		push(read())
		get()
	elif com == "history":
		push(com)
		l = int(get())
		for i in range(l):
			get()
	else:
		push("send")
		push(com)
		get()
sock.close()
