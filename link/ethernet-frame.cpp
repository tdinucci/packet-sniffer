#include <stdexcept>
#include <sstream>

#include "ethernet-frame.h"
#include "../network/arp-packet.h"
#include "../network/ip-packet.h"
#include "../util.h"

EthernetFrame::EthernetFrame(shared_ptr<vector<uint8_t>> frame) {
  if (frame == nullptr) throw runtime_error("Supplied Ethernet frame was null");

  auto frame_iter = frame->begin();

  auto raw_src = frame_iter;
  auto raw_dest = frame_iter + 6;
  auto raw_protocol = frame_iter + 12;

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
      new vector<uint8_t>(frame_iter + length, frame->end()));
}

string EthernetFrame::get_dest() { return dest; }

string EthernetFrame::get_source() { return source; }

uint16_t EthernetFrame::get_protcol() { return protocol; }

uint16_t EthernetFrame::get_length() { return length; }

shared_ptr<vector<uint8_t>> EthernetFrame::get_payload() { return payload; }

shared_ptr<Protocol> EthernetFrame::get_inner_protocol() {
	if (inner_protocol == nullptr) {
		if (protocol == ETH_ARP)
			inner_protocol = shared_ptr<ArpPacket>(new ArpPacket(payload));
		else if (protocol == ETH_IP4)
			inner_protocol = shared_ptr<IpPacket>(new IpPacket(payload));
	}

	return inner_protocol;
}

string EthernetFrame::get_description() {
	stringstream desc_ss;

	desc_ss << "Ethernet" << endl;
	desc_ss << "\tSource: " << source << endl;
	desc_ss << "\tDestination: " << dest << endl;
	desc_ss << "\tProtocol: 0x" << hex << protocol << " ["
		<< get_protocol_name(protocol) << "]" << endl;
	desc_ss << "\tLength: " << dec << (int)length << endl;

	auto inner_protocol = get_inner_protocol();
	if (inner_protocol != nullptr)
		desc_ss << inner_protocol->get_description();
	else {
		for (auto b : *payload)
			desc_ss << hex << (int)b;
		desc_ss << endl;
	}

	return desc_ss.str();
}

string EthernetFrame::get_protocol_name(uint16_t code) {
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