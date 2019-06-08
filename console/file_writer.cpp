//
// Created by Илья on 01.06.2019.
//

#include "file_writer.h"

file_writer::file_writer(string const &filename) : writer(filename, ofstream::binary), cur_ind(0) {}

file_writer::~file_writer() {
    writer.write(buffer, cur_ind);
    writer.close();
}

void file_writer::write(byte c) {
    if (cur_ind == BUF_SIZE) {
        writer.write(buffer, cur_ind);
        cur_ind = 0;
    }

    buffer[cur_ind++] = static_cast<char>(c);
}

void file_writer::write_short(uint16_t x)
{
    write(static_cast<byte>(x >> 8));
    write(static_cast<byte>((x << 8) >> 8));
}