#ifndef _WIN32

#ifndef LINUX_SOCKET_H_
#define LINUX_SOCKET_H_

#include <sys/socket.h>

#include "../raw-socket.h"

namespace sniff {
class LinuxSocket : public RawSocket {
 public:
  LinuxSocket(const sockaddr& bind_to);
  ~LinuxSocket() override;
};
}  // namespace sniff
#endif
#endif