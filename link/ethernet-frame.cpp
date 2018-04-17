#include <iostream>
#include <sstream>
#include <valarray>

#include "../util.h"
#include "ethernet-frame.h"

EthernetFrame::EthernetFrame(unique_ptr<vector<uint8_t>> packet) {
  auto piter = packet->begin();

  auto raw_src = piter;
  auto raw_dest = piter + 6;
  auto raw_protocol = piter + 12;

  stringstream dest_ss, source_ss;
  for (auto i = 0; i < 6; i++) {
    dest_ss << hex << (int)raw_src[i];
    source_ss << hex << (int)raw_dest[i];

    if (i < 5) {
      dest_ss << ":";
      source_ss << ":";
    }
  }

  dest = dest_ss.str();
  source = source_ss.str();

  protocol = ntohs(raw_protocol);
  length = 14;  // TODO: need to account for 802.1Q

  payload = shared_ptr<vector<uint8_t>>(
      new vector<uint8_t>(piter + length, packet->end()));
}

string EthernetFrame::get_dest() { return dest; }

string EthernetFrame::get_source() { return source; }

uint16_t EthernetFrame::get_protcol() { return protocol; }

uint8_t EthernetFrame::get_length() { return length; }

shared_ptr<vector<uint8_t>> EthernetFrame::get_payload() { return payload; }

void EthernetFrame::dump() {
  cout << "Ethernet" << endl;
  cout << "\tSource: " << source << endl;
  cout << "\tDestination: " << dest << endl;
  cout << "\tProtocol: 0x" << hex << protocol << " ["
       << get_protocol_description(protocol) << "]" << endl;
  cout << "\tLength: " << dec << (int)length << endl;
}

string EthernetFrame::get_protocol_description(uint16_t code) {
  switch (code) {
    case ETH_IP4:
      return "IPv4";
    case ETH_IP6:
      return "IPv6";
    case ETH_ARP:
      return "ARP";
    default:
      return "";
  }
}