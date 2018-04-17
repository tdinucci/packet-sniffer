#include <iostream>
#include <stdexcept>

#include "tcp-header.h"
#include "util.h"

using namespace std;

TcpHeader::TcpHeader(uint8_t* packet) {
  if (packet == nullptr) throw runtime_error("Supplied packet is NULL");

  source_port = ntohs(packet);
  dest_port = ntohs(packet + 2);
  sequence = ntohi(packet + 4);
  ack_sequence = ntohi(packet + 8);
  data_offset = (packet[12] >> 4) * 4;  // this is count of 32 bit words

  flag_cwr = packet[13] >> 7 & 0x01;
  flag_ece = packet[13] >> 6 & 0x01;
  flag_urg = packet[13] >> 5 & 0x01;
  flag_ack = packet[13] >> 4 & 0x01;
  flag_psh = packet[13] >> 3 & 0x01;
  flag_rst = packet[13] >> 2 & 0x01;
  flag_syn = packet[13] >> 1 & 0x01;
  flag_fin = packet[13] & 0x01;

  window = ntohs(packet + 14);
  checksum = ntohs(packet + 16);
  urg_ptr = ntohs(packet + 16);
}

uint16_t TcpHeader::get_source_port() { return source_port; }
uint16_t TcpHeader::get_dest_port() { return dest_port; }
uint32_t TcpHeader::get_sequence() { return sequence; }
uint32_t TcpHeader::get_ack_sequence() { return ack_sequence; }
int8_t TcpHeader::get_data_offset() { return data_offset; }

uint8_t TcpHeader::get_flag_cwr() { return flag_cwr; }
uint8_t TcpHeader::get_flag_ece() { return flag_ece; }
uint8_t TcpHeader::get_flag_urg() { return flag_urg; }
uint8_t TcpHeader::get_flag_ack() { return flag_ack; }
uint8_t TcpHeader::get_flag_psh() { return flag_psh; }
uint8_t TcpHeader::get_flag_rst() { return flag_rst; }
uint8_t TcpHeader::get_flag_syn() { return flag_syn; }
uint8_t TcpHeader::get_flag_fin() { return flag_fin; }

uint16_t TcpHeader::get_window() { return window; }
uint16_t TcpHeader::get_checksum() { return checksum; }
uint16_t TcpHeader::get_urg_ptr() { return urg_ptr; }

void TcpHeader::dump() {
  cout << "TCP Header" << endl;

  cout << "\tSource Port: " << dec << (int)source_port << endl;
  cout << "\tDestination Port: " << dec << (int)dest_port << endl;
  cout << "\tSequence: " << dec << (uint32_t)sequence << endl;
  cout << "\tACK Sequence: " << dec << (uint32_t)ack_sequence << endl;
  cout << "\tData Offset: " << dec << (int)data_offset << endl;

  cout << "\tFlags: "
       << "[SYN - " << (bool)flag_syn << "], "
       << "[ACK - " << (bool)flag_ack << "], "
       << "[PSH - " << (bool)flag_psh << "]"
       << "[FIN - " << (bool)flag_fin << "]" << endl;

  // if (data_len > 0) printf("\t|Data (%d):\n%s\n", data_len, data);
}