import socket
 
HOST = ''   # Symbolic name, meaning all available interfaces
PORT = 8888 # Arbitrary non-privileged port
 
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print('Socket created');
 
#Bind socket to local host and port
try:
	s.bind((HOST, PORT))
	print('Socket bind complete');
except socket.error as msg:
	print('Bind failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]);
	sys.exit()

#Start listening on socket
s.listen(1)
print('Socket now listening')
 
#now keep talking with the client
while 1:
	#wait to accept a connection - blocking call
	conn, addr = s.accept()
	print('Connected with ' + str(addr));
	conn.close();
s.close()
