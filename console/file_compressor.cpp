//
// Created by Илья on 01.06.2019.
//

#include "file_compressor.h"
#include "file_writer.h"

counter get_count(std::string const &filename) {
    counter res;
    file_reader reader(filename);
    std::vector<byte> block;
    while (!reader.eof()) {
        if (block.size() == BUF_SIZE) {
            res.calc(block);
            block.clear();
        }
        block.push_back(reader.get());
    }
    res.calc(block);
    return res;
}

void write_block(encoded_bytes const &block, file_writer &writer) {
    // std::cout << "compressed block:";
//    std::cout << "curSize = " << block.size() << '\n';
    writer.write_short(uint16_t(block.size()));
    writer.write((byte) block.size_last);
    for (size_t i = 0; i < block.size(); ++i) {
        writer.write(block.get(i));
        //std::cout << (int)block.get(i) << " ";
    }
    //std::cout << '\n';
}

void compress(std::string const &fileIn, std::string const &fileOut) {
    try {
        file_reader check(fileIn);
    } catch (...) {
        //throw FileOpenE
        throw 1;
        // throw std::runtime_error("Wrong file");
    }
    encoder e(get_count(fileIn));
    file_reader reader(fileIn);
    file_writer writer(fileOut);
    if (reader.eof()) {
        writer.write(0);
        writer.write(0);
        return;
    }
    std::pair<encoded_bytes, std::vector<byte>> encodedTree = e.encoded_tree();
    //std::cout << "Tree: ";
    //std::cout << "Size = " << encodedTree.first.size() << '\n';
    writer.write_short(static_cast<uint16_t> (encodedTree.first.size()));
    for (size_t i = 0; i < encodedTree.first.size(); ++i) {
        writer.write((byte) encodedTree.first.get(i));
        //std::cout << (int) encodedTree.first.get(i) << " ";
    }
    writer.write((byte) encodedTree.first.size_last);
    //std::cout << '\n';
    writer.write_short(static_cast<uint16_t >(encodedTree.second.size()));
    for (byte i : encodedTree.second) {
        writer.write((byte) i);
    }
    std::vector<byte> block;
    block.reserve(BUF_SIZE);
    while (!reader.eof()) {
        // std::cout << block.size() << '\n';
        if (block.size() == BUF_SIZE) {
            write_block(e.encode(block), writer);
            block.clear();
            block.reserve(BUF_SIZE);
        }
        block.push_back(reader.get());
    }
    if (!block.empty()) {
        write_block(e.encode(block), writer);
    }
}
