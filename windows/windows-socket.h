#ifdef _WIN32

#ifndef WINDOWS_SOCKET_H_
#define WINDOWS_SOCKET_H_

#include <winsock2.h>

#include "../raw-socket.h"

namespace sniff {
class WindowsSocket : public RawSocket {
 public:
  WindowsSocket(const sockaddr& bind_to);
  ~WindowsSocket() override;
};
}  // namespace sniff

#endif
#endif