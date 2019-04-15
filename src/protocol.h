#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include <string>
#include <memory>

using namespace std;

namespace sniff {
    class Protocol {
    public:
        virtual shared_ptr<Protocol> get_inner_protocol() = 0;
        virtual string get_description() = 0;
    };
}  // namespace sniff

#endif
