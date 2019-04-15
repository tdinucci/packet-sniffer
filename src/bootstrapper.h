#ifndef BOOTSTRAPPER_H_
#define BOOTSTRAPPER_H_

#ifdef _WIN32
#include <winsock2.h>
#else

#include <sys/socket.h>

#endif

#include <memory>

#include "raw-socket.h"

using namespace std;

namespace sniff {
    class Bootstrapper {
    public:
        Bootstrapper() {}

        virtual ~Bootstrapper() {}

        virtual sockaddr_in get_network_iterface() = 0;
        virtual unique_ptr<RawSocket> get_socket(const sockaddr& bind_to) = 0;
    };
}  // namespace sniff

#endif