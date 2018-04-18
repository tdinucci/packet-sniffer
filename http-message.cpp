#include "http-message.h"

HttpMessage::HttpMessage(shared_ptr<vector<uint8_t>> message) {
	if (message == nullptr) throw runtime_error("Supplied message is NULL");
}