#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tls_headers.h"

struct __attribute__((__packed__)) record {
	struct record_layer rl;
	struct handshake_layer hl;
	
	char all_certificates_length[3];
	char certificate_length[3];
	char certificate[5000];
};

void print_struct(struct record r) {
	unsigned char packet[sizeof(r)] = {0x00};
	memcpy(packet, &r, sizeof(r));
	
	for(int i = 0; i < 1102; i++) {
		printf("%02x", packet[i]);
	}
}

void get_content(char * name, char * s, int index, int amount) {
	FILE *f = {0};
	//long fsize = 0;
	
	if ((f = fopen(name, "r")) == NULL) {
		printf("Error! opening file");
		exit(1);
	}
	
	//fseek(f, 0, SEEK_SET);
	//fsize = ftell(f);
	fseek(f, index, SEEK_SET);	
	
	fread(s, 1, amount, f);
}

int main() {
	struct record server_certificate = {0};
	FILE *cert = {0};
	int fsize = 0;

	server_certificate.rl.record_type = 0x16;
	server_certificate.rl.version = 0x0303;
	server_certificate.rl.length = 0x4904;
	
	server_certificate.hl.handshake_type = 0x0b;
	server_certificate.hl.hello_length[0] = 0x00;
	server_certificate.hl.hello_length[1] = 0x04;
	server_certificate.hl.hello_length[2] = 0x45;
	
	if ((cert = fopen("serv.txt","r")) == NULL) {
		printf("Error! opening file");
		exit(1);
	}
	
	fseek(cert, 0L, SEEK_END);
	fsize = ftell(cert);
	//fseek(cert, 0, SEEK_SET);
	
	//memset(server_certificate.certificate, 0xf1, sizeof(server_certificate.certificate));
	//fread(server_certificate.certificate, 1, fsize, cert);
	
	get_content("serv.txt", server_certificate.certificate, 0, 1087);
	
	server_certificate.all_certificates_length[2] = 0x42;
	server_certificate.all_certificates_length[1] = 0x04;
	server_certificate.all_certificates_length[0] = 0x00;
	
	server_certificate.certificate_length[2] = 0x3f;
	server_certificate.certificate_length[1] = 0x04;
	server_certificate.certificate_length[0] = 0x00;
	
	print_struct(server_certificate);
	
	fclose(cert);
	return 0;
}
	