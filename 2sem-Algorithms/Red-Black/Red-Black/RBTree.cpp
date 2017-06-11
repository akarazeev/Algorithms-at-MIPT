//
//  RBTree.cpp
//  Red-Black
//
//  Created by Anton Wetret on 29/04/15.
//  Copyright (c) 2015 Anton Karazeev. All rights reserved.
//

#include "RBTree.h"

node::node() {
    
}

//FIXME: Без аллокации узла это сделать невозможно
node::node(int val) {
    val_ = val;
}

/*---RBTREE Description---*/

rbtree::rbtree() {
    root_ = new node;
    NIL_ = new node;
    root_ -> col_ = b;
    root_ -> par = NIL_;
}

node* rbtree::nil() const {
    return NIL_;
}

void rbtree::rot_l(node* x) {
    node* y = x -> right;
    x -> right = y -> left;
    if (y -> left != NIL_) {
        y -> left -> par = x;
    }
    y -> par = x -> par;
    if (x -> par == NIL_) {
        root_ = y;
    }
    else if (x == x -> par -> left) {
        x -> par -> left = y;
    }
    else {
        x -> par -> right = y;
    }
    y -> left = x;
    x -> par = y;
}

void rbtree::rot_r(node* x) {
    node* y = x -> left;
    x -> left = y -> right;
    if (y -> right != NIL_) {
        y -> right -> par = x;
    }
    y -> par = x -> par;
    if (x -> par == NIL_) {
        root_ = y;
    }
    else if (x == x -> par -> right) {
        x -> par -> right = y;
    }
    else {
        x -> par -> left = y;
    }
    y -> right = x;
    x -> par = y;
}

void rbtree::insert(node* n) {
    root_ -> left = n;
}

void rbtree::rbinsert(node* z) {
    node* y = NIL_;
    node* x = root_;
    while (x != NIL_) {
        y = x;
        if (z -> val_ < x -> val_) x = x -> left;
        else x = x -> left;
    }
    z -> par = y;
    if (y == NIL_) root_ = z;
    else if (z -> val_ < y ->val_) y -> left = z;
    else y -> right = z;
    z -> left = NIL_;
    z -> right = NIL_;
    z -> col_ = r;
    rbinsert_fixup(z);
}

void rbtree::rbinsert_fixup(node* z) {
    while (z -> par -> col_ == r) {
        if (z -> par == z -> par -> par -> left) {
            node* y = z -> par -> par -> right;
            if (y -> col_ == r) {
                z -> par -> col_ = b;
                y -> col_ = b;
                z -> par -> par -> col_ = r;
                z = z -> par -> par;
            }
            else if (z == z -> par -> right) {
                z = z -> par;
                rot_l(z);
            }
        }
    }
}