//
// Created by Илья on 31.05.2019.
//

#ifndef HUFFMAN_ENCODED_BYTES_H
#define HUFFMAN_ENCODED_BYTES_H

#include "consts.h"
#include "counter.h"

struct encoded_bytes {
    encoded_bytes();

    void push_back(byte x);
    void push_back(bool x);
    bool operator[](size_t ind);
    byte const &get(size_t ind) const;
    size_t size() const;
    std::vector<byte> bytes;
    size_t size_last;
};

#endif //HUFFMAN_ENCODED_BYTES_H
