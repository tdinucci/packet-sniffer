#ifdef _WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#endif

#include "raw-socket.h"
#include "util.h"

RawSocket::~RawSocket() {}

shared_ptr<vector<uint8_t>> RawSocket::read() {
	struct sockaddr saddr;
	int saddr_len = sizeof(saddr);

	char buffer[MAX_PACKET_SIZE];

	int read_size = recvfrom(handle, (char*)buffer, MAX_PACKET_SIZE, 0, &saddr, &saddr_len);
	if (read_size < 0)
		throw runtime_error(*get_last_error("Socket read error"));

	auto packet = new vector<uint8_t>(buffer, buffer + read_size);

	return shared_ptr<vector<uint8_t>>(packet);
}