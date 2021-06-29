#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

void gen_shared_secret(char * private_key, char * public_key) {
	char arr[500] = "./curve25519-mult.exe ";
	if(strlen(private_key) > 100 || strlen(private_key) > 100) {
		printf("Keys file names are too large\n.");
	} else {
		strncat(arr, private_key, 100);
		strncat(arr, " ", 1);
		strncat(arr, public_key, 100);
		strncat(arr, " > result.txt", 13);
		printf("%s", arr);
		system(arr);
	}
}

void gen_master_secret(char * shared_secret, char * client_random, char * server_random) {
	char seed[77] = {0};
	
	if(strlen(client_random) > 32 || strlen(server_random) > 32) {
		printf("randoms too large\n.");
	} else {
		strcat(seed, 'master secret');
		strcat(seed, client_random);
		strcat(seed, server_random);
		
		set_content("a0.txt", seed, 0, 77);
		"openssl dgst -sha256 -mac HMAC -macopt hexkey:"
	
	}
}

int main()
{
	char  shared_secret[32] = {0};
	char * client_random = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
	char * server_random = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
	
	gen_shared_secret("privkey.pem", "server_pub_key.pem");
	get_content("result.txt", shared_secret, 0, 32);

	gen_master_secret(shared_secret, client_random, server_random);
	
	return 0;
}
