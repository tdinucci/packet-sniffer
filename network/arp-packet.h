#ifndef ARP_PACKET_H_
#define ARP_PACKET_H_

#include <cstdint>
#include <string>
#include <vector>
#include "../protocol.h"

using namespace std;

namespace sniff {
class ArpPacket : public Protocol {
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

  shared_ptr<Protocol> get_inner_protocol() override;
  string get_description() override;
};
}  // namespace sniff
#endif