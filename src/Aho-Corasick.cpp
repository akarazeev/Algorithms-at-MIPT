//
//  Aho-Corasick.cpp
//  Aho-Corasik
//
//  Created by Anton Wetret on 16/11/15.
//  Copyright © 2015 Anton Karazeev. All rights reserved.
//

#include "Aho-Corasick.h"

AhoCorasick::AhoCorasick() {
    vertex tmp;
    states_.push_back(tmp);
    size_ = 1;
}

void AhoCorasick::add_string(const std::string& s) {
    int v = 0;
    for (int i = 0; i < s.length(); ++i) {
        char ch = s[i];
        if (states_[v].next.count(ch) == 0) {
            vertex tmp1;
            tmp1.p = v;
            tmp1.pch = ch;
            states_.push_back(tmp1);
            
            states_[v].next[ch] = size_;
            ++size_;
        }
        v = states_[v].next[ch];
    }
    states_[v].leaf = true;
    states_[v].leng = static_cast<int>(s.length());
    states_[v].word = s;
    mapofwords.insert({s, mapofwords.size()});
}

int AhoCorasick::get_link(int v) {
    if (states_[v].link == -1) {
        if (v == 0 || states_[v].p == 0) {
            states_[v].link = 0;
        } else {
            states_[v].link = go(get_link(states_[v].p), states_[v].pch);
        }
    }
    return states_[v].link;
}

int AhoCorasick::go(int v, char c) {
    if (states_[v].go.count(c) == 0) {
        if (states_[v].next.count(c) != 0) {
            states_[v].go[c] = states_[v].next[c];
        } else {
            if (v == 0) {
                states_[v].go[c] = 0;
            } else {
                states_[v].go[c] = go(get_link(v), c);
            }
        }
    }
    return states_[v].go[c];
}

int AhoCorasick::count_entry(const std::string& s) {
    int v = 0;
    int res = 0;
    for (int i = 0; i < s.length(); ++i) {
        v = go(v, s[i]);
        for (int tmp = v; tmp > 0; tmp = get_link(tmp)) {
            if (states_[tmp].leaf == true) {
                ++res;
                std::cout << res << '_' << states_[tmp].word << std::endl;
            }
        }
    }
    return res;
}

std::set<AhoCorasick::Elem, AhoCorasick::cmp> AhoCorasick::count_seq(
                                                                     const std::string& s) {
    std::set<Elem, cmp> res;
    int v = 0;
    for (int i = 0; i < s.size(); ++i) {
        v = go(v, s[i]);
        for (int tmp = v; tmp > 0; tmp = get_link(tmp)) {
            if (states_[tmp].leaf == true) {
                res.insert({i-states_[tmp].leng+1, states_[tmp].word});
            }
        }
    }
    return res;
}

std::vector<std::pair<std::string, std::set<int> > > AhoCorasick::count_seq_sorted(
                                                                                   const std::string& s) {
    std::map<std::string, std::set<int> > tmp_res;
    int v = 0;
    for (int i = 0; i < s.size(); ++i) {
        v = go(v, s[i]);
        for (int tmp = v; tmp > 0; tmp = get_link(tmp)) {
            if (states_[tmp].leaf == true) {
                tmp_res[states_[tmp].word].insert(i-states_[tmp].leng+1);
            }
        }
    }
    std::vector<std::pair<std::string, std::set<int> > > res;
    for (auto it : tmp_res) {
        res.push_back(it);
    }
    std::sort(res.begin(), res.end(), [](std::pair<std::string, std::set<int> > a, std::pair<std::string, std::set<int> > b) {
        return *(b.second.begin()) > *(a.second.begin());
    });
    return res;
}
