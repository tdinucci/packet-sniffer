#include <stdexcept>
#include <sstream>
#include <tuple>

#include "../link/ethernet-frame.h"
#include "../util.h"
#include "arp-packet.h"

tuple<string, string> get_hardware_addresses(shared_ptr<vector<uint8_t>> packet,
                                             uint8_t addr_len);
tuple<string, string> get_software_addresses(shared_ptr<vector<uint8_t>> packet,
                                             uint8_t addr_len);

ArpPacket::ArpPacket(shared_ptr<vector<uint8_t>> packet) {
  if (packet == nullptr) throw runtime_error("Supplied ARP packet was null");
	
  auto piter = packet->begin();

  hardware_type = ntohs(piter);
  protocol_type = ntohs(piter + 2);
  hardware_addr_len = packet->at(4);
  protocol_addr_len = packet->at(5);
  operation = ntohs(piter + 6);

  auto hardware_addrs = get_hardware_addresses(packet, hardware_addr_len);
  sender_hardware_addr = get<0>(hardware_addrs);
  target_hardware_addr = get<1>(hardware_addrs);

  auto software_addrs = get_software_addresses(packet, protocol_addr_len);
  sender_protocol_addr = get<0>(software_addrs);
  target_protocol_addr = get<1>(software_addrs);
}

uint16_t ArpPacket::get_hardware_type() { return hardware_type; }
uint16_t ArpPacket::get_protocol_type() { return protocol_type; }
uint8_t ArpPacket::get_hardware_addr_len() { return hardware_addr_len; }
uint8_t ArpPacket::get_protocol_addr_len() { return protocol_addr_len; }
uint16_t ArpPacket::get_operation() { return operation; }
string ArpPacket::get_sender_hardware_addr() { return sender_hardware_addr; }
string ArpPacket::get_sender_protocol_addr() { return sender_protocol_addr; }
string ArpPacket::get_target_hardware_addr() { return target_hardware_addr; }
string ArpPacket::get_target_protocol_addr() { return target_protocol_addr; }

shared_ptr<Protocol> ArpPacket::get_inner_protocol() {
	return nullptr;
}

string ArpPacket::get_description() {
  stringstream result_ss;
  result_ss << "ARP Packet" << endl;

  auto operation_desc = operation == 1
                            ? " [Request]"
                            : operation == 2 ? " [Response]" : " [UNKNOWN]";
  result_ss << "\tOperation: 0x" << hex << (int)operation << operation_desc
            << endl;

  auto hardware_desc = hardware_type == 1 ? " [Ethernet]" : "";
  result_ss << "\tHardware Type: 0x" << hex << (int)hardware_type
            << hardware_desc << endl;

  auto protocol_desc = EthernetFrame::get_protocol_name(protocol_type);
  result_ss << "\tProtocol Type: 0x" << hex << (int)protocol_type << " ["
            << protocol_desc << "]" << endl;

  result_ss << "\tSender Hardware: " << sender_hardware_addr << endl;
  result_ss << "\tSender Protocol: " << sender_protocol_addr << endl;
  result_ss << "\tTarget Hardware: " << target_hardware_addr << endl;
  result_ss << "\tTarget Protocol: " << target_protocol_addr << endl;

  return result_ss.str();
}

tuple<string, string> get_hardware_addresses(shared_ptr<vector<uint8_t>> packet,
                                             uint8_t addr_len) {
  const uint8_t sender_hrd_off = 8;
  const uint8_t target_hrd_off = 18;

  stringstream s_hrd_ss, t_hrd_ss;
  for (auto i = 0; i < addr_len; i++) {
    s_hrd_ss << hex << (int)packet->at(sender_hrd_off + i);
    t_hrd_ss << hex << (int)packet->at(target_hrd_off + i);

    if (i < addr_len - 1) {
      s_hrd_ss << ":";
      t_hrd_ss << ":";
    }
  }

  return make_tuple(s_hrd_ss.str(), t_hrd_ss.str());
}

tuple<string, string> get_software_addresses(shared_ptr<vector<uint8_t>> packet,
                                             uint8_t addr_len) {
  const uint8_t sender_prt_off = 14;
  const uint8_t target_prt_off = 24;

  stringstream s_prt_ss, t_prt_ss;
  for (auto i = 0; i < addr_len; i++) {
    s_prt_ss << (int)packet->at(sender_prt_off + i);
    t_prt_ss << (int)packet->at(target_prt_off + i);

    if (i < addr_len - 1) {
      s_prt_ss << ".";
      t_prt_ss << ".";
    }
  }

  return make_tuple(s_prt_ss.str(), t_prt_ss.str());
}