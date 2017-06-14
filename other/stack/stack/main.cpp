//
//  main.cpp
//  stack
//
//  Created by Anton Karazeev on 13/06/2017.
//  Copyright © 2017 Anton Karazeev. All rights reserved.
//

#include <iostream>
#include <string>

class Node {
public:
    Node () {
        
    }
    
    Node (int value_arg) : value(value_arg) {
        
    }
    
    Node* next = nullptr;
    Node* prev = nullptr;
    int value;
};

class Stack {
public:
    Stack() {
        head_ = new Node();
    }
    
    void insert(char ch) {
        head_->value = ch;
        
        Node* tmp = new Node;
        tmp->prev = head_;
        head_->next = tmp;
        head_ = tmp;
    }
    
    bool is_empty() {
        return head_->prev == nullptr;
    }
    
    char pop() {
        int ans = head_->prev->value;
        Node* tmp = head_;
        head_ = head_->prev;
        head_->next = nullptr;
        delete tmp;
        
        return ans;
    }
    
private:
    Node* head_;
};

bool check_seq(std::string sequence) {
    Stack data;
    
    for (int i = 0; i < sequence.length(); ++i) {
        if (sequence[i] == '(') {
            data.insert(sequence[i]);
        } else if (sequence[i] == ')') {
            if ((data.is_empty() == true) or (data.is_empty() == false and data.pop() != '(')) {
                return false;
            }
        }
    }
    
    return data.is_empty();
}

int main() {
    
    std::string seq = "()()(())";
    
    std::cout << check_seq(seq) << std::endl;
    
    return 0;
}
