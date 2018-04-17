#ifndef IP_HEADER_H_
#define IP_HEADER_H_

#include <string>

#include "util.h"

using namespace std;

class IpHeader {
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

 public:
  explicit IpHeader(uint8_t* packet);

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

  void dump();
};

#endif