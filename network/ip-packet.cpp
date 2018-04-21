#include <cstring>
#include <sstream>
#include <stdexcept>

#include "../transport/tcp-segment.h"
#include "../transport/udp-message.h"
#include "../util.h"
#include "ip-packet.h"

using namespace sniff;

IpPacket::IpPacket(shared_ptr<vector<uint8_t>> packet) {
  if (packet == nullptr) throw runtime_error("Supplied IP packet was null");

  auto pac_iter = packet->begin();

  // TODO: big endian machines?
  version = packet->at(0) >> 4;
  header_length = (packet->at(0) & 0x0f) * 4;  // this is count of 32 bit words

  dscp = packet->at(1);
  packet_length = ntohs(pac_iter + 2);
  id = ntohs(pac_iter + 4);
  fragment_offset = ntohs(pac_iter + 6);
  ttl = packet->at(8);
  protocol = packet->at(9);
  checksum = ntohs(pac_iter + 10);

  stringstream source_ss, dest_ss;
  int src_pack = 12;
  int dest_pack = 16;
  for (auto i = 0; i < 4; i++) {
    source_ss << (int)packet->at(src_pack + i);
    dest_ss << (int)packet->at(dest_pack + i);
    if (i < 3) {
      source_ss << ".";
      dest_ss << ".";
    }
  }

  source_ip = source_ss.str();
  dest_ip = dest_ss.str();

  payload = shared_ptr<vector<uint8_t>>(
      new vector<uint8_t>(pac_iter + header_length, packet->end()));
}

uint8_t IpPacket::get_version() { return version; }
uint8_t IpPacket::get_header_length() { return header_length; }
uint8_t IpPacket::get_dscp() { return dscp; }
uint16_t IpPacket::get_packet_length() { return packet_length; }
uint16_t IpPacket::get_id() { return id; }
uint16_t IpPacket::get_fragment_offset() { return fragment_offset; }
uint8_t IpPacket::get_ttl() { return ttl; }
uint8_t IpPacket::get_protocol() { return protocol; }
uint16_t IpPacket::get_checksum() { return checksum; }
string IpPacket::get_source_ip() { return source_ip; }
string IpPacket::get_dest_ip() { return dest_ip; }
shared_ptr<vector<uint8_t>> IpPacket::get_payload() { return payload; }

shared_ptr<Protocol> IpPacket::get_inner_protocol() {
  if (inner_protocol == nullptr) {
    if (protocol == IP_UDP)
      inner_protocol = shared_ptr<UdpMessage>(new UdpMessage(payload));
    else if (protocol == IP_TCP)
      inner_protocol = shared_ptr<TcpSegment>(new TcpSegment(payload));
  }

  return inner_protocol;
}

string IpPacket::get_description() {
  stringstream desc_ss;
  desc_ss << "IP Header" << endl;
  desc_ss << "\tVersion: " << dec << (int)version << endl;
  desc_ss << "\tLength: " << dec << (int)header_length << endl;
  desc_ss << "\tDSCP: 0x" << hex << (int)dscp << endl;
  desc_ss << "\tPacket Length: " << dec << (int)packet_length << endl;
  desc_ss << "\tIdentification: 0x" << hex << (int)id << endl;
  desc_ss << "\tTime To Live: " << dec << (int)ttl << endl;
  desc_ss << "\tProtocol: 0x" << hex << (int)protocol << endl;
  desc_ss << "\tHeader Checksum: 0x" << hex << (int)checksum << endl;
  desc_ss << "\tSource IP: " << source_ip << endl;
  desc_ss << "\tDestination IP: " << dest_ip << endl;

  auto inner_protocol = get_inner_protocol();
  if (inner_protocol != nullptr)
    desc_ss << inner_protocol->get_description();
  else {
    for (auto b : *payload) desc_ss << hex << (int)b;
    desc_ss << endl;
  }

  return desc_ss.str();
}