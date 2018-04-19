#ifndef ETHERNET_FRAME_H_
#define ETHERNET_FRAME_H_

#include <memory>
#include <string>
#include <vector>

#include "../protocol.h"

using namespace std;

#define ETH_IP4 0x0800
#define ETH_IP6 0x86dd
#define ETH_ARP 0x0806

class EthernetFrame : public Protocol {
 private:
  string dest;
  string source;
  uint16_t protocol;
  uint16_t length;

  shared_ptr<vector<uint8_t>> payload;
  shared_ptr<Protocol> inner_protocol;

 public:
  static string get_protocol_name(uint16_t code);

  explicit EthernetFrame(shared_ptr<vector<uint8_t>> frame);

  string get_dest();
  string get_source();
  uint16_t get_protcol();
  uint16_t get_length();
  
  shared_ptr<vector<uint8_t>> get_payload();

  shared_ptr<Protocol> get_inner_protocol() override;
  string get_description() override;
};

#endif