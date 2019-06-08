//
// Created by Илья on 01.06.2019.
//

#include "file_reader.h"

file_reader::file_reader(std::string const &filename) : reader(filename, std::ios::in | std::ios::binary), name(filename),
                                                        cur_ind(0), end_ind(0) {
    if (!reader) {
        reader.close();
        throw std::runtime_error("No file");
    }
    // FILE *f = fopen(filename, "r");

}

file_reader::~file_reader() {
    reader.close();
}

bool file_reader::eof() {
    return (cur_ind == end_ind && reader.peek() == EOF);
}

byte file_reader::get() {
    if (cur_ind == end_ind) {
        reader.read(buffer, BUF_SIZE);
        end_ind = static_cast<size_t>(reader.gcount());
        if (end_ind == 0) {
            throw 2;
        }
        cur_ind = 0;
    }
    // std::cout << "cur = " << cur_ind << " " << end_ind << '\n';
    return (byte) buffer[cur_ind++];
}

uint16_t file_reader::get_short() {
    uint16_t res = 0;
    if (eof()) {
        throw std::runtime_error("Expected 16 bits");
    }
    res += static_cast<uint16_t>(get());
    res <<= 8;
    if (eof()) {
        throw std::runtime_error("16 bits");
    }
    res += static_cast<uint16_t>(get());
    return res;
}
