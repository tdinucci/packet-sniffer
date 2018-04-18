#ifndef HTTP_MESSAGE_H_
#define HTTP_MESSAGE_H_

#include <cstdint>
#include <memory>
#include <vector>
#include <string>

using namespace std;

class HttpMessage {
private:
	string object;
	shared_ptr<string> headers;
	shared_ptr<string> body;

public:
	HttpMessage(shared_ptr<vector<uint8_t>> message);
};

#endif 

