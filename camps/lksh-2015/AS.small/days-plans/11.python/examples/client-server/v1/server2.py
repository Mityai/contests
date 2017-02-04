#!/usr/bin/env python
# -*- coding: utf-8 -*-

import time, sys, socket, threading, multiprocessing

run = True

def letmequit():
	print("srarted!")
	while True:
		s = sys.stdin.readline().strip()
		print('get ', s);
		if s == "q":
			print('kill thread');
			global run
			run = False
			sys.exit();
		else:
			print("print 'q' to quit")

def mainloop():
	print('mainloop')
	sock = socket.socket()
	sock.bind((ip, port))
	sock.listen(10)
	while True:
		conn, addr = sock.accept()
		print('connected:', addr)
		data = conn.recv(1024)
		if not data:
			break
		conn.send(data.upper())
		conn.close()

if __name__ == '__main__':
	threading.Thread(target=letmequit).start()
	myMain = multiprocessing.Process(target=mainloop)
	myMain.start()

	cnt = 0
	while run == True:
		cnt += 1
		time.sleep(0.5)
		print("cnt = ", cnt)
	myMain.terminate()
