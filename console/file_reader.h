//
// Created by Илья on 01.06.2019.
//

#ifndef HUFFMAN_FILE_READER_H
#define HUFFMAN_FILE_READER_H

#include "consts.h"
#include <string>
#include <fstream>
#include <cstdlib>

struct file_reader
{
    file_reader() = delete;

    explicit file_reader(std::string const &filename);
    ~file_reader();

    bool eof();

    byte get();

    uint16_t get_short();

private:
    std::ifstream reader;
    std::string name;
    char buffer[BUF_SIZE];
    size_t cur_ind, end_ind;
};

#endif //HUFFMAN_FILE_READER_H
