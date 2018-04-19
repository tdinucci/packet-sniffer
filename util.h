#ifndef SNIFF_UTIL_H_ 
#define SNIFF_UTIL_H_

#include <cstdint>
#include <string>
#include <vector>

using namespace std;

uint16_t ntohs(uint8_t network_short[2]);
uint16_t ntohs(vector<uint8_t>::iterator iter);

uint32_t ntohi(uint8_t network_int[4]);
uint32_t ntohi(vector<uint8_t>::iterator iter);

unique_ptr<string> get_last_error(const string prefix);

#endif