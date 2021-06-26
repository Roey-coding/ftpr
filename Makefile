client_hello.exe: client_hello.c
	gcc -Wall client_hello.c -o client_hello.exe

server_hello.exe: server_hello.c
	gcc -Wall server_hello.c -o server_hello.exe

server_certificate.exe: server_certificate.c
	gcc -Wall server_certificate.c -o server_certificate.exe
	
server_key_exchange.exe: server_key_exchange.c
	gcc -Wall server_key_exchange.c -o server_key_exchange.exe
	

