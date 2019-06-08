#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <utility>
#include <gtest.h>
#include <fstream>
#include <bitset>

#include "huffman_tree.h"
#include "encoded_bytes.h"
#include "encoder.h"
#include "decoder.h"
#include "file_compressor.h"
#include "file_decompressor.h"


std::vector<byte> encode_decode(std::vector<byte> x) {
//    counter cnt;
//    cnt.update(x);
//    encoder en(cnt);
//    encoded_bytes v = en.dictionary();
//    decoder dec(v);
//    encoded_bytes z = en.encode(x);
//    return dec.decode(z);
    counter cnt;
    cnt.calc(x);
    encoder en(cnt);
    auto tree = en.encoded_tree();
    encoded_bytes d = en.encode(x);
    decoder dec(tree.first, tree.second);
    return dec.decode(d);
}

TEST(correctness, bamboo) {
    std::vector<byte> x = {1, 1, 1, 1, 3, 3, 3, 0, 0, 2};
    std::vector<byte> y = encode_decode(x);
    std::cout << '\n';
    EXPECT_TRUE(std::equal(x.begin(), x.end(), y.begin()));
}
//
TEST(correctness, balance) {
    std::vector<byte> x = {0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3};
    std::vector<byte> y = encode_decode(x);
    EXPECT_TRUE(std::equal(x.begin(), x.end(), y.begin()));
}

TEST(correctness, zero) {
    std::vector<byte> x = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::vector<byte> y = encode_decode(x);

    EXPECT_TRUE(std::equal(x.begin(), x.end(), y.begin()));
}

bool file_encode_decode(std::string const &in) {
    string out = "tester/files/out";
    string out1 = "tester/files/out1";
    compress(in, out);
    decompress(out, out1);
    file_reader f(in);
    file_reader s(out1);
    while (!f.eof() && !s.eof()) {
        auto f1 = f.get();
        auto s1 = s.get();
        if (f1 != s1) {
            return false;
        }
    }
    return !(!f.eof() || !s.eof());
}
TEST(correctness, kek) {
    string in = "tester/files/kek.txt";
    EXPECT_TRUE(file_encode_decode(in));
}
TEST(correctness, file_symbol) {
    EXPECT_TRUE(file_encode_decode("tester/files/symbol"));
}

TEST(correctness, file_bamboo) {
    EXPECT_TRUE(file_encode_decode("tester/files/bamboo"));
}

TEST(correctness, file_balance) {
    EXPECT_TRUE(file_encode_decode("tester/files/balance"));
}

TEST(correctness, no_file) {
    EXPECT_ANY_THROW(file_encode_decode("tester/files/no_file"));
}
TEST(correctness, file_fill) {
    EXPECT_TRUE(file_encode_decode("tester/files/fill"));
}

TEST(correctness, corrupt) {
    EXPECT_ANY_THROW(decompress("tester/files/corrupt", "tester/files/zzz.txt"));
}

TEST(correctness, file_1MB) {
    EXPECT_TRUE(file_encode_decode("tester/files/1MB"));
}


//TEST(correctness, random) {
//    size_t count = 1;
//
//    for (size_t i = 0; i < count; ++i) {
//        std::vector<byte> x(static_cast<size_t>(rand() % 20000));
//        for (unsigned char &j : x) {
//            j = (static_cast<byte>(rand() % MAX_DATA));
//        }
//
//        std::vector<byte> y = encode_decode(x);
//        std::cout << x.size() << " " << y.size() << '\n';
//        EXPECT_TRUE(std::equal(x.begin(), x.end(), y.begin()));
//    }
//}
//
//TEST(correctness, 10MB) {
//    std::vector<byte> x(static_cast<size_t>(10 * 1024 * 1024));
//    for (unsigned char &j : x) {
//        j = (static_cast<byte>(rand() % MAX_DATA));
//    }
//
//    std::vector<byte> y = encode_decode(x);
//
//    EXPECT_TRUE(std::equal(x.begin(), x.end(), y.begin()));
//}
//