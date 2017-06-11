//
//  RBTree.h
//  Red-Black
//
//  Created by Anton Wetret on 29/04/15.
//  Copyright (c) 2015 Anton Karazeev. All rights reserved.
//

#ifndef __Red_Black__RBTree__
#define __Red_Black__RBTree__

#define r 1
#define b 0

#include <stdio.h>

class rbtree;

class node {
public:
    node();
    node(int val);
    node(char color);
    friend rbtree;
//private:
    int val_;
    node* par;
    node* left;
    node* right;
    int col_;
};

class rbtree {
public:
    rbtree();
    
    void rot_r(node* x);
    void rot_l(node* x);
    
    void insert(node* x);
    void rbinsert(node* z);
    void rbinsert_fixup(node* z);
    
    node* nil() const;
    friend node;
private:
    node* root_;
    node* NIL_;
};

#endif /* defined(__Red_Black__RBTree__) */
