//
//  BTree.h
//  b-tree
//
//  Created by Danil Tulin on 4/30/15.
//  Copyright (c) 2015 Danil Tulin. All rights reserved.
//

#include <iostream>
#include <vector>

#include <memory.h>

#pragma once

template <class Key, class Value>
class BTree
{
    size_t branching;
    
    class Node
    {
        
    public:
        
        Node();
        bool isLeaf() const;
        
        std::vector<std::pair<Key, Value>> values;
        std::vector<BTree<Key, Value>::Node *> children;
    };
    
    BTree<Key, Value>::Node *root;
    
    void splitChild(BTree<Key, Value>::Node *node, int index, BTree<Key, Value>::Node *parent);
    
    Value search(const BTree<Key, Value>::Node *node, const Key &key) const;
    void deleteKey(const Key &key, Node *node);
    
    typename BTree<Key, Value>::Node *searchNode(const BTree<Key, Value>::Node *node, const Key &key) const;
    
    const BTree<Key, Value>::Node &getRoot() const;
    
    void insertNonFull(const Key &key, const Value &value, Node *node);
    
    std::pair<Key, Value> removePredecessor(BTree<Key, Value>::Node *node);
    std::pair<Key, Value> removeSuccessor(BTree<Key, Value>::Node *node);
    
public:
    
    BTree(size_t branching);
    BTree(const BTree &tree);
    void operator = (const BTree &rhs);
    
    Value search(const Key &key) const;
    void deleteKey(const Key &key);
    void insert(const Key &key, const Value &value);
};
