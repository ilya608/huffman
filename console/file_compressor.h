//
// Created by Илья on 01.06.2019.
//

#ifndef HUFFMAN_FILE_COMPRESSOR_H
#define HUFFMAN_FILE_COMPRESSOR_H

#include "consts.h"
#include "counter.h"
#include "file_reader.h"
#include "encoder.h"

counter get_count(std::string const &filename);

// void write_compressed_block(code const &block, file_writer &writer);
void write_block(encoded_bytes const &block);

void compress(std::string const &src, std::string const &dst);

#endif //HUFFMAN_FILE_COMPRESSOR_H
