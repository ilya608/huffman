//
// Created by Илья on 01.06.2019.
//

#ifndef HUFFMAN_FILE_DECOMPRESSOR_H
#define HUFFMAN_FILE_DECOMPRESSOR_H

#include "file_reader.h"
#include "file_writer.h"
#include "encoder.h"
#include "decoder.h"

void decompress(std::string const &fileIn, string const &fileOut);

#endif //HUFFMAN_FILE_DECOMPRESSOR_H
