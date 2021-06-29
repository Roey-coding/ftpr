#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tls_headers.h"

struct __attribute__((__packed__)) record {
	struct record_layer rl;
	struct handshake_layer hl;
	
	// client version
	uint16_t tls_version;
	
	// client random
	char     client_random[32];
	
	// session id
	uint8_t  session_id;
	
	// cipher suites
	uint16_t suites_length;
	uint16_t suites[1000];
	
	// compression methods
	uint8_t  compression_length;
	uint8_t  compression;
	
	// extentions length
	uint16_t extentions_length;
	
	uint16_t server_name_flag;
	uint16_t server_name_length;
	uint16_t server_name_list_entry_length;
	uint8_t  server_name_list_entry_type;
	uint16_t hostname_length;
	char     hostname[1000];
	// server name extension
	// status request extention
	// supported groups extention
	// signature algorithem extension
	// renegotiation info extension
	
};
/* 
struct internal {
	hostname_length = (num>>8) | (num<<8);

	
}; */


// int valid_struct(struct record r) {	}

void print_struct(struct record r) {
	uint16_t suites_length = (r.suites_length >> 8) | (r.suites_length << 8);
	uint16_t hostname_length = (r.hostname_length >> 8) | (r.hostname_length << 8);
	int i = 0;
	
	//printf("This is the suits length: %d\n", suites_length);
	//printf("This is the hostname length: %d\n", hostname_length);
	
	unsigned char packet[sizeof(r)] = {0x00};
	memcpy(packet, &r, sizeof(r));
	
	for(; i < 46; i++) {
		printf("%02x", packet[i]);
	}
	
	if(!suites_length) {
		printf("No cypher suits are provided\n");
		exit(1);
	}
	
	for(; i < suites_length + 46; i++) {
		printf("%02x", packet[i]);
	}
	
	for(i = 2000 + 46; i < 46 + 13 + 2000; i++) {
		printf("%02x", packet[i]);
	}
	
	for(; i <  46 + 13 + 2000 + hostname_length; i++) {
		printf("%02x", packet[i]);
	}
}

int main() {
	struct record client_hello = {0};
	
	client_hello.rl.record_type = 0x16;
	client_hello.rl.version = 0x0103;
	client_hello.rl.length = 0x6900;
	
	client_hello.hl.handshake_type = 0x01;
	client_hello.hl.hello_length[0] = 0x00;
	client_hello.hl.hello_length[1] = 0x00;
	client_hello.hl.hello_length[2] = 0x65;
	
	client_hello.tls_version = 0x0303;
	
	memcpy(client_hello.client_random, "123456789asdfghjklzxcvbnmasdfghj", 32);
	
	client_hello.session_id = 0x00;
	client_hello.suites_length = 0x2000;
	
	uint16_t arr[] = {0xa8cc, 0xa9cc, 0x2fc0, 0x30c0, 0x2bc0, 0x2cc0, 0x13c0, 0x09c0, 0x14c0, 0x0ac0, 0x9c00, 0x9d00, 0x2f00, 0x3500, 0x12c0, 0x0a00};
	memset(client_hello.suites, 0xffff, sizeof(client_hello.suites));
	memcpy(client_hello.suites, arr, sizeof(arr));

	client_hello.compression_length = 0x1;
	client_hello.compression = 0x00;
	
	client_hello.extentions_length = 0x1c00;
	
	client_hello.server_name_flag = 0x0000;
	client_hello.server_name_length = 0x1800;
	client_hello.server_name_list_entry_length = 0x1600;
	client_hello.server_name_list_entry_type = 0x00;
	client_hello.hostname_length = 0x1300;
	
	memset(client_hello.hostname, 0xff, sizeof(client_hello.hostname));
	memcpy(client_hello.hostname, "example.ulfheim.net", 19);
 
	print_struct(client_hello);
	
	return 0;
}