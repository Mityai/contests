# -*- coding: utf-8 -*-

import sys, socket, threading
from tkinter import *

fconfig = open('config.txt', 'r')
ip = fconfig.readline().strip()
port = int(fconfig.readline().strip())

sock = socket.socket()
sock.connect((ip, port))
inf = sock.makefile('r', encoding='utf-8')
outf = sock.makefile('w', encoding='utf-8')

def log(s):
	print(s)
	T.insert(END, s + "\n")
	T.see(END)

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

master = Tk()
H = 1
DY = 30
DX = 80

def comSend(event):
	if entryMsg.get() == "":
		return
	push("send")
	push(entryMsg.get())
	get()
btSend = Button(master, text="Send", width=8, height=H)
btSend.bind("<Button-1>", comSend); 
btSend.pack()
entryMsg = Entry(master, width=20)
entryMsg.pack()

def comName(event):
	if entryName.get() == "":
		return
	push("name")
	push(entryName.get())
	get()
btName = Button(master, text="Name", width=8, height=H)
btName.bind("<Button-1>", comName); 
btName.pack()
entryName = Entry(master, width=20)
entryName.pack()

def comQuit(event):
	push("quit")
	get()
	master.destroy()
btQuit = Button(master, text="Quit", width=10, height=H)
btQuit.bind("<Button-1>", comQuit); 
btQuit.pack()

def comHistory(event):
	push("history")
	l = int(get())
	for i in range(l):
		get()
btHistory = Button(master, text="History", width=10, height=H)
btHistory.bind("<Button-1>", comHistory); 
btHistory.pack()

S = Scrollbar(master)
T = Text(master,
  font="Courier-New 10",
  width=40,
  height=10
)
S.pack(side=RIGHT, fill=Y)
S.config(command=T.yview)
T.config(yscrollcommand=S.set)
T.pack()

master.mainloop()
