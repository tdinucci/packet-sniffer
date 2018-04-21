#ifndef _WIN32

#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

#include "../util.h"
#include "linux-socket.h"

using namespace sniff;

const uint16_t PROTOCOL_ALL =
    0x0300;  // shifted for network order, actual value is 0x0003
const uint16_t PROTOCOL_IP =
    0x0008;  // shifted for network order, actual value is 0x0800

LinuxSocket::LinuxSocket(const sockaddr& bind_to) {
  // we're just going to bind to all interfaces
  handle = socket(AF_PACKET, SOCK_RAW, PROTOCOL_ALL);
  if ((int)handle < 0)
    throw runtime_error(*get_last_error("Failed to create socket"));
}

LinuxSocket::~LinuxSocket() {
  int status = shutdown(handle, SHUT_RDWR);
  if (status == 0) status = close(handle);
}

#endif