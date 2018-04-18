#ifndef ARP_HEADER_H_
#define ARP_HEADER_H_

#include <vector>
#include <cstdint>
#include <string>
#include "../packet.h"

using namespace std;

class ArpPacket : public Packet {
 private:
  uint16_t hardware_type;
  uint16_t protocol_type;
  uint8_t hardware_addr_len;
  uint8_t protocol_addr_len;
  uint16_t operation;
  string sender_hardware_addr;
  string sender_protocol_addr;
  string target_hardware_addr;
  string target_protocol_addr;

 public:
  explicit ArpPacket(shared_ptr<vector<uint8_t>> packet);

  uint16_t get_hardware_type();
  uint16_t get_protocol_type();
  uint8_t get_hardware_addr_len();
  uint8_t get_protocol_addr_len();
  uint16_t get_operation();
  string get_sender_hardware_addr();
  string get_sender_protocol_addr();
  string get_target_hardware_addr();
  string get_target_protocol_addr();

  string get_description() override;
};

#endif