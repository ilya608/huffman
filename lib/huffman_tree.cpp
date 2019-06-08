//
// Created by Илья on 31.05.2019.
//

#include <set>

#include "huffman_tree.h"
#include "consts.h"

huffman_tree::node::node() : cnt(0), symbol(0), leaf(false), l(nullptr), r(nullptr), p(nullptr) {
}

huffman_tree::node::node(byte symbol, ull cnt) : cnt(cnt), symbol(symbol), leaf(true), l(nullptr), r(nullptr),
                                                 p(nullptr) {}

huffman_tree::node::node(ull cnt, node *l, node *r) : cnt(cnt), symbol(0), leaf(false), l(l), r(r), p(nullptr) {}


huffman_tree::huffman_tree(std::map<byte, ull> cnt) {
    code.resize(257);
    cntLeafs = 0;
    std::multiset<node *, comparator> nodes;
    for (auto i : cnt) {
        nodes.insert(new node(i.first, i.second));
    }
    build(nodes);
}

huffman_tree::huffman_tree(counter counter) : huffman_tree(counter.get_cnt()) {}


void huffman_tree::build(std::multiset<node *, comparator> nodes) {
    while (nodes.size() > 1) {
        node *l = *nodes.begin();
        nodes.erase(nodes.begin());
        node *r = *nodes.begin();
        nodes.erase(nodes.begin());
        nodes.insert(new node(l->cnt + r->cnt, l, r));
    }

    if (nodes.size() == 1) {
        if ((*nodes.begin())->leaf) {
            root = new node();
            root->l = *nodes.begin();
        } else {
            root = *nodes.begin();
        }
        getCodes(root, std::vector<bool>(0));
    } else {
        root = nullptr;
    }
}

void huffman_tree::getCodes(node *v, std::vector<bool> curCode) {
    if (v == nullptr) {
        return;
    }
    //std::cout << "v " << curCode.size() << '\n';
    if (v->leaf) {
       // std::cout << "nonono" << '\n';
        code[v->symbol] = curCode;
    }
    curCode.push_back(false);
    getCodes(v->l, curCode);
    curCode.pop_back();

    curCode.push_back(true);
    getCodes(v->r, curCode);
}

std::vector<bool> huffman_tree::getCode(byte x) {
    return code[x];
}


void huffman_tree::decodeTree(huffman_tree::node *v, encoded_bytes &encoded_tree, std::vector<byte> &alp) {
    size_t cur = 0;
    for (size_t i = 0; i < encoded_tree.size(); ++i) {
        auto x = encoded_tree.get(i);
        size_t pos = 0;
        while ((i != encoded_tree.size() - 1 && pos < 8) || (i == encoded_tree.size() - 1 && pos < encoded_tree.size_last)) {
            pos++;
            cur = static_cast<size_t>(x % 2);
            x /= 2;
            if (cur == 0) {
                if (v->l == nullptr) {
                    v->l = new node();
                    v->l->p = v;
                    v = v->l;
                } else {
                    v->r = new node();
                    v->r->p = v;
                    v = v->r;
                }
            } else {
                if (v->l == nullptr) {
                    v->leaf = true;
                    v->symbol = alp[cntLeafs++];
                } else {
                    v->leaf = false;
                }
                v = v->p;
            }
        }
    }
}

huffman_tree::huffman_tree(encoded_bytes encodedTree, std::vector<byte> &alp) {
    root = new node();
    code.resize(257);
    cntLeafs = 0;
    decodeTree(root, encodedTree, alp);
    getCodes(root, std::vector<bool>(0));
}

void huffman_tree::del(node *&v) {
    if (v != nullptr) {
        del(v->l);
        del(v->r);

        delete v;
        v = nullptr;
    }
}

huffman_tree::~huffman_tree() {
    del(root);
}


