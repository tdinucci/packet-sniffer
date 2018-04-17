#include <errno.h>
#include <linux/if_ether.h>
#include <sys/socket.h>

#include <cstdint>
#include <cstring>
#include <iostream>
#include <memory>
#include <valarray>
#include <vector>

#include "link/ethernet-frame.h"
#include "network/arp-packet.h"
#include "util.h"

using namespace std;

const size_t MAX_PACKET_SIZE = 65536;
const uint16_t PROTOCOL_ALL =
    0x0300;  // shifted for network order, actual value is 0x0003
const uint16_t PROTOCOL_IP =
    0x0008;  // shifted for network order, actual value is 0x0800

int main() {
  int handle = socket(AF_PACKET, SOCK_RAW, PROTOCOL_ALL);
  if (handle < 0) {
    cout << "Failed to connect to socket: [#" << errno << "] - "
         << strerror(errno) << endl;
    return -1;
  }

  uint8_t *buffer = (uint8_t *)malloc(MAX_PACKET_SIZE);
  memset(buffer, 0, MAX_PACKET_SIZE);

  struct sockaddr saddr;
  int saddr_len = sizeof(saddr);

  while (1) {
    size_t buflen = recvfrom(handle, buffer, MAX_PACKET_SIZE, 0, &saddr,
                             (socklen_t *)&saddr_len);
    if (buflen < 0) {
      cout << "Error receiving packet: [#" << errno << "] - " << strerror(errno)
           << endl;
      return -1;
    }

    unique_ptr<vector<uint8_t>> packet = unique_ptr<vector<uint8_t>>(
        new vector<uint8_t>(buffer, buffer + buflen));
    auto eth = unique_ptr<EthernetFrame>(new EthernetFrame(move(packet)));
    eth->dump();

    if (eth->get_protcol() == ETH_ARP) {
      auto arp = unique_ptr<ArpPacket>(new ArpPacket(eth->get_payload()));
      cout << arp->get_description() << endl;
    }
    // else if (eth->get_protcol() == ETH_IP4) {
    //   auto ip = unique_ptr<IpHeader>(new IpHeader(packet +
    //   eth->get_length()));

    //   if (ip->get_protocol() == 0x11) {
    //     auto udp = unique_ptr<UdpHeader>(new UdpHeader(
    //         packet + eth->get_length() + ip->get_header_length()));

    //     eth->dump();
    //     ip->dump();
    //     udp->dump();

    //   } else if (ip->get_protocol() == 6) {
    //     auto tcp = unique_ptr<TcpHeader>(new TcpHeader(
    //         packet + eth->get_length() + ip->get_header_length()));

    //     if (tcp->get_dest_port() == 8080 || tcp->get_source_port() == 8080) {
    //       eth->dump();
    //       ip->dump();
    //       tcp->dump();
    //     }
    //   }
    // }
  }

  free(buffer);
  return 0;
}