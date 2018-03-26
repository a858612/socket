import socket
import threading
import time
import sys

def send(mySocket):
	while True:
		message = 0
		message = input()
		mySocket.send(message.encode())
def recv(mySocket):
	while True:
		data = mySocket.recv(1024).decode()
		if not data:
			break
		print (data)
		

def Main():
        host = '127.0.0.1'
        if len(sys.argv) == 1:
        	port = 5000
        port = int(sys.argv[1])  
        mySocket = socket.socket()
        mySocket.connect((host,port))
        t1 = threading.Thread(name='send', target=send,args=(mySocket,))
        t2 = threading.Thread(name='recv', target=recv,args=(mySocket,))
        t1.start()
        t2.start() 
        t1.join()
        t2.join()
        mySocket.close()
  
if __name__ == '__main__':
    Main()



