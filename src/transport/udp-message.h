#ifndef UDP_MESSAGE_H_
#define UDP_MESSAGE_H_

#include <cstdint>
#include <memory>
#include <vector>

#include "../protocol.h"

using namespace std;

namespace sniff {
    class UdpMessage : public Protocol {
    private:
        uint16_t source_port;
        uint16_t dest_port;
        uint16_t length;
        uint16_t checksum;

        vector<uint8_t> payload;

    public:
        explicit UdpMessage(vector<uint8_t>& message);

        uint16_t get_source_port();
        uint16_t get_dest_port();
        uint16_t get_length();
        uint16_t get_checksum();

        vector<uint8_t> get_payload();

        shared_ptr<Protocol> get_inner_protocol() override;
        string get_description() override;
    };
}  // namespace sniff

#endif