#ifndef TCP_SEGMENT_H_
#define TCP_SEGMENT_H_

#include <cstdint>
#include <memory>
#include <vector>

#include "../protocol.h"

using namespace std;

namespace sniff {
    class TcpSegment : public Protocol {
    private:
        uint16_t source_port;
        uint16_t dest_port;
        uint32_t sequence;
        uint32_t ack_sequence;
        uint8_t data_offset;

        uint8_t flag_cwr;
        uint8_t flag_ece;
        uint8_t flag_urg;
        uint8_t flag_ack;
        uint8_t flag_psh;
        uint8_t flag_rst;
        uint8_t flag_syn;
        uint8_t flag_fin;

        uint16_t window;
        uint16_t checksum;
        uint16_t urg_ptr;

        vector<uint8_t> payload;

    public:
        TcpSegment(vector<uint8_t>& segment);

        uint16_t get_source_port();
        uint16_t get_dest_port();
        uint32_t get_sequence();
        uint32_t get_ack_sequence();
        int8_t get_data_offset();

        uint8_t get_flag_cwr();
        uint8_t get_flag_ece();
        uint8_t get_flag_urg();
        uint8_t get_flag_ack();
        uint8_t get_flag_psh();
        uint8_t get_flag_rst();
        uint8_t get_flag_syn();
        uint8_t get_flag_fin();

        uint16_t get_window();
        uint16_t get_checksum();
        uint16_t get_urg_ptr();

        vector<uint8_t> get_payload();

        shared_ptr<Protocol> get_inner_protocol() override;
        string get_description() override;
    };
}  // namespace sniff

#endif