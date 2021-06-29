#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "tls_headers.h"

struct __attribute__((__packed__)) record {
	struct record_layer rl;
	struct handshake_layer hl;
};

void print_struct(struct record r) {
	unsigned char packet[sizeof(r)] = {0x00};
	memcpy(packet, &r, sizeof(r));
	
	for(int i = 0; i < sizeof(packet); i++) {
		printf("%02x", packet[i]);
	}
}

int main() {
	struct record server_hello_done = {0};
	
	server_hello_done.rl.record_type = 0x16;
	server_hello_done.rl.version = 0x0303;
	server_hello_done.rl.length = 0x0400;
	
	server_hello_done.hl.handshake_type = 0x0e;
	server_hello_done.hl.hello_length[0] = 0x00;
	server_hello_done.hl.hello_length[1] = 0x00;
	server_hello_done.hl.hello_length[2] = 0x00;
	
	print_struct(server_hello_done);
	
	return 0;
}
	