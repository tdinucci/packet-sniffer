#ifndef _WIN32

#ifndef LINUX_SOCKET_H_
#define LINUX_SOCKET_H_

#include <winsock2.h>

#include "../raw-socket.h"

class LinuxSocket : public RawSocket {
public:
	LinuxSocket(const sockaddr& bind_to);
	~LinuxSocket() override;
};

#endif 
#endif