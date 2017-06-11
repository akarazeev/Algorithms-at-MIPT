//
//  TextEdit.cpp
//  Undo-Redo
//
//  Created by Anton Wetret on 22/04/15.
//  Copyright (c) 2015 Anton Karazeev. All rights reserved.
//

#include "TextEdit.h"
#include <iostream>
#include <stack>

using namespace std;

textedit::textedit() {
    vector<char> t;
    data_.push_back(t);
}

void textedit::left(bool flag) {
    if (j_ != 0) --j_;
    else if (j_ == 0 && i_ != 0) {
        --i_;
        j_ = (int)data_[i_].size();
    }
    if (flag) {
        action a("left");
        undo_.push(a);
    }
}

void textedit::right(bool flag) {
    if (data_.size() == 0);
    else if (data_[i_].size() == j_) {
        if (data_.size() == i_+1);
        else {
            ++i_;
            j_ = 0;
        }
    }
    else {
        ++j_;
    }
    if (flag) {
        action a("right");
        undo_.push(a);
    }
}

void textedit::up(bool flag, int pos) {
    int bufpos = j_;
    if (flag || pos < 0) {
        if (i_ > 0 && j_+1 <= data_[i_-1].size()) --i_;
        else if (i_ > 0 && j_+1 > data_[i_-1].size()) {
            --i_;
            j_ = (int)data_[i_].size();
        }
        else if (i_ == 0) j_ = 0;
        if (flag) {
            action a("up", bufpos);
            undo_.push(a);
        }
    }
    else {
        --i_;
        j_ = pos;
    }
}

void textedit::down(bool flag, int pos) {
    int bufpos = j_;
    if (flag || pos < 0) {
        if (i_+1 < data_.size() && j_ <= data_[i_+1].size()) ++i_;
        else if (i_+1 < data_.size() && j_+1 > data_[i_].size()) {
            ++i_;
            j_ = (int)data_[i_].size();
        }
        else if (i_+1 == data_.size()) j_ = (int)data_[i_].size();
        if (flag) {
            action a("down", bufpos);
            undo_.push(a);
        }
    }
    else {
        ++i_;
        j_ = pos;
    }
}

vector<char> textedit::operator[](int i) {
    return data_[i];
}

void textedit::insert(char c, bool flag) {
    data_[i_].insert(data_[i_].begin()+j_, c);
    ++j_;
    if (flag) {
        action a("insert", data_[i_][j_-1]);
        undo_.push(a);
    }
}

void textedit::del(bool flag) {
    if (j_ != 0) {
        if (flag) {
            action a("del", data_[i_][j_-1]);
            undo_.push(a);
        }
        data_[i_].erase(data_[i_].begin()+j_-1);
        --j_;
    }
    else if (j_ == 0 && i_ != 0) {
        if (flag) {
            action a("del");
            undo_.push(a);
        }
        int buf = (int)data_[i_].size();
        data_[i_-1].insert(data_[i_-1].end(), data_[i_].begin(), data_[i_].end());
        data_.erase(data_.begin()+i_);
        j_ = (int)data_[i_-1].size() - buf;
        --i_;
    }
}

void textedit::undo() {
    if (undo_.size() != 0) {
        action a(undo_.top());
        undo_.pop();
        redo_.push(a);
        if (a.what_ == "insert") {
            this->del(0);
        }
        else if (a.what_ == "del") {
            if (a.chr_ != '\0') this->insert(a.chr_, 0);
            else this->nextstring(0);
        }
        else if (a.what_ == "nextstring") {
            this->del(0);
        }
        else if (a.what_ == "left") {
            this->right(0);
        }
        else if (a.what_ == "right") {
            this->left(0);
        }
        else if (a.what_ == "up") {
            this->down(0, a.pos_);
        }
        else if (a.what_ == "down") {
            this->up(0, a.pos_);
        }
    }
}

void textedit::redo() {
    if (redo_.size() != 0) {
        action a(redo_.top());
        redo_.pop();
        undo_.push(a);
        if (a.what_ == "insert") {
            this->insert(a.chr_, 0);
        }
        else if (a.what_ == "del") {
            this->del(0);
        }
        else if (a.what_ == "nextstring") {
            this->nextstring(0);
        }
        else if (a.what_ == "right") {
            this->right(0);
        }
        else if (a.what_ == "left") {
            this->left(0);
        }
        else if (a.what_ == "up") {
            this->up(0, a.pos_);
        }
        else if (a.what_ == "down") {
            this->down(0, a.pos_);
        }
    }
}

int textedit::v_size() {
    return (int)data_.size();
}

int textedit::h_size(int i) {
    return (int)data_[i].size();
}

int textedit::I() const {
    return i_;
}

int textedit::J() const {
    return j_;
}

void textedit::nextstring(bool flag) {
    if ((data_[i_].size() == j_) || data_.size() == 0 || data_[i_].size() == 0) {
        vector<char> temp;
        data_.insert(data_.begin()+i_+1, temp);
        j_ = 0;
        ++i_;
    }
    else if (j_ < data_[i_].size()) {
        vector<char> temp;
        data_.insert(data_.begin()+i_+1, temp);
        data_[i_+1].insert(data_[i_+1].end(), data_[i_].begin()+j_, data_[i_].end());
        data_[i_].erase(data_[i_].begin()+j_, data_[i_].end());
        j_ = 0;
        ++i_;
    }
    if (flag) {
        action a("nextstring");
        undo_.push(a);
    }
}

ostream& operator<<(ostream& stream, textedit& t) {
    for (int i = 0; i < t.v_size(); ++i) {
        for (int j = 0; j < t.h_size(i); ++j) {
            stream << t[i][j];
        }
        if (i+1 < t.v_size()) cout << endl;
    }
    return stream;
}

action::action(const action& a): what_(a.what_), chr_(a.chr_), pos_(a.pos_) {
    
}

action::action(string what): what_(what) {
    
}

action::action(string what, int pos): what_(what), pos_(pos) {
    
}

action::action(string what, char chr): what_(what), chr_(chr) {
    
}