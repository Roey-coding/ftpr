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
	
	for(int i = 0; i < sizeof(packet); i++) {
		if(packet[i] != 0xf1) {
			printf("%02x", packet[i]);
		}
	}
}

int main() {
	struct record server_certificate = {0};
	FILE *cert = {0};
	long fsize = 0;

	server_certificate.rl.record_type = 0x16;
	server_certificate.rl.version = 0x0303;
	server_certificate.rl.length = 0x0206;
	
	server_certificate.hl.handshake_type = 0x0b;
	server_certificate.hl.hello_length[0] = 0x00;
	server_certificate.hl.hello_length[1] = 0x05;
	server_certificate.hl.hello_length[2] = 0xff;
	
	if ((cert = fopen("revolution-tls.com.crt","r")) == NULL) {
		printf("Error! opening file");
		exit(1);
	}
	
	fseek(cert, 0, SEEK_END);
	fsize = ftell(cert);
	fseek(cert, 0, SEEK_SET);
	
	memset(server_certificate.certificate, 0xf1, sizeof(server_certificate.certificate));
	fread(server_certificate.certificate, 1, fsize, cert);
	
	//printf("%lu\n", fsize);
	
	server_certificate.all_certificates_length[2] = 0x00;
	server_certificate.all_certificates_length[1] = 0x05;
	server_certificate.all_certificates_length[0] = 0xfc;
	
	server_certificate.certificate_length[2] = 0x00;
	server_certificate.certificate_length[1] = 0x05;
	server_certificate.certificate_length[0] = 0xf9;
	
	print_struct(server_certificate);
	
	return 0;
}
	