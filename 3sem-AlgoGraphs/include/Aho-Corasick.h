//
//  Aho-Corasick.h
//  Aho-Corasik
//
//  Created by Anton Wetret on 16/11/15.
//  Copyright © 2015 Anton Karazeev. All rights reserved.
//

#ifndef Aho_Corasick_h
#define Aho_Corasick_h

#include <assert.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

class AhoCorasick {
private:
    typedef std::pair<int, std::string> Elem;
    
    class cmp {
    public:
        bool operator()(Elem a, Elem b) {
            return a.first < b.first;
        }
    };
    
    struct vertex {
        bool leaf = false;
        int p = -1;  // parent id
        char pch;  // char of parent
        int link = -1;
        int leng = -1;  // length of string
        std::string word;  // whole founded string
        std::map<char, int> next;  // possible transition from current statement
        std::map<char, int> go;
    };
    
public:
    AhoCorasick();
    
    void add_string(const std::string& s);
    
    int go(int v, char c);
    int get_link(int v);
    
    int count_entry(const std::string& s);
    std::set<Elem, cmp> count_seq(const std::string& s);
    std::vector<std::pair<std::string, std::set<int> > > count_seq_sorted
    (const std::string& s);
    
private:
    int size_;  // counter of statements
    std::vector<vertex> states_;  // all statements
};

#endif /* Aho_Corasick_h */
