#ifndef _WIN32

#include <linux/if_ether.h>
#include <sys/socket.h>

#include "linux-socket.h"
#include "../util.h"

LinuxSocket::LinuxSocket(const sockaddr& bind_to) {
	handle = socket(AF_PACKET, SOCK_RAW, PROTOCOL_ALL);
	if ((int)handle < 0)
		throw runtime_error(*get_last_error("Failed to create socket"));

	if (bind(handle, &bind_to, sizeof(bind_to)) == SOCKET_ERROR) {
		throw runtime_error(*get_last_error("Bind failed"));
	}
}

LinuxSocket::~LinuxSocket() {
	int status = shutdown(sock, SHUT_RDWR);
	// if (status == 0) { status = close(sock); }
}

#endif