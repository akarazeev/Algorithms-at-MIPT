//
//  main.cpp
//  Huffman coding
//
//  Created by Anton Wetret on 14/05/15.
//  Copyright (c) 2015 Anton Karazeev. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
#include <fstream>

using namespace std;

class node {
public:
    node() {

    }
    node(const node* n): parent(n->parent), ch_(n->ch_), freq_(n->freq_),
                         left(n->left), right(n->right) {

    }
    node(char ch, int freq) {
        ch_ = ch;
        freq_ = freq;
        node* null_node = nullptr;
        parent = null_node;
        left = null_node;
        right = null_node;
    }
    void operator=(node* other) {
        parent = other->parent;
        left = other->left;
        right = other->right;
        ch_ = other->ch_;
        col_ = other->col_;
        freq_ = other->freq_;
    }
    // nodes
    node* parent;
    node* left;
    node* right;
    // character
    char ch_;
    // frequency of character in given text
    int freq_;
    // used in GetCodes function as a flag
    int col_ = 0;
};

// Comparator for nodes
class nodecmp {
public:
    bool operator()(const node* left, const node* right) const {
        if (left->freq_ == right->freq_) {
            return left->ch_ > right->ch_;
        }
        else {
            return left->freq_ > right->freq_;
        }
    }
};

priority_queue<node*, vector<node*>, nodecmp> CountNodeQueu(string input_string) {
    // queue with nodes - (char, number of char in input_string)
    priority_queue<node*, vector<node*>, nodecmp> result_queue;
    // make copy of input_string
    string unique_chars(input_string);
    // sort unique_chars string
    sort(unique_chars.begin(), unique_chars.end());
    // find and assign unique characters to unique_chars
    auto it = unique(unique_chars.begin(), unique_chars.end());
    // fit the size of unique_chars
    unique_chars.resize(distance(unique_chars.begin(), it));
    // iterate over unique characters and count
    // the number of char in input_string
    for (char ch : unique_chars) {
        node* n = new node(ch, (int)count(input_string.begin(), input_string.end(), ch));
        result_queue.push(n);
    }
    return result_queue;
}

node* GetTree(priority_queue<node*, vector<node*>, nodecmp> q) {
    while (q.size() > 1) {
        node* n1 = q.top();
        q.pop();
        node* n2 = q.top();
        q.pop();
        node* par = new node;

        par->left = n1;
        par->right = n2;

        n1->parent = par;
        n2->parent = par;

        par->freq_ = n1->freq_ + n2->freq_;
        q.push(par);
    }
    return q.top();
}

vector<pair<char, string> > GetCodes(string s) {
    vector<pair<char, string> > res;
    string code;
    auto q = CountNodeQueu(s);
    int size = (int)q.size();
    node* root = GetTree(q);
    int sz = 0;
    node* it = root;
    while (sz < size) {
        if (it->left != nullptr && it->left->col_ == 0) {
            it = it->left;
            code += '0';
        }
        else if (it->right != nullptr && it->right->col_ == 0) {
            it = it->right;
            code += '1';
        }
        else if (it->right != nullptr && it->right->col_ == 1 &&
                 it->left != nullptr && it->left->col_ == 1) {
            it->col_ = 1;
            it = it->parent;
            code.pop_back();
        }
        else if (it->right == nullptr && it->left == nullptr) {
            res.push_back(pair<char, string>(it->ch_, code));
            it->col_ = 1;
            it = it->parent;
            code.pop_back();
            ++sz;
        }
    }
    return res;
}

int main() {
    ifstream fin("/Users/AntonWetret/Documents/XCode/Seminars/2 семестр/Tasks_2/Huffman coding/Huffman coding/test.txt");
    string s;
    fin >> s;

    vector<pair<char, string> > coding = GetCodes(s);

    for (auto it = coding.begin(); it != coding.end(); ++it) {
        cout << it->first << ' ' << it->second << endl;
    }

    return 0;
}
