//
// Created by Илья on 31.05.2019.
//

#include <encoder.h>
#include <huffman_tree.h>

encoded_bytes encoder::encode(std::vector<byte> data) {
    encoded_bytes res;
    for (auto i : data) {
        for (auto j : tree.getCode(i)) {
            // cur <<= 1;
            // cur += (size_t) j
            res.push_back(j);
        }
        // res.push_back(cur);
    }
    return res;
}

encoder::encoder(counter const &cnt) : tree(cnt) {}

void encoder::encode_tree(huffman_tree::node *v) {
    if (v->leaf) {
        alp.push_back(v->symbol);
    }
    if (v->l != nullptr) {
        treeBytes.push_back(false);
        encode_tree(v->l);
        treeBytes.push_back(true);
    }
    if (v->r != nullptr) {
        treeBytes.push_back(false);
        encode_tree(v->r);
        treeBytes.push_back(true);
    }
}

std::pair<encoded_bytes, std::vector<byte>> encoder::encoded_tree() {
    encode_tree(tree.root);
    return {treeBytes, alp};
}


