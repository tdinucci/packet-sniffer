#include <cstring>
#include <iostream>
#include <sstream>

#include "ip-header.h"
#include "util.h"

IpHeader::IpHeader(uint8_t* packet) {
  version = packet[0] >> 4;
  header_length = (packet[0] & 0x0f) * 4;  // this is count of 32 bit words

  dscp = packet[1];
  packet_length = ntohs(packet + 2);
  id = ntohs(packet + 4);
  fragment_offset = ntohs(packet + 6);
  ttl = packet[8];
  protocol = packet[9];
  checksum = ntohs(packet + 10);

  stringstream source_ss, dest_ss;
  int src_pack = 12;
  int dest_pack = 16;
  for (auto i = 0; i < 4; i++) {
    source_ss << (int)packet[src_pack + i];
    dest_ss << (int)packet[dest_pack + i];
    if (i < 3) {
      source_ss << ".";
      dest_ss << ".";
    }
  }

  source_ip = source_ss.str();
  dest_ip = dest_ss.str();
  ;
}

uint8_t IpHeader::get_version() { return version; }
uint8_t IpHeader::get_header_length() { return header_length; }
uint8_t IpHeader::get_dscp() { return dscp; }
uint16_t IpHeader::get_packet_length() { return packet_length; }
uint16_t IpHeader::get_id() { return id; }
uint16_t IpHeader::get_fragment_offset() { return fragment_offset; }
uint8_t IpHeader::get_ttl() { return ttl; }
uint8_t IpHeader::get_protocol() { return protocol; }
uint16_t IpHeader::get_checksum() { return checksum; }
string IpHeader::get_source_ip() { return source_ip; }
string IpHeader::get_dest_ip() { return dest_ip; }

void IpHeader::dump() {
  cout << "IP Header" << endl;
  cout << "\tVersion: " << dec << (int)version << endl;
  cout << "\tLength: " << dec << (int)header_length << endl;
  cout << "\tDSCP: 0x" << hex << (int)dscp << endl;
  cout << "\tPacket Length: " << dec << (int)packet_length << endl;
  cout << "\tIdentification: 0x" << hex << (int)id << endl;
  cout << "\tTime To Live: " << dec << (int)ttl << endl;
  cout << "\tProtocol: 0x" << hex << (int)protocol << endl;
  cout << "\tHeader Checksum: 0x" << hex << (int)checksum << endl;
  cout << "\tSource IP: " << source_ip << endl;
  cout << "\tDestination IP: " << dest_ip << endl;
}