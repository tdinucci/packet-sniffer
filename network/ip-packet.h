#ifndef IP_PACKET_H_
#define IP_PACKET_H_

#include <memory>
#include <string>

#include "../protocol.h"
#include "../util.h"

#define IP_UDP 0x11
#define IP_TCP 0x06

using namespace std;

namespace sniff {
class IpPacket : public Protocol {
 private:
  uint8_t version;
  uint8_t header_length;
  uint8_t dscp;
  uint16_t packet_length;
  uint16_t id;
  uint16_t fragment_offset;
  uint8_t ttl;
  uint8_t protocol;
  uint16_t checksum;
  string source_ip;
  string dest_ip;

  shared_ptr<vector<uint8_t>> payload;
  shared_ptr<Protocol> inner_protocol;

 public:
  explicit IpPacket(shared_ptr<vector<uint8_t>> packet);

  uint8_t get_version();
  uint8_t get_header_length();
  uint8_t get_dscp();
  uint16_t get_packet_length();
  uint16_t get_id();
  uint16_t get_fragment_offset();
  uint8_t get_ttl();
  uint8_t get_protocol();
  uint16_t get_checksum();
  string get_source_ip();
  string get_dest_ip();

  shared_ptr<vector<uint8_t>> get_payload();

  shared_ptr<Protocol> get_inner_protocol() override;
  string get_description() override;
};
}  // namespace sniff
#endif