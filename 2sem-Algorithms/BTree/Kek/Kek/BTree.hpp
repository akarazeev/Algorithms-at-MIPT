//
//  BTree.cpp
//  b-tree
//
//  Created by Danil Tulin on 4/30/15.
//  Copyright (c) 2015 Danil Tulin. All rights reserved.
//

#include "BTree.h"

template <class Key, class Value>
bool BTree<Key, Value>::Node::isLeaf() const
{
    return children.size() == 0;
}

template <class Key, class Value>
BTree<Key, Value>::Node::Node()
{
    
}

template <class Key, class Value>
BTree<Key, Value>::BTree(size_t branching): branching(branching)
{
    BTree<Key, Value>::Node *node = new Node;
    root = node;
}

template <class Key, class Value>
const typename BTree<Key, Value>::Node &BTree<Key, Value>::getRoot() const
{
    return root;
}

template <class Key, class Value>
Value BTree<Key, Value>::search(const typename BTree<Key, Value>::Node *node, const Key &key) const
{
    size_t i = 0;
    while (i < node->values.size() && key > node->values[i].first)
    {
        i++;
    }
    
    if (i < node->values.size() && key == node->values[i].first)
        return node->values[i].second;
    
    if (node->isLeaf())
    {
        return Value();
    }
    else
    {
        return search(node->children[i], key);
    }
}

template <class Key, class Value>
typename BTree<Key, Value>::Node *BTree<Key, Value>::searchNode(const BTree<Key, Value>::Node *node, const Key &key) const
{
    size_t i = 0;
    while (i < node->values.size() && key > node->values[i].first)
    {
        i++;
    }
    
    if (i < node->values.size() && key == node->values[i].first)
        return node;
    
    if (node->isLeaf())
    {
        return BTree<Key, Value>::Node();
    }
    else
    {
        return search(node->children[i], key);
    }
}

template <class Key, class Value>
Value BTree<Key, Value>::search(const Key &key) const
{
    return search(root, key);
}

template <class Key, class Value>
void BTree<Key, Value>::insert(const Key &key, const Value &value)
{
    if (root->values.size() == 2 * branching - 1)
    {
        Node *newNode = new Node;
        Node *prevRoot = root;
        root = newNode;
        newNode->children.push_back(prevRoot);
        splitChild(prevRoot, 0, newNode);
        insertNonFull(key, value, newNode);
    }
    else
    {
        insertNonFull(key, value, root);
    }
}

template <class Key, class Value>
void BTree<Key, Value>::insertNonFull(const Key &key, const Value &value, Node *node)
{
    int index = (int)node->values.size() - 1;
    
    if (node->isLeaf())
    {
        node->values.resize(index + 2);
        while (index >= 0 && key < node->values[index].first)
        {
            node->values.at(index + 1) = node->values.at(index);
            index--;
        }
        
        node->values.at(index + 1) = {key, value};
    }
    else
    {
        while (index >= 0 && key < node->values[index].first)
        {
            index--;
        }
        
//        index++;
        if (node->children[index+1]->values.size() == 2 * branching - 1)
        {
            splitChild(node->children[index+1], index+1, node);
            if (key > node->values[index+1].first)
            {
                index++;
            }
        }
        insertNonFull(key, value, node->children[index+1]);
    }
}

template <class Key, class Value>
void BTree<Key, Value>::deleteKey(const Key &key)
{
    deleteKey(key, root);
}

template <class Key, class Value>
void BTree<Key, Value>::deleteKey(const Key &key, BTree<Key, Value>::Node *node)
{
    int index = 0;
    
    while (index < (int)node->values.size() && key > node->values.at(index).first)
    {
        index++;
    }
    
    if (node->isLeaf())
    {
        for (int i = index; i < node->values.size() - 1; i++)
        {
            node->values.at(i) = node->values.at(i + 1);
        }
        node->values.resize(node->values.size() - 1);
        
        return;
    }
    
    if (!node->isLeaf() && index < node->values.size() && node->values.at(index).first == key)
    {
        BTree<Key, Value>::Node *leftChild = node->children.at(index);
        BTree<Key, Value>::Node *rightChild = node->children.at(index + 1);
        
        if (leftChild->values.size() >= branching)
        {
            std::pair<Key, Value> pair = removePredecessor(leftChild);
            node->values.at(index) = pair;
            
            return;
        }
        
        if (rightChild->values.size() >= branching)
        {
            std::pair<Key, Value> pair = removeSuccessor(rightChild);
            node->values.at(index) = pair;
            
            return;
        }
        
        if (leftChild->values.size() == branching - 1 && rightChild->values.size() == branching - 1)
        {
            leftChild->values.push_back(node->values.at(index));
            for (int i = 0; i < rightChild->values.size(); i++)
            {
                leftChild->values.push_back(rightChild->values.at(i));
            }
            
            for (int i = index; i < node->values.size() - 1; i++)
            {
                node->values.at(i) = node->values.at(i + 1);
                node->children.at(i + 1) = node->children.at(i + 2);
            }
            delete rightChild;
            
            node->values.resize(node->values.size() - 1);
            node->children.resize(node->children.size() - 1);
            
            deleteKey(key, leftChild);
            return;
        }
    }
    else if (!node->isLeaf())
    {
        deleteKey(key, node->children.at(index));
    }
}

template <class Key, class Value>
std::pair<Key, Value> BTree<Key, Value>::removePredecessor(BTree<Key, Value>::Node *node)
{
    if (node->isLeaf())
    {
        std::pair<Key, Value> value = node->values.back();
        node->values.resize(node->values.size() - 1);
        return value;
    }
    return removePredecessor(node->children.back());
}

template <class Key, class Value>
std::pair<Key, Value> BTree<Key, Value>::removeSuccessor(BTree<Key, Value>::Node *node)
{
    if (node->isLeaf())
    {
        std::pair<Key, Value> value = node->values.front();
        
        for (int i = 0; i < node->values.size() - 1; i++)
        {
            node->values.at(i) = node->values.at(i + 1);
        }
        
        node->values.resize(node->values.size() - 1);
        return value;
    }
    return removeSuccessor(node->children.front());
}

template <class Key, class Value>
void BTree<Key, Value>::splitChild(BTree<Key, Value>::Node *node, int index, BTree<Key, Value>::Node *parent)
{
    BTree<Key, Value>::Node *newNode = new Node();
    for (size_t i = 0; i < branching - 1; i++)
    {
        newNode->values.push_back(node->values[i + branching]);
    }
    
    if (node->isLeaf() == false)
    {
        for (int i = 0; i < branching; i++)
        {
            newNode->children.push_back(node->children[i + branching]);
        }
        node->children.resize(branching);
    }
    
    parent->children.resize(parent->children.size() + 1);
    for (int i = (int)parent->values.size(); i > index; i--)
    {
        parent->children.at(i + 1) = parent->children.at(i);
    }
    parent->children.at(index + 1) = newNode;
    
    int i = (int)parent->values.size() - 1;
    while (i >= index)
    {
        parent->values.resize(i + 1);
        parent->values.at(i + 1) = parent->values.at(i);
        i--;
    }
    
//    for (int i = (int)parent->values.size() - 1; i >= index; --i)
//    {
//        parent->values.at(i + 1) = parent->values.at(i);
//    }
    
    parent->values.resize(index + 1);
    parent->values.at(index) = node->values.at(branching - 1);
    
    node->values.resize(branching - 1);
}
