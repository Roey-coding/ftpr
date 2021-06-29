import socket
import subprocess
import sys
import ast
import os

IP = '' 
PORT = 2004
WELCOME_MESSAGE = """
Welcome to the server.
this is a basic welcome message,
You can turn it off by adding -q as an argument.
"""

def recive_tls(conn):
	y = int.from_bytes(conn.recv(5)[3:5], "big")
	return y;

# def get_content(programs):
	# result = b""
	
	# for prog in programs:
		# string = subprocess.check_output([prog]).decode()
		# print(prog)
		# b = str(string.encode())[2:][:-1]
		# a = bytes.fromhex(b)
		
		# result += a
	
	# return result

def get_content(program):
	string = subprocess.check_output([program]).decode()
	b = str(string.encode())[2:][:-1]
	return bytes.fromhex(b)
	
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
		print(conn.recv(recive_tls(conn)))
		conn.send(get_content("server_hello.exe"))
		conn.send(get_content("server_certificate.exe"))
		conn.send(get_content("server_key_exchange.exe"))
		conn.send(get_content("server_hello_done.exe"))
		print(conn.recv(recive_tls(conn)))

def welcome():
	print(WELCOME_MESSAGE)

if __name__ == "__main__":
	if(len(sys.argv) == 1 or sys.argv[1] != "-q"):
		welcome()

	main()