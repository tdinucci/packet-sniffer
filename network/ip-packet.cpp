#include <cstring>
#include <iostream>
#include <sstream>

#include "ip-packet.h"
#include "../util.h"

IpPacket::IpPacket(shared_ptr<vector<uint8_t>> packet) {
	auto pac_iter = packet->begin();

	// TODO: big endian machines?
	version = packet->at(0) >> 4;
	header_length = (packet->at(0) & 0x0f) * 4;  // this is count of 32 bit words

	dscp = packet->at(1);
	packet_length = ntohs(pac_iter + 2);
	id = ntohs(pac_iter + 4);
	fragment_offset = ntohs(pac_iter + 6);
	ttl = packet->at(8);
	protocol = packet->at(9);
	checksum = ntohs(pac_iter + 10);

	stringstream source_ss, dest_ss;
	int src_pack = 12;
	int dest_pack = 16;
	for (auto i = 0; i < 4; i++) {
		source_ss << (int)packet->at(src_pack + i);
		dest_ss << (int)packet->at(dest_pack + i);
		if (i < 3) {
			source_ss << ".";
			dest_ss << ".";
		}
	}

	source_ip = source_ss.str();
	dest_ip = dest_ss.str();

	payload = shared_ptr<vector<uint8_t>>(
		new vector<uint8_t>(pac_iter + header_length, packet->end()));
}

uint8_t IpPacket::get_version() { return version; }
uint8_t IpPacket::get_header_length() { return header_length; }
uint8_t IpPacket::get_dscp() { return dscp; }
uint16_t IpPacket::get_packet_length() { return packet_length; }
uint16_t IpPacket::get_id() { return id; }
uint16_t IpPacket::get_fragment_offset() { return fragment_offset; }
uint8_t IpPacket::get_ttl() { return ttl; }
uint8_t IpPacket::get_protocol() { return protocol; }
uint16_t IpPacket::get_checksum() { return checksum; }
string IpPacket::get_source_ip() { return source_ip; }
string IpPacket::get_dest_ip() { return dest_ip; }
shared_ptr<vector<uint8_t>> IpPacket::get_payload() { return payload; }

void IpPacket::dump() {
  cout << "IP Header" << endl;
  cout << "\tVersion: " << dec << (int)version << endl;
  cout << "\tLength: " << dec << (int)header_length << endl;
  cout << "\tDSCP: 0x" << hex << (int)dscp << endl;
  cout << "\tPacket Length: " << dec << (int)packet_length << endl;
  cout << "\tIdentification: 0x" << hex << (int)id << endl;
  cout << "\tTime To Live: " << dec << (int)ttl << endl;
  cout << "\tProtocol: 0x" << hex << (int)protocol << endl;
  cout << "\tHeader Checksum: 0x" << hex << (int)checksum << endl;
  cout << "\tSource IP: " << source_ip << endl;
  cout << "\tDestination IP: " << dest_ip << endl;
}