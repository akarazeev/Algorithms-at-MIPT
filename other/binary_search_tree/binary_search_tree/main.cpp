//
//  main.cpp
//  binary_search_tree
//
//  Created by Anton Karazeev on 12/06/2017.
//  Copyright © 2017 Anton Karazeev. All rights reserved.
//

#include <iostream>

class Node {
public:
    Node(int value_arg) : value(value_arg) {
        
    }
    
    bool is_leaf() {
        return (right == nullptr) and (left == nullptr);
    }
    
    bool not_full() {
        return (right == nullptr) or (left == nullptr);
    }
    
    int value;
    Node* right = nullptr;
    Node* left = nullptr;
};

class BST {
public:
    BST() {
        
    }
    
    void insert(int value) {
        if (root_ == nullptr) {
            root_ = new Node(value);
        } else {
            Node* tmp = root_;
            
            while (tmp != nullptr) {
                if (value > tmp->value) {
                    if (tmp->right != nullptr) {
                        tmp = tmp->right;
                    } else {
                        tmp->right = new Node(value);
                        return;
                    }
                } else if (value < tmp->value) {
                    if (tmp->left != nullptr) {
                        tmp = tmp->left;
                    } else {
                        tmp->left = new Node(value);
                        return;
                    }
                }
            }
        }
    }
    
    void help_traverse(Node* node) {
        std::cout << "> " << node->value << std::endl;
        
        if (node->left != nullptr) {
            std::cout << node->value << "_left: " << std::endl;
            help_traverse(node->left);
        }
        if (node->right != nullptr) {
            std::cout << node->value << "_right: " << std::endl;
            help_traverse(node->right);
        }
    }
    
    void traverse() {
        help_traverse(root_);
    }
    
private:
    Node* root_ = nullptr;
};

int main() {
    BST tree;
    
    tree.insert(1);
    tree.insert(4);
    tree.insert(5);
    tree.insert(13);
    
    tree.traverse();
    
    return 0;
}
