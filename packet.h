#ifndef PACKET_H_
#define PACKET_H_

#include <cstdint>
#include <memory>
#include <vector>
#include <string>

using namespace std;

class Packet {
 private:
  uint16_t size;

 public:
  uint16_t get_size() { return size; }
  virtual string get_description() = 0;
};

#endif