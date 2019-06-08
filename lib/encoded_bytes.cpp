//
// Created by Илья on 31.05.2019.
//

#include "encoded_bytes.h"


encoded_bytes::encoded_bytes() : bytes(), size_last(0) {}

void encoded_bytes::push_back(bool x) {
    if (size_last == 8) {
        bytes.push_back((byte) x);
        size_last = 1;
    } else {
        if (bytes.empty()) {
            bytes.push_back(0);
        }
        if (x) {
            bytes.back() += (1 << size_last);
        }
        size_last++;
    }
}


void encoded_bytes::push_back(byte x) { // a1, a2, ..., an
    size_t bigBit = 0;
    for (size_t i = 0; i < 8; ++i) {
        if ((x >> i) & 1) {
            bigBit = i;
        }
    }
    if (bytes.empty()) {
        bytes.push_back(x);
        size_last = bigBit + 1;
        return;
    }
    bytes.back() += (x << size_last);
    if (size_last + bigBit >= 8) {
        bytes.push_back(x >> (8 - size_last));
        size_last = (bigBit + 1) - (8 - size_last);
    } else {
        size_last += bigBit + 1;
    }
}

byte const &encoded_bytes::get(size_t ind) const {
    return bytes[ind];
}

size_t encoded_bytes::size() const {
    return bytes.size();
}





