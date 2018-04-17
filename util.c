#include "util.h"

uint16_t ntohs(uint8_t network_short[2]) {
  return network_short[1] | network_short[0] << 8;
}

uint16_t ntohs(vector<uint8_t>::iterator iter) {
  return *(iter + 1) | *iter << 8;
}

uint32_t ntohi(uint8_t network_int[4]) {
  return network_int[3] << 0 | network_int[2] << 8 | network_int[1] << 16 |
         network_int[0] << 24;
}

uint32_t ntohl(vector<uint8_t>::iterator iter) {
  return *(iter + 3) << 0 | *(iter + 2) << 8 | *(iter + 1) << 16 | *iter << 24;
}