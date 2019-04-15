#ifdef _WIN32
#include "windows/windows-bootstrapper.h"
#else

#include "linux/linux-bootstrapper.h"

#endif

#include <cstdint>
#include <cstring>
#include <iostream>
#include <memory>
#include <vector>

#include "bootstrapper.h"
#include "link/ethernet-frame.h"
#include "network/ip-packet.h"
#include "raw-socket.h"

using namespace std;
using namespace sniff;

unique_ptr<Bootstrapper> get_bootstrapper() {
    unique_ptr<Bootstrapper> bootstrapper;
#ifdef _WIN32
    bootstrapper = make_unique<WindowsBootstrapper>();
#else
    bootstrapper = make_unique<LinuxBootstrapper>();
#endif
    return bootstrapper;
}

int main() {
    try {
        auto bootstrapper = get_bootstrapper();
        // could have the bootstrapper return the socket in a single call but having
        // these things seperate is more flexible
        auto net_iface = bootstrapper->get_network_iterface();
        auto socket = bootstrapper->get_socket((sockaddr&) net_iface);

        while (1) {
            auto packet = socket->read();

#ifdef _WIN32
            auto ip = make_unique<IpPacket>(packet);
            cout << ip->get_description() << endl;
#else
            auto eth = make_unique<EthernetFrame>(packet);
            cout << eth->get_description() << endl;
#endif
        }
    } catch (const std::exception& e) {
        cout << "An error occurred (ensure running as root/admin): " << endl
             << e.what() << endl;
        return 1;
    }
}