#ifndef ETHERNET_PARSER_H_
#define ETHERNET_PARSER_H_

#include <memory>
#include <vector>
#include <cstdint>

#include "ethernet-frame.h"

using namespace std;

class EthernetParser {
public:
  EthernetParser(unique_ptr<vector<uint8_t>> packet);

  
};

#endif