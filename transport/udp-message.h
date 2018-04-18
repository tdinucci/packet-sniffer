#ifndef UDP_HEADER_H_
#define UDP_HEADER_H_

#include <cstdint>
#include <memory>
#include <vector>

using namespace std;

class UdpMessage {
 private:
  uint16_t source_port;
  uint16_t dest_port;
  uint16_t length;
  uint16_t checksum;

  shared_ptr<vector<uint8_t>> payload;

 public:
  explicit UdpMessage(shared_ptr<vector<uint8_t>> message);

  uint16_t get_source_port();
  uint16_t get_dest_port();
  uint16_t get_length();
  uint16_t get_checksum();

  shared_ptr<vector<uint8_t>> get_payload();

  void dump();
};

#endif