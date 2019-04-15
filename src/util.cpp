#ifdef _WIN32
#include <winsock2.h>
#else

#include <cstring>

#endif

#include "util.h"

uint16_t sniff::ntohs(uint8_t network_short[2]) {
    return network_short[1] | network_short[0] << 8;
}

uint16_t sniff::ntohs(vector<uint8_t>::iterator iter) {
    return *(iter + 1) | *iter << 8;
}

uint32_t sniff::ntohi(uint8_t network_int[4]) {
    return network_int[3] | network_int[2] << 8 | network_int[1] << 16 | network_int[0] << 24;
}

uint32_t sniff::ntohi(vector<uint8_t>::iterator iter) {
    return *(iter + 3) | *(iter + 2) << 8 | *(iter + 1) << 16 | *iter << 24;
}

string sniff::get_last_error(const string prefix) {
    string message{};
    char* err_msg;

#ifdef  _WIN32
    auto err = WSAGetLastError();
    char err_buf[256];
    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), err_buf,
        sizeof(err_buf), NULL);

    err_msg = err_buf;
#else
    err_msg = strerror(errno);
#endif

    if (!prefix.empty())
        message.append(prefix);
    if (strlen(err_msg) > 0)
        message.append(" - ").append(err_msg);

    return message;
}