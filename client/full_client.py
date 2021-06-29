import socket
import subprocess
import sys
import ast
import os

HOST = "127.0.0.1"
PORT = 2004
BUFFER_SIZE = 2000
PROGRMS = ["client_hello.exe", "client_key_exchange.exe"]

def recive_tls(conn):
	y = int.from_bytes(conn.recv(5)[3:5], "big")
	return y;

	
# def get_content(programs):
	# result = b""
	
	# for prog in programs:
		# string = subprocess.check_output([prog]).decode()

		# b = str(string.encode())[2:][:-1]
		# a = bytes.fromhex(b)
		
		# result += a
	
	# return result

def get_content(program):
	string = subprocess.check_output([program]).decode()
	b = str(string.encode())[2:][:-1]
	return bytes.fromhex(b)

def main():
	tcpclienta = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	tcpclienta.connect((HOST, PORT))
	
	payload = b""
	
	tcpclienta.send(get_content("client_hello.exe"))
	print(tcpclienta.recv(recive_tls(tcpclienta)))
	print(tcpclienta.recv(recive_tls(tcpclienta)))
	print(tcpclienta.recv(recive_tls(tcpclienta)))
	print(tcpclienta.recv(recive_tls(tcpclienta)))
	tcpclienta.send(get_content("client_key_exchange.exe"))
	#print(tcpclienta.recv(recive_tls(tcpclienta)))


if __name__ == "__main__":
	main()