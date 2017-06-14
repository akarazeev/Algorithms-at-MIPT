//
//  main.cpp
//  binary_tree_check
//
//  Created by Anton Karazeev on 09/06/2017.
//  Copyright © 2017 Anton Karazeev. All rights reserved.
//

#include <iostream>
#include <algorithm>

class Node {
public:
    Node(int value_arg) : value(value_arg) {
        
    }
    bool is_leaf() {
        return (right == nullptr) and (left == nullptr);
    }
    
    int value;
    Node* right = nullptr;
    Node* left = nullptr;
};

class Tree {
public:
    Tree(Node* root) : root_(root) {
        
    }
    Tree() {
        
    }
    Node* get_root() {
        return root_;
    }
private:
    Node* root_ = nullptr;
};

std::tuple<int, int, bool> min_max_flag(Node* node) {
    std::cout << "> " << node->value << std::endl;
    
    if (node->is_leaf()) {
        return std::make_tuple(node->value, node->value, true);
    } else {
        if ((node->left != nullptr) and (node->right != nullptr)) {
            std::tuple<int, int, bool> tmp_left = min_max_flag(node->left);
            std::tuple<int, int, bool> tmp_right = min_max_flag(node->right);
            
            int tmp_min = std::min(std::get<0>(tmp_left), std::get<0>(tmp_right));
            int tmp_max = std::max(std::get<1>(tmp_left), std::get<1>(tmp_right));
            
            bool flag = (node->value > std::get<1>(tmp_left)) and (node->value < std::get<0>(tmp_right)) and (std::get<2>(tmp_left)) and (std::get<2>(tmp_right));
            
            return std::make_tuple(tmp_min, tmp_max, flag);
        } else if (node->right != nullptr) {
            std::tuple<int, int, bool> tmp_right = min_max_flag(node->right);
            bool flag = (node->value < std::get<0>(tmp_right)) and (std::get<2>(tmp_right));

            return std::make_tuple(std::get<0>(tmp_right), std::get<1>(tmp_right), flag);
        } else {
            std::tuple<int, int, bool> tmp_left = min_max_flag(node->left);
            bool flag = (node->value > std::get<1>(tmp_left)) and (std::get<2>(tmp_left));
            
            return std::make_tuple(std::get<0>(tmp_left), std::get<1>(tmp_left), flag);
        }
    }
}

bool is_binary_tree(Node* root) {
    if (root == nullptr) {
        return false;
    } else {
        return std::get<2>(min_max_flag(root));
    }
}


/*
 
Binary Search Tree:
        6
       / \
      4  7
     / \
    1  5
 
        6
      /  \
     4    8
    / \   /
   1  5  7
 
Not Binary Search Tree:
        6
       / \
      4  7
     / \
    1  8

 */

int main() {
    Node a(6);
    
    Node aa(4);
    Node bb(8);
    
    Node aaa(1);
    Node bbb(5);
    Node ccc(7);
    
    aa.left = &aaa;
    aa.right = &bbb;
    bb.left = &ccc;
    
    a.left = &aa;
    a.right = &bb;
    
    Tree tr(&a);
    bool answer = is_binary_tree(tr.get_root());

    std::cout << "is_binary_tree: " << answer << std::endl;
    
    return 0;
}
