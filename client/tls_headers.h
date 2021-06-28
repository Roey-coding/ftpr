
struct __attribute__((__packed__)) record_layer {
	uint8_t  record_type;
	uint16_t version;
	uint16_t length;
};

struct __attribute__((__packed__)) handshake_layer {
	uint8_t  handshake_type;
	char     hello_length[3];
};

