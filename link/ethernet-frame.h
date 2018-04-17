#ifndef ETHERNET_FRAME_H_
#define ETHERNET_FRAME_H_

#include <memory>
#include <string>
#include <vector>

using namespace std;

#define ETH_IP4 0x0800
#define ETH_IP6 0x86dd
#define ETH_ARP 0x0806

class EthernetFrame {
 private:
  string dest;
  string source;
  uint16_t protocol;
  uint16_t length;

  shared_ptr<vector<uint8_t>> payload;

 public:
  static string get_protocol_description(uint16_t code);

  explicit EthernetFrame(unique_ptr<vector<uint8_t>> packet);

  string get_dest();
  string get_source();
  uint16_t get_protcol();
  uint8_t get_length();
  shared_ptr<vector<uint8_t>> get_payload();

  void dump();
};

#endif