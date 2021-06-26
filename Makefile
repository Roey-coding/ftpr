client_hello.exe: client_hello.c
	gcc -Wall client_hello.c -o client_hello.exe

server_hello.exe: server_hello.c
	gcc -Wall server_hello.c -o server_hello.exe

