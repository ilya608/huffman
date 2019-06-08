//
// Created by Илья on 31.05.2019.
//

#include <counter.h>

counter::counter() : cnt(MAX_DATA){}

void counter::calc(std::vector<byte> const &data) {
    for (auto x : data) {
        cnt[x]++;
    }
    times++;
}

std::map<byte, ull> counter::get_cnt() {
    std::map<byte, ull> res;
    for (size_t i = 0; i < MAX_DATA; ++i) {
        if (cnt[i] != 0) {
            res[i] = cnt[i];
        }
    }
    return res;
}

size_t counter::get_times() {
    return times;
}

