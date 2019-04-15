#ifdef _WIN32

#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)

#include <iostream>

#include "../util.h"
#include "windows-bootstrapper.h"
#include "windows-socket.h"

using namespace sniff;

WindowsBootstrapper::WindowsBootstrapper() {
#ifdef _WIN32
  WSADATA wsa_data;
  if (WSAStartup(MAKEWORD(1, 1), &wsa_data) != 0) {
    throw runtime_error("WSAStartup failed");
  }
#endif
}

WindowsBootstrapper::~WindowsBootstrapper() {
#ifdef _WIN32
  WSACleanup();
#endif
}

sockaddr_in WindowsBootstrapper::get_network_iterface() {
  struct sockaddr_in dest;

#ifdef _WIN32
  struct hostent* local = gethostbyname("");
  if (local == nullptr)
    throw runtime_error(*get_last_error("Failed to get host name"));

  struct in_addr addr;
  int max_interface_id = -1;
  for (int i = 0; local->h_addr_list[i] != 0; ++i) {
    memcpy(&addr, local->h_addr_list[i], sizeof(struct in_addr));
    cout << "Interface: " << i << " [" << inet_ntoa(addr) << "] " << endl;
    max_interface_id++;
  }

  if (max_interface_id < 0) throw runtime_error("No network interfaces found");

  int selected_interface_id;
  do {
    cout << "Enter interface number: " << endl;
    cin >> selected_interface_id;

    if (selected_interface_id > max_interface_id)
      cout << "Invalid selection" << endl;

  } while (selected_interface_id < 0 ||
           selected_interface_id > max_interface_id);

  memset(&dest, 0, sizeof(dest));
  memcpy(&dest.sin_addr.s_addr, local->h_addr_list[selected_interface_id],
         sizeof(dest.sin_addr.s_addr));
  dest.sin_family = AF_INET;
  dest.sin_port = 0;
#endif

  return dest;
}

unique_ptr<RawSocket> WindowsBootstrapper::get_socket(const sockaddr& bind_to) {
  return make_unique<RawSocket>(bind_to);
}

#endif