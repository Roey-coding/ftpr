import socket
import sys

IP = '' 
PORT = 2004
WELCOME_MESSAGE = """
Welcome to the server.
this is a basic welcome message,
You can turn it off by adding -q as an argument.
"""


def main():
	tcp_server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	tcp_server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1) 
	tcp_server.bind((IP, PORT))

	while 1:
		x = input("start?")
		
		if(x == "no") :
			break
		
		tcp_server.listen(4)
		(conn, (ip,port)) = tcp_server.accept()
		print(conn.recv(2000))

def welcome():
	print(WELCOME_MESSAGE)

if __name__ == "__main__":
	if(len(sys.argv) == 1 or sys.argv[1] != "-q"):
		welcome()

	main()