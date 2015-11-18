//
//  Aho-Corasick.h
//  Aho-Korasik
//
//  Created by Anton Wetret on 16/11/15.
//  Copyright © 2015 Anton Karazeev. All rights reserved.
//

#ifndef Aho_Corasick_h
#define Aho_Corasick_h

#include <iostream>
#include <string>
#include <vector>
#include <assert.h>

class AhoCorasick {
public:
    struct vertex {
        std::vector<int> next; // possible transition from current statement
        bool leaf;
        int p; // parent id
        char pch; // char of parent
        int link;
        std::vector<int> go;
    };
    AhoCorasick(int K, int MaxNum);
    void add_string(std::string& s);
    int go(int v, char c);
    int get_link(int v);
    int count_entry(std::string& s);
private:
    int size_; // counter of statements
    std::vector<vertex> states_;
    int K_; // size of alphabet
    int MaxNum_; // MaxNum of statements
};

AhoCorasick::AhoCorasick(int K, int MaxNum): K_(K), MaxNum_(MaxNum) {
    states_ = std::vector<vertex> (MaxNum_, vertex());
    states_[0].next = std::vector<int> (K_, -1);
    states_[0].go = std::vector<int> (K_, -1);
    states_[0].p = -1;
    states_[0].link = -1;
    size_ = 1;
}

void AhoCorasick::add_string(std::string& s) {
    int v = 0;
    for (int i = 0; i < s.length(); ++i) {
        char c = s[i] - 'a';
        assert(c < K_);
        assert(c > 0);
        if (states_[v].next[c] == -1) {
            states_[size_].next = std::vector<int> (K_, -1);
            states_[size_].go = std::vector<int> (K_, -1);
            
            states_[size_].link = -1;
            states_[size_].p = v;
            states_[size_].pch = c;
            states_[v].next[c] = size_;
            ++size_;
        }
        v = states_[v].next[c];
    }
    states_[v].leaf = true;
}

int AhoCorasick::get_link(int v) {
    if (states_[v].link == -1) {
        if (v == 0 || states_[v].p == 0) {
            states_[v].link = 0;
        }
        else {
            states_[v].link = go(get_link(states_[v].p), states_[v].pch);
        }
    }
    return states_[v].link;
}

int AhoCorasick::go(int v, char c) {
    if (states_[v].go[c] == -1) {
        if (states_[v].next[c] != -1) {
            states_[v].go[c] = states_[v].next[c];
        } else {
            states_[v].go[c] = (v == 0) ? (0) : (go(get_link(v), c));
        }
    }
    return states_[v].go[c];
}

int AhoCorasick::count_entry(std::string& s) {
    int v = 0;
    int res = 0;
    for (auto it : s) {
        assert(v < MaxNum_);
        v = go(v, it - 'a');
        if (states_[v].leaf == true) {
            ++res;
        }
    }
    return res;
}

#endif /* Aho_Corasick_h */
