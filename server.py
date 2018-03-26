import socket
import threading
import time
import sys
def send(conn):
	while True:
		message = input()
		conn.send(message.encode())
def recv(conn):
	while True:
		data = '0'
		data = conn.recv(1024).decode()
		if not data:
			break
		print (data)
 
def Main():
    host = "127.0.0.1"
    if len(sys.argv) == 1:
    	port = 5000
    port = int(sys.argv[1])
    mySocket = socket.socket()
    mySocket.bind((host,port))
     
    mySocket.listen(1)
    conn, addr = mySocket.accept()
    print ("Connection from: " + str(addr))

    t1 = threading.Thread(name='send', target=send,args=(conn,))
    t2 = threading.Thread(name='recv', target=recv,args=(conn,))
    t1.start()
    t2.start()
    t1.join()
    t2.join()	        
    conn.close()
     
if __name__ == '__main__':
    Main()
