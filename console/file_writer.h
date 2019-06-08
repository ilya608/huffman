//
// Created by Илья on 01.06.2019.
//

#ifndef HUFFMAN_FILE_WRITER_H
#define HUFFMAN_FILE_WRITER_H

#include <string>
#include <fstream>
#include <cstdlib>

#include "consts.h"

using std::ofstream;
using std::string;


struct file_writer
{
    file_writer() = delete;
    explicit file_writer(string const &filename);
    ~file_writer();

    void write(byte );

    void write_short(uint16_t x);


private:
    ofstream writer;
    char buffer[BUF_SIZE];
    size_t cur_ind;
};

#endif //HUFFMAN_FILE_WRITER_H
