import socket, sys, threading 
 
HOST = '10.0.6.197'
PORT = 9090
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print('Socket created')
try:
    s.bind((HOST, PORT))
except socket.error as msg:
    print('Bind failed. Error Code : ' + str(msg) + ' Message ')
    sys.exit()
print('Socket bind complete')
s.listen(10)
print('Socket now listening')
 
def clientthread(conn):
    conn.send(b'Welcome to the server. Type something and hit enter\n') #send only takes string
    while True:
        data = conn.recv(1024)
        reply = b'OK...' + data
        if not data: 
            break
        conn.sendall(reply)
    conn.close()
 
while 1:
	conn, addr = s.accept()
	print('Connected with ' + addr[0] + ':' + str(addr[1]))
	threading.Thread(target=clientthread, args=(conn,)).start()
 
s.close()
