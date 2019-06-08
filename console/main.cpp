#include <iostream>
#include <vector>
#include <decoder.h>
#include "counter.h"
#include "encoder.h"
#include "huffman_tree.h"
#include "encoded_bytes.h"
#include "file_reader.h"
#include "file_compressor.h"
#include "file_decompressor.h"

void greet() {
    std::cout << " It is Huffman encoder!\n Write \"help\" for lists of commands\n";
}

void help() {
    std::cout << "For compress use: \"compress File_input File_output\"\n";
    std::cout << "For decompress use: \"decompress File_input File_output\"\n";
}

std::vector<string> parse_command(string command) {
    std::vector<string> result;
    size_t last = 0;
    for (size_t i = 0; i < command.length(); ++i) {
        if (command[i] == ' ') {
            if (i > last) {
                result.push_back(command.substr(last, i - last));
            }

            last = i + 1;
        }
    }
    result.push_back(command.substr(last));
    return result;
}

void console_compress(string in, string out) {
    std::cout << "Compressing..." << '\n' << '\n';
    try {
        compress(in, out);
        std::cout << "OK" << '\n';
    } catch (int error) {
        if (error == 1) {
            std::cout << "Error!\nFile wasn't found or permission denied" << '\n';
        } else {
            std::cout << "Error!\nUnknown error";
        }
    }
}

void console_decompress(string in, string out) {
    std::cout << "Decompressing..." << '\n' << '\n';
    try {
        decompress(in, out);
        std::cout << "OK" << '\n';
    } catch (int error) {
        if (error == 1) {
            std::cout << "Error!\nFile not found or permission denied" << '\n';
        } else if (error == 2) {
            std::cout << "Error!\nFile was corrupted" << '\n';
        }
    }
}
int main(int argc, char *argv[]) {
    if (argc == 1) {
        greet();
    } else if (argc == 2 && string(argv[1]) == "help") {
        help();
    } else if (argc == 4 && string(argv[1]) == "compress") {
        console_compress(argv[2], argv[3]);
    } else if (argc == 4 && string(argv[1]) == "decompress") {
        console_decompress(argv[2], argv[3]);
    } else {
        std::cout << "Wrong console arguments\n Write \"help\" to watch list commands\n";
    }
    return 0;
}
