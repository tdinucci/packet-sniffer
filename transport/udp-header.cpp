#include <cstdint>
#include <iostream>

#include "udp-header.h"
#include "util.h"

using namespace std;

UdpHeader::UdpHeader(uint8_t* packet) {
  source_port = ntohs(packet);
  dest_port = ntohs(packet + 2);
  length = ntohs(packet + 4);
  checksum = ntohs(packet + 6);
}

uint16_t UdpHeader::get_source_port() { return source_port; }

uint16_t UdpHeader::get_dest_port() { return dest_port; }

uint16_t UdpHeader::get_length() { return length; }

uint16_t UdpHeader::get_checksum() { return checksum; }

void UdpHeader::dump() {
  cout << "UDP Header" << endl;
  cout << "\tSource Port: " << dec << (int)source_port << endl;
  cout << "\tDestination Port: " << dec << (int)dest_port << endl;
  cout << "\tLength:" << dec << (int)length << endl;
}