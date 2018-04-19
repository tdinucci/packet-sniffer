#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include<string>

using namespace std;

class Protocol {
public:
	virtual shared_ptr<Protocol> get_inner_protocol() = 0;
	virtual string get_description() = 0;
};

#endif 
