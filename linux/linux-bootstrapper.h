#ifndef _WIN32

#ifndef LINUX_BOOTSTRAPPER_H_
#define LINUX_BOOTSTRAPPER_H_

#include <netinet/in.h>

#include "../bootstrapper.h"

namespace sniff {
class LinuxBootstrapper : public Bootstrapper {
 public:
  sockaddr_in get_network_iterface() override;
  unique_ptr<RawSocket> get_socket(const sockaddr& bind_to) override;
};
}  // namespace sniff
#endif
#endif