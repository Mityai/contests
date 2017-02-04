from threading import Thread
from multiprocessing import Process
import os, time, select, sys

def console():
	while True:
		s = sys.stdin.readline()
		if s == "":
			break
		print("line = ", s)

def info(title):
	print(title)
	print('module name:', __name__)
	print('parent process:', os.getppid())
	print('process id:', os.getpid())

def f(name):
	info('function f')
	print('hello', name)

if __name__ == '__main__':
	info('main line')
	Process(target=f, args=('bob',)).start()
	Thread(target=console).start()
	print("started")
	while True:
		print("[tick]")
		time.sleep(0.5)
