import socket
import subprocess
import sys
import ast
import os

HOST = "127.0.0.1"
PORT = 2004
BUFFER_SIZE = 2000

def main(program):
	string = subprocess.check_output([program]).decode()

	b = str(string.encode())[2:][:-1]
	a = bytes.fromhex(b)

	print(len(b))

	tcpClientA = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	tcpClientA.connect((HOST, PORT))

	tcpClientA.send(a)


if __name__ == "__main__":
	if(len(sys.argv) == 2):
		main(sys.argv[1])
	else:
		print("Usage: python client.py [packet_generator_name.exe]")