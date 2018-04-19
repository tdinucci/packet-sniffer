#ifdef _WIN32
#include "windows/windows-bootstrapper.h"
#else
#include "linux/linux-bootstrapper.h"
#endif

#include <cstdint>
#include <csignal>
#include <cstring>
#include <iostream>
#include <memory>
#include <vector>

#include "bootstrapper.h"
#include "link/ethernet-frame.h"
#include "network/ip-packet.h"
#include "raw-socket.h"

using namespace std;

unique_ptr<Bootstrapper> get_bootstrapper() {
	unique_ptr<Bootstrapper> bootstrapper;
#ifdef _WIN32
	bootstrapper = unique_ptr<Bootstrapper>(new WindowsBootstrapper());
#else
	bootstrapper = unique_ptr<Bootstrapper>(new LinuxBootstrapper());
#endif 
	return bootstrapper;
}

int main() {
	auto bootstrapper = get_bootstrapper();
	// could have the bootstrapper return the socket in a single call but having these things seperate is more flexible
	auto net_iface = bootstrapper->get_network_iterface();
	auto socket = bootstrapper->get_socket((sockaddr&)net_iface);

	while (1) {
		auto packet = socket->read();

#ifdef _WIN32
		auto ip = unique_ptr<IpPacket>(new IpPacket(packet));
		cout << ip->get_description() << endl;
#else
		auto eth = unique_ptr<EthernetFrame>(new EthernetFrame(packet));
		cout << eth->get_description() << endl;
#endif  
	}

	return 0;
}