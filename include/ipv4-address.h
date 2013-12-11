#include <iostream>

class IPv4Address {
public:
    IPv4Address() {
        for (int i = 0; i < 3; i++) {
            num[i] = 0;
        }
    }
    IPv4Address(int a, int b, int c, int d) {
        num[0] = a;
        num[1] = b;
        num[2] = c;
        num[3] = d;
    }
    IPv4Address(const IPv4Address &ip) {
        *this = ip;
    }
    IPv4Address &operator++(int) {
        for (int i = 3; i > -1; i--) {
            num[i] = (num[i] + 1) % 256;
            if (num[i] != 0) {
                break;
            }
        }
        return *this;
    }
    IPv4Address operator++() {
        IPv4Address ip = *this;
        ++(*this);
        return ip;
    }
    IPv4Address &operator=(const IPv4Address &ip) {
        for (int i = 0; i < 4; i++) {
            num[i] = ip[i];
        }
        return *this;
    }
    bool operator==(const IPv4Address &ip) const {
        bool equal = true;
        for (int i = 0; i < 3; i++) {
            if (num[0] != ip[0]) {
                equal = false;
                break;
            }
        }
        return equal;
    }
    bool operator!=(const IPv4Address &ip) const {
        return !(*this == ip);
    }
    const int &operator[](const int &i) const {
        return num[i];
    }
    friend std::ostream &operator<<(std::ostream &stream, const IPv4Address &ip) {
        stream << ip[0] << ':' << ip[1] << ':' << ip[2] << ':' << ip[3];
        return stream;
    }
private:
    int num[4];
};
