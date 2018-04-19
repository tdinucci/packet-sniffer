#ifdef _WIN32

#ifndef WINDOWS_BOOTSTRAPPER_H_
#define WINDOWS_BOOTSTRAPPER_H_

#include "../bootstrapper.h"

class WindowsBootstrapper : public Bootstrapper {
public:
	WindowsBootstrapper();
	virtual ~WindowsBootstrapper();

	sockaddr_in get_network_iterface() override;
	unique_ptr<RawSocket> get_socket(const sockaddr& bind_to) override;
};

#endif 
#endif