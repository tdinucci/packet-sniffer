#ifdef _WIN32
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")         // For winsock
#define SIO_RCVALL _WSAIOW(IOC_VENDOR, 1)  // this removes the need of mstcpip.h
#pragma warning(disable : 4996)

#else
#include <errno.h>
#include <linux/if_ether.h>
#include <sys/socket.h>
#endif

#include <cstdint>
#include <cstring>
#include <iostream>
#include <memory>
#include <valarray>
#include <vector>

#include "link/ethernet-frame.h"
#include "network/arp-packet.h"
#include "network/ip-packet.h"
#include "transport/tcp-segment.h"
#include "transport/udp-message.h"
#include "util.h"

using namespace std;

const int MAX_PACKET_SIZE = 65536;
const uint16_t PROTOCOL_ALL =
    0x0300;  // shifted for network order, actual value is 0x0003
const uint16_t PROTOCOL_IP =
    0x0008;  // shifted for network order, actual value is 0x0800

string get_last_error() { return strerror(errno); }

#ifdef _WIN32
string get_last_error() {
  int err = WSAGetLastError();
  char msg_buf[256];
  FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL, err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), msg_buf,
                sizeof(msg_buf), NULL);

  return string(msg_buf);
}

void winsock_init() {
  WSADATA wsa_data;
  int result;
  if (WSAStartup(MAKEWORD(1, 1), &wsa_data) != 0) {
    cout << "WSAStartup failed: " << get_last_error() << endl;
  }
}

void winsock_cleanup() { WSACleanup(); }

#endif

int socket_close(int sock) {
  int status = 0;

#ifdef _WIN32
  status = shutdown(sock, SD_BOTH);
  if (status == 0) {
    status = closesocket(sock);
  }
#else
  status = shutdown(sock, SHUT_RDWR);
  // if (status == 0) { status = close(sock); }
#endif

  return status;
}

#ifdef _WIN32

int get_winsock() {
  SOCKET sniffer;
  struct in_addr addr;
  struct sockaddr_in source, dest;
  int in;

  char hostname[100];
  struct hostent *local;
  WSADATA wsa;

  cout << "Initialising Winsock..." << endl;
  if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
    cout << "WSAStartup failed - " << get_last_error() << endl;
    return 1;
  }

  cout << "Creating RAW Socket..." << endl;
  sniffer = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
  if (sniffer == INVALID_SOCKET) {
    cout << "Failed to create raw socket - " << get_last_error() << endl;
    return 1;
  }

  if (gethostname(hostname, sizeof(hostname)) == SOCKET_ERROR) {
    cout << "Error getting hostname - " << get_last_error()) << endl;
    return 1;
  }
  cout << "Host name: " << hostname << endl;

  local = gethostbyname(hostname);
  cout << "Available Network Interfaces: << endl;
  if (local == NULL) {
    cout << "Error - " << get_last_error() << endl;
    return 1;
  }

  for (int i = 0; local->h_addr_list[i] != 0; ++i) {
    memcpy(&addr, local->h_addr_list[i], sizeof(struct in_addr));
    cout << "Interface Number: " << i << " Address: " << inet_ntoa(addr) << endl;
  }

  cout << "Enter the interface number: " << endl;
  cin >> in;

  memset(&dest, 0, sizeof(dest));
  memcpy(&dest.sin_addr.s_addr, local->h_addr_list[in],
         sizeof(dest.sin_addr.s_addr));
  dest.sin_family = AF_INET;
  dest.sin_port = 0;

  cout << "Binding" << endl;
  if (bind(sniffer, (struct sockaddr *)&dest, sizeof(dest)) == SOCKET_ERROR) {
    cout << "Bind failed - " << get_last_error() << endl;
    return 1;
  }

  int j = 1;
  if (WSAIoctl(sniffer, SIO_RCVALL, &j, sizeof(j), 0, 0, (LPDWORD)&in, 0, 0) ==
      SOCKET_ERROR) {
    cout << "WSAIoctl failed - " << get_last_error() << endl;
    return 1;
  }

  return sniffer;
}

#endif

int get_socket() {
#ifdef _WIN32
  return get_winsock();
#else
  int handle = socket(AF_PACKET, SOCK_RAW, PROTOCOL_ALL);
  if (handle < 0) {
    cout << "Failed to create socket: " << strerror(errno) << endl;
    return -1;
  }

  return handle;
#endif
}

int main() {
  int handle = get_socket();
  if (handle < 0) {
    return -1;
  }

  char *buffer = (char *)malloc(MAX_PACKET_SIZE);
  memset(buffer, 0, MAX_PACKET_SIZE);

  struct sockaddr saddr;
  socklen_t saddr_len = sizeof(saddr);

  while (1) {
    int buflen =
        recvfrom(handle, buffer, MAX_PACKET_SIZE, 0, &saddr, &saddr_len);
    if (buflen < 0) {
      cout << "Error reading from socket: " << get_last_error() << endl;

      // cout << "Error receiving packet: [#" << errno << "] - " //<<
      // strerror(errno)
      //	<< endl;
      return -1;
    }

    shared_ptr<vector<uint8_t>> packet = shared_ptr<vector<uint8_t>>(
        new vector<uint8_t>(buffer, buffer + buflen));

#ifdef _WIN32
    auto ip = unique_ptr<IpPacket>(new IpPacket(packet));
    // ip->dump();

    if (ip->get_protocol() == 0x11) {
      auto udp = unique_ptr<UdpMessage>(new UdpMessage(ip->get_payload()));
      ip->dump();
      udp->dump();
    }
      // else if (ip->get_protocol() == 6) {
      //	auto tcp = unique_ptr<TcpSegment>(new
      //TcpSegment(ip->get_payload())); 	if (/*tcp->get_dest_port() == 80
      //|| */tcp->get_source_port() == 80) { 		ip->dump();
      //		tcp->dump();
      //	}
      //}
#else
    auto eth = unique_ptr<EthernetFrame>(new EthernetFrame(packet));
    //eth->dump();

    if (eth->get_protcol() == ETH_ARP) {
      auto arp = unique_ptr<ArpPacket>(new ArpPacket(eth->get_payload()));
      cout << arp->get_description() << endl;
    }
    else if (eth->get_protcol() == ETH_IP4) {
       auto ip = unique_ptr<IpPacket>(new IpPacket(eth->get_payload()));

       if (ip->get_protocol() == 0x11) {
         auto udp = unique_ptr<UdpMessage>(new UdpMessage(ip->get_payload()));

         eth->dump();
         ip->dump();
         udp->dump();

       } else if (ip->get_protocol() == 6) {
         auto tcp = unique_ptr<TcpSegment>(new TcpSegment(ip->get_payload()));

         //if (tcp->get_dest_port() == 8080 || tcp->get_source_port() == 8080) {
           eth->dump();
           ip->dump();
           tcp->dump();
         //}
       }
     }
#endif
  }

  free(buffer);
  return 0;
}