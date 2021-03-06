#include <cstdint>
#include <sstream>
#include <stdexcept>

#include "../util.h"
#include "udp-message.h"

using namespace std;
using namespace sniff;

UdpMessage::UdpMessage(vector<uint8_t>& message) {
    auto msg_iter = message.begin();

    source_port = ntohs(msg_iter);
    dest_port = ntohs(msg_iter + 2);
    length = ntohs(msg_iter + 4);
    checksum = ntohs(msg_iter + 6);

    payload = vector<uint8_t>(msg_iter + 8, message.end());
}

uint16_t UdpMessage::get_source_port() { return source_port; }

uint16_t UdpMessage::get_dest_port() { return dest_port; }

uint16_t UdpMessage::get_length() { return length; }

uint16_t UdpMessage::get_checksum() { return checksum; }

vector<uint8_t> UdpMessage::get_payload() { return payload; }

shared_ptr<Protocol> UdpMessage::get_inner_protocol() { return nullptr; }

string UdpMessage::get_description() {
    stringstream desc_ss;

    desc_ss << "UDP Header" << endl;
    desc_ss << "\tSource Port: " << dec << (int) source_port << endl;
    desc_ss << "\tDestination Port: " << dec << (int) dest_port << endl;
    desc_ss << "\tLength:" << dec << (int) length << endl;

    auto inner_protocol = get_inner_protocol();
    if (inner_protocol != nullptr)
        desc_ss << inner_protocol->get_description();
    else {
        for (auto& b : payload) desc_ss << (char) b;
        desc_ss << endl;
    }

    return desc_ss.str();
}