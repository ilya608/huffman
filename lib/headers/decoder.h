//
// Created by Илья on 31.05.2019.
//

#ifndef HUFFMAN_DECODER_H
#define HUFFMAN_DECODER_H

#include "consts.h"
#include "counter.h"
#include "huffman_tree.h"

#include "encoded_bytes.h"

struct decoder {
    decoder(encoded_bytes&, std::vector<byte>);

    std::vector<byte> decode(const encoded_bytes& encodedBytes);

    huffman_tree tree;
private:
};

#endif //HUFFMAN_DECODER_H
