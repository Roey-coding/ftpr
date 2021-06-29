#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tls_headers.h"

struct __attribute__((__packed__)) record {
	struct record_layer rl;
	struct handshake_layer hl;
	
	uint8_t  curve;
	uint16_t curve_type;
	
	uint8_t  public_key_length;
	char public_key[32];
	
	uint16_t signature_type;
	uint16_t signature_length;
	char signature[512];
};

void get_content(char * name, char * s, int index, int amount) {
	FILE *f = {0};
	
	if ((f = fopen(name, "r")) == NULL) {
		printf("Error! opening file");
		exit(1);
	}
	
	fseek(f, index, SEEK_SET);	
	
	fread(s, 1, amount, f);
}

void set_content(char * name, char * s, int index, int amount) {
	FILE *f = {0};
	
	if ((f = fopen(name, "w")) == NULL) {
		printf("Error! opening file");
		exit(1);
	}
	
	fseek(f, index, SEEK_SET);	
	
	fwrite(s, 1, amount, f);
	fclose(f);
}

void print_bytes(char * s, int amount) {
	
	for(int i = 0; i < amount; i++) {
		printf("%02x", (unsigned char)s[i]);
	}
	
}

void print_struct(struct record r) {
	unsigned char packet[sizeof(r)] = {0x00};
	memcpy(packet, &r, sizeof(r));
	
	for(int i = 0; i < sizeof(packet); i++) {
		printf("%02x", packet[i]);
	}
}

void sign_packet(struct record *s, char * client_random, char * server_random) {
	unsigned char total_string[101];
	char content[101] = {0};
	
	memcpy((unsigned char *)&total_string[0], client_random, 32);
	memcpy((unsigned char *)&total_string[32], server_random, 32);
	memcpy((unsigned char *)&total_string[64], (char *)&s->curve, 36);
	
	
	set_content("compute.txt", total_string, 0, 100);
	get_content("compute.txt", content, 0, 100);
	
	system("openssl dgst -sign server.key -sha512 compute.txt > signature.txt");
	get_content("signature.txt", s->signature, 0, 512);
	
}

int main() {
	struct record key_exchange = {0};
	char s[100] = {0};
	char cmd[70] = {0};
	
	key_exchange.rl.record_type = 0x16;
	key_exchange.rl.version = 0x0303;
	key_exchange.rl.length = 0x2c02;
	
	key_exchange.hl.handshake_type = 0x0c;
	key_exchange.hl.hello_length[0] = 0x00;
	key_exchange.hl.hello_length[1] = 0x02;
	key_exchange.hl.hello_length[2] = 0x28;
	
	key_exchange.curve = 0x03;
	key_exchange.curve_type = 0x1d00;
	
	key_exchange.public_key_length = 0x20;
	
	system("openssl genpkey -algorithm X25519 -out privkey.pem");
	system("openssl pkey -in privkey.pem -pubout -out pubkey.pem");
	
	get_content("pubkey.pem", s, 43, 44);
	
	strcat(cmd, "echo '");
	strcat(cmd, s);
	strcat(cmd, "' | base64 --decode > hello.txt");
	system(cmd);
	
	get_content("hello.txt", key_exchange.public_key, 0, 32);
	
	
	key_exchange.signature_type   = 0x0106;
	key_exchange.signature_length = 0x0002;
	
	sign_packet(&key_exchange, "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB", "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
	 
	print_struct(key_exchange);
	
	return 0;
}

