#ifndef RAW_SOCKET_H_
#define RAW_SOCKET_H_

#include <cstdint>
#include <memory>
#include <vector>

using namespace std;

class RawSocket {
private:
	static const int MAX_PACKET_SIZE = 65536;

protected:
	uint64_t handle;

public:
	virtual ~RawSocket() = 0;

	shared_ptr<vector<uint8_t>> read();
};

#endif
