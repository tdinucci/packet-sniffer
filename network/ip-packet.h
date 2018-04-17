#ifndef IP_PACKET_H_
#define IP_PACKET_H_

#include <memory>
#include <vector>

#include "ip-header.h"

using namespace std;

class IpPacket {
private:

  unique_ptr<IpHeader> header;

};

#endif