#ifdef _WIN32

#include "windows-socket.h"
#include "../util.h"

using namespace sniff;

#define SIO_RCVALL _WSAIOW(IOC_VENDOR, 1)

WindowsSocket::WindowsSocket(const sockaddr& bind_to) {
  handle = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
  if (handle == INVALID_SOCKET) {
    throw runtime_error(*get_last_error("Failed to create socket"));
  }

  if (bind(handle, &bind_to, sizeof(bind_to)) == SOCKET_ERROR) {
    throw runtime_error(*get_last_error("Bind failed"));
  }

  int j = 1;
  int k = 0;
  if (WSAIoctl(handle, SIO_RCVALL, &j, sizeof(j), 0, 0, (LPDWORD)&k, 0, 0) ==
      SOCKET_ERROR) {
    throw runtime_error(*get_last_error("WSAIoctl failed"));
  }
}

WindowsSocket::~WindowsSocket() {
  int status = shutdown(handle, SD_BOTH);
  if (status == 0) status = closesocket(handle);
}

#endif