//
// Created by Илья on 31.05.2019.
//

#include <decoder.h>
#include <assert.h>
#include <algorithm>

#include "decoder.h"
#include "consts.h"
#include "encoded_bytes.h"
#include "huffman_tree.h"

decoder::decoder(encoded_bytes &encodedTree, std::vector<byte> alp) : tree(encodedTree, alp) {}

std::vector<byte> decoder::decode(const encoded_bytes& encodedBytes) {
    std::vector<bool> data;
    for (size_t i = 0; i < encodedBytes.size(); ++i) {
        auto x = encodedBytes.get(i);
        //std::cout << "x = " << (int)x << " last = " << encodedBytes.size_last << '\n';
        size_t pos = 0;
        while ((i != encodedBytes.size() - 1 && pos < 8) || (i == encodedBytes.size() - 1 && pos < encodedBytes.size_last)) {
            //std::cout << "x' =  " << (int)x << '\n';
            pos++;
            auto cur = static_cast<size_t>(x % 2);
            data.push_back((bool) cur);
            x /= 2;
        }
    }
    huffman_tree::node *v = tree.root;
    std::vector<byte> res;
    for (auto i : data) {
        //std::cout << "i = " << i << '\n';
        if (!i) {
            v = v->l;
        } else {
            v = v->r;
        }
        if (v == nullptr) {
            throw 2;
            // assert(0);
        }
        if (v->leaf) {
            res.push_back(v->symbol);
            v = tree.root;
        }
    }
    return res;
}
