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

#endif /* Aho_Corasick_h */
