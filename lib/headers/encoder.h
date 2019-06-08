//
// Created by Илья on 31.05.2019.
//

#ifndef HUFFMAN_ENCODER_H
#define HUFFMAN_ENCODER_H

#include "consts.h"
#include "counter.h"
#include "huffman_tree.h"
#include "encoded_bytes.h"

struct encoder {
    explicit encoder(counter const &cnt);

    encoded_bytes encode(std::vector<byte> data);

    void encode_tree(huffman_tree::node *);

    std::pair<encoded_bytes, std::vector<byte>> encoded_tree();


    huffman_tree tree;
private:
    encoded_bytes treeBytes;
    std::vector<byte> alp;
};

#endif //HUFFMAN_ENCODER_H
