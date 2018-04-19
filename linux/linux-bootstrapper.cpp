#ifndef _WIN32

#include <iostream>

#include "linux-bootstrapper.h"
//#include "linux-socket.h"
#include "../util.h"

sockaddr_in LinuxBootstrapper::get_network_iterface()
{
	throw runtime_error("Not implemented");
	struct sockaddr_in dest;
	return dest;
}

unique_ptr<RawSocket> LinuxBootstrapper::get_socket(const sockaddr& bind_to)
{
	return unique_ptr<RawSocket>();
}

#endif