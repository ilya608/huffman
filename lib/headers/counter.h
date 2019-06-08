//
// Created by Илья on 31.05.2019.
//

#ifndef HUFFMAN_COUNTER_H

#include "consts.h"

struct counter {
    counter();

    void calc(std::vector<byte> const &data);

    std::map<byte, ull> get_cnt();

    size_t get_times();

private:
    std::vector<ull> cnt;
    size_t times;
};

#define HUFFMAN_COUNTER_H

#endif //HUFFMAN_COUNTER_H
