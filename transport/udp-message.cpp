#include <cstdint>
#include <iostream>

#include "udp-message.h"
#include "../util.h"

using namespace std;

UdpMessage::UdpMessage(shared_ptr<vector<uint8_t>> message) {
	auto msg_iter = message->begin();

	source_port = ntohs(msg_iter);
	dest_port = ntohs(msg_iter + 2);
	length = ntohs(msg_iter + 4);
	checksum = ntohs(msg_iter + 6);

	payload = shared_ptr<vector<uint8_t>>(new vector<uint8_t>(msg_iter + 8, message->end()));
}

uint16_t UdpMessage::get_source_port() { return source_port; }

uint16_t UdpMessage::get_dest_port() { return dest_port; }

uint16_t UdpMessage::get_length() { return length; }

uint16_t UdpMessage::get_checksum() { return checksum; }

shared_ptr<vector<uint8_t>> UdpMessage::get_payload() { return payload; }

void UdpMessage::dump() {
	cout << "UDP Header" << endl;
	cout << "\tSource Port: " << dec << (int)source_port << endl;
	cout << "\tDestination Port: " << dec << (int)dest_port << endl;
	cout << "\tLength:" << dec << (int)length << endl;

	for (auto b : *payload)
		cout << (char)b;

	cout << endl;
}