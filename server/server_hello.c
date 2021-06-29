#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "tls_headers.h"

struct __attribute__((__packed__)) record {
	struct record_layer rl;
	struct handshake_layer hl;
	
	// server version
	uint16_t tls_version;
	
	// client random
	char     server_random[32];
	
	// session id
	uint8_t  session_id;
	
	// selected cipher suite
	uint16_t cipher_suite;
	
	// compression_method
	uint8_t  compression_method;
	
	// extensions_length
	uint16_t extensions_length;
	
	uint16_t renegotiation_flag;
	uint16_t renegotiation_info_length;
	uint8_t renegotiation_datalength;
	
};

void print_struct(struct record r) {
	unsigned char packet[sizeof(r)] = {0x00};
	memcpy(packet, &r, sizeof(r));
	
	for(int i = 0; i < sizeof(packet); i++) {
		printf("%02x", packet[i]);
	}
}

int main() {
	struct record server_hello = {0};
	
	server_hello.rl.record_type = 0x16;
	server_hello.rl.version = 0x0303;
	server_hello.rl.length = 0x3100;
	
	server_hello.hl.handshake_type = 0x02;
	server_hello.hl.hello_length[0] = 0x00;
	server_hello.hl.hello_length[1] = 0x00;
	server_hello.hl.hello_length[2] = 0x2d;

	server_hello.tls_version = 0x0303;
	memcpy(server_hello.server_random, "123456789asdfghjklzxcvbnmasdfghj", 32);
	
	server_hello.session_id = 0x00;
	server_hello.cipher_suite = 0x13c0;
	server_hello.compression_method = 0x00;
	
	server_hello.extensions_length = 0x0500;
	server_hello.renegotiation_flag = 0x01ff;
	server_hello.renegotiation_info_length = 0x0100;
	server_hello.renegotiation_datalength = 0x00;
	
	print_struct(server_hello);
	
	return 0;
}
	