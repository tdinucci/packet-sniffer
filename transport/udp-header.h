#ifndef UDP_HEADER_H_
#define UDP_HEADER_H_

#include <cstdint>

class UdpHeader {
 private:
  uint16_t source_port;
  uint16_t dest_port;
  uint16_t length;
  uint16_t checksum;

 public:
  explicit UdpHeader(uint8_t* packet);

  uint16_t get_source_port();
  uint16_t get_dest_port();
  uint16_t get_length();
  uint16_t get_checksum();

  void dump();
};

#endif