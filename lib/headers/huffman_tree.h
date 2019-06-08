//
// Created by Илья on 31.05.2019.
//

#ifndef HUFFMAN_HUFFMAN_TREE_H
#define HUFFMAN_HUFFMAN_TREE_H

#include "consts.h"
#include "counter.h"
#include "encoded_bytes.h"

struct huffman_tree {
    struct node {
        node();

        node(byte symbol, ull cnt);

        node(ull cnt, node *l, node *r);

        ull cnt;
        byte symbol;
        bool leaf;

        node *l, *r, *p;
    };

    struct comparator {
        bool operator()(node *a, node *b) {
            return a->cnt < b->cnt;
        }
    };

    void decodeTree(node *v, encoded_bytes &encoded_tree, std::vector<byte> &alp);

    huffman_tree(encoded_bytes encodedTree, std::vector<byte> &alp);

    explicit huffman_tree(counter counter);

    explicit huffman_tree(std::map<byte, ull> alphabet);
    // huffman_tree() = default;
    // ~huffman_tree() = default;

    std::vector<bool> getCode(byte x);
    ~huffman_tree();
    node *root;

    std::vector<std::vector<bool>> code;
private:
    void build(std::multiset<node *, comparator> nodes);

    void getCodes(node *v, std::vector<bool> curCode);

    size_t cntLeafs;

    void del(node *&v);
};

#endif //HUFFMAN_HUFFMAN_TREE_H
