//
// Created by Илья on 01.06.2019.
//

#include "file_decompressor.h"

void decompress(std::string const &fileIn, string const &fileOut) {
    try {
        file_reader check(fileIn);
    } catch (...) {
        throw 1;
       // throw std::runtime_error("File does not exists or permission denied");
    }
    file_reader reader(fileIn);
    file_writer writer(fileOut);
    uint16_t sizeTour;
    sizeTour = reader.get_short();
    if (sizeTour == 0 && reader.eof()) {
        return;
    }
    //std::cout << sizeTour << '\n';
    encoded_bytes encodedTree;
    for (size_t i = 0; i < sizeTour; ++i) {
        auto cur = reader.get();
        //std::cout << "byte = " << (int) cur << '\n';
        encodedTree.bytes.push_back(cur);
    }
    encodedTree.size_last = reader.get();
    uint16_t cntLeafs = reader.get_short();
    std::vector<byte> alp(0);
   // std::cout << "cntLeafs = " << (int) cntLeafs << '\n';
    for (size_t i = 0; i < cntLeafs; ++i) {
        auto cur = reader.get();
     //   std::cout << "leaf = " << (int) cur << '\n';
        alp.push_back(cur);
    }
    decoder ddr(encodedTree, alp);
    while (!reader.eof()) {
        encoded_bytes encodedBytes;
        uint16_t bytesLen = reader.get_short();
        byte lastSize = reader.get();
        // auto cur = reader.get();
        for (size_t i = 0; i < bytesLen; ++i) {
            auto x = reader.get();
            //std::cout << "x = " << (int)x << '\n';
            encodedBytes.bytes.push_back(x);
        }
        encodedBytes.size_last = lastSize;
        auto res = ddr.decode(encodedBytes);
        for (byte i : res) {
            writer.write(i);
        }
    }
}
