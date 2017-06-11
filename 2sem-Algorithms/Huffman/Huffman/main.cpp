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
    node(const node* n): parent(n->parent), c_(n->c_), prob_(n->prob_), left(n->left), right(n->right) {
        
    }
    node(char c, int prob): c_(c), prob_(prob) {
        node* n = nullptr;
        parent = n;
        left = n;
        right = n;
    }
    void operator=(node* other) {
        parent = other->parent;
        left = other->left;
        right = other->right;
        c_ = other->c_;
        col_ = other->col_;
        prob_ = other->prob_;
    }
    node* parent;
    node* left;
    node* right;
    char c_;
    int col_ = 0;
    int prob_;
};

class nodecmp {
public:
    bool operator()(const node* left, const node* right) const {
        if (left->prob_ == right->prob_) return left->c_ > right->c_;
        else return left->prob_ > right->prob_;
    }
};

priority_queue<node*, vector<node*>, nodecmp> CountNodeQueu(string s) {
    priority_queue<node*, vector<node*>, nodecmp> res;
    string buf = s;
    sort(buf.begin(), buf.end());
    auto it = unique(buf.begin(), buf.end());
    buf.resize(distance(buf.begin(), it));
    
    for (char c : buf) {
        node* n = new node(c, (int)count(s.begin(), s.end(), c));
        res.push(n);
    }
    
    return res;
}

node* GetTree(priority_queue<node*, vector<node*>, nodecmp>& q) {
    while (q.size() > 1) {
        node* n1 = (q.top());
        q.pop();
        node* n2 = (q.top());
        q.pop();
        node* par = new node;
        
        par->left = n1;
        par->right = n2;
        
        n1->parent = par;
        n2->parent = par;
        
        par->prob_ = n1->prob_ + n2->prob_;
        
        q.push(par);
    }
    return q.top();
}

//vector<pair<char, string> > GetCodes(node* root) {
//
//    return ;
//}

int main() {
    
    string s;
    s = "hHelloworld";
    
    auto q = CountNodeQueu(s);
    int size = (int)q.size();
    
    vector<pair<char, string> > coding;
    
    auto it = GetTree(q);
    
    string code;
    
    int sz = 0;
    
    while (sz < size) {
        if (it->left != nullptr && it->left->col_ == 0) {
            it = it->left;
            code += '0';
        }
        else if (it->right != nullptr && it->right->col_ == 0) {
            it = it->right;
            code += '1';
        }
        else if (it->right != nullptr && it->right->col_ == 1 && it->left != nullptr && it->left->col_ == 1) {
            it->col_ = 1;
            it = it->parent;
            code.pop_back();
        }
        else if (it->right == nullptr && it->left == nullptr) {
            coding.push_back(pair<char, string>(it->c_, code));
            it->col_ = 1;
            it = it->parent;
            code.pop_back();
            ++sz;
        }
    }
    
    for (auto it = coding.begin(); it != coding.end(); ++it) {
        cout << it->first << ' ' << it->second << endl;
    }
    
    return 0;
}