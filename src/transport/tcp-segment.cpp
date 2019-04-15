#include <sstream>
#include <stdexcept>

#include "../util.h"
#include "tcp-segment.h"

using namespace std;
using namespace sniff;

TcpSegment::TcpSegment(vector<uint8_t>& segment) {
    auto seg_iter = segment.begin();

    source_port = ntohs(seg_iter);
    dest_port = ntohs(seg_iter + 2);
    sequence = ntohi(seg_iter + 4);
    ack_sequence = ntohi(seg_iter + 8);
    data_offset = (segment.at(12) >> 4) * 4;  // this is count of 32 bit words

    auto flags = segment.at(13);
    flag_cwr = flags >> 7 & 0x01;
    flag_ece = flags >> 6 & 0x01;
    flag_urg = flags >> 5 & 0x01;
    flag_ack = flags >> 4 & 0x01;
    flag_psh = flags >> 3 & 0x01;
    flag_rst = flags >> 2 & 0x01;
    flag_syn = flags >> 1 & 0x01;
    flag_fin = flags & 0x01;

    window = ntohs(seg_iter + 14);
    checksum = ntohs(seg_iter + 16);
    urg_ptr = ntohs(seg_iter + 16);

    payload = vector<uint8_t>(seg_iter + data_offset, segment.end());
}

uint16_t TcpSegment::get_source_port() { return source_port; }

uint16_t TcpSegment::get_dest_port() { return dest_port; }

uint32_t TcpSegment::get_sequence() { return sequence; }

uint32_t TcpSegment::get_ack_sequence() { return ack_sequence; }

int8_t TcpSegment::get_data_offset() { return data_offset; }

uint8_t TcpSegment::get_flag_cwr() { return flag_cwr; }

uint8_t TcpSegment::get_flag_ece() { return flag_ece; }

uint8_t TcpSegment::get_flag_urg() { return flag_urg; }

uint8_t TcpSegment::get_flag_ack() { return flag_ack; }

uint8_t TcpSegment::get_flag_psh() { return flag_psh; }

uint8_t TcpSegment::get_flag_rst() { return flag_rst; }

uint8_t TcpSegment::get_flag_syn() { return flag_syn; }

uint8_t TcpSegment::get_flag_fin() { return flag_fin; }

uint16_t TcpSegment::get_window() { return window; }

uint16_t TcpSegment::get_checksum() { return checksum; }

uint16_t TcpSegment::get_urg_ptr() { return urg_ptr; }

vector<uint8_t> TcpSegment::get_payload() { return payload; }

shared_ptr<Protocol> TcpSegment::get_inner_protocol() { return nullptr; }

string TcpSegment::get_description() {
    stringstream desc_ss;

    desc_ss << "TCP Header" << endl;

    desc_ss << "\tSource Port: " << dec << (int) source_port << endl;
    desc_ss << "\tDestination Port: " << dec << (int) dest_port << endl;
    desc_ss << "\tSequence: " << dec << (uint32_t) sequence << endl;
    desc_ss << "\tACK Sequence: " << dec << (uint32_t) ack_sequence << endl;
    desc_ss << "\tData Offset: " << dec << (int) data_offset << endl;

    desc_ss << "\tFlags: "
            << "[SYN - " << (bool) flag_syn << "], "
            << "[ACK - " << (bool) flag_ack << "], "
            << "[PSH - " << (bool) flag_psh << "]"
            << "[FIN - " << (bool) flag_fin << "]" << endl;

    auto inner_protocol = get_inner_protocol();
    if (inner_protocol != nullptr)
        desc_ss << inner_protocol->get_description();
    else {
        for (auto& b : payload) desc_ss << (char) b;
        desc_ss << endl;
    }

    return desc_ss.str();
}