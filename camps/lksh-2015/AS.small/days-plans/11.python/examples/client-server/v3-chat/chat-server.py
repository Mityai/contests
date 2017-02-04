# -*- coding: utf-8 -*-

import socket, sys, threading 
 
fconfig = open('config.txt', 'r')
HOST = fconfig.readline().strip()
PORT = int(fconfig.readline().strip())

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print('Socket created')
try:
	s.bind((HOST, PORT))
except socket.error as msg:
	print('Bind failed. Error Code : ' + str(msg) + ' Message ')
	sys.exit()
print('Socket bind complete')
s.listen(20)
print('Socket now listening')
 
name = {}

def get(infile):
	data = infile.readline().strip()
	print("get: " + data)
	return data
def push(outfile, s):
	print("push: " + s)
	print(s, file=outfile)
	outfile.flush()
def flush():
	sys.stdout.flush()
	sys.stderr.flush()

history = []
lastId = {}

def addToHistory(s):
	print(s)
	flush()
	history.append(s)

def clientthread(conn, addr):
	# send <msg> --> ok
	# name <msg> --> ok
	# quit       --> ok
	# history    --> <n> <a1> ... <an>
	infile = conn.makefile('r', encoding='utf-8')
	outfile = conn.makefile('w', encoding='utf-8')

	ip = addr[0]
	name[addr] = ip
	if not (ip in lastId):
		lastId[ip] = len(history)

	while True:
		com = get(infile)
		print(name[addr] + ": command=" + com)
		if com == "send":
			data = get(infile)
			addToHistory(name[addr] + ": " + data)
			push(outfile, 'OK...' + data)
		elif com == "history":
			last = lastId[ip]
			end = len(history)
			push(outfile, str(end - last))
			for i in range(last, end):
				push(outfile, history[i])
			lastId[ip] = end
		elif com == "quit":
			push(outfile, 'goodbye')
			conn.close()
			break
		elif com == "name":
			newName = get(infile)
			addToHistory(name[addr] + ": " + "new name = " + newName)
			name[addr] = newName
			push(outfile, 'your name: ' + newName)
		else:
			push(outfile, 'unknown command: ' + com)
	flush()

while 1:
	conn, addr = s.accept()
	addToHistory('Connected with ' + addr[0])
	flush()
	threading.Thread(target=clientthread, args=(conn, addr)).start()
 
s.close()
