#ifndef _WIN32

#include <iostream>
#include <vector>

#include "../util.h"
#include "linux-bootstrapper.h"
#include "linux-socket.h"

using namespace sniff;

sockaddr_in LinuxBootstrapper::get_network_iterface() {
  // just want to bind to all interfaces, this doesn't appear to be possible
  // with Windows which is the reason for this method
  struct sockaddr_in dest;
  dest.sin_port = 0;
  return dest;
}

unique_ptr<RawSocket> LinuxBootstrapper::get_socket(const sockaddr &bind_to) {
  return unique_ptr<LinuxSocket>(new LinuxSocket(bind_to));
}

#endif