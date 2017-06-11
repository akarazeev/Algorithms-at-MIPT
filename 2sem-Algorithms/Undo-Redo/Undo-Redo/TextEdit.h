//
//  TextEdit.h
//  Undo-Redo
//
//  Created by Anton Wetret on 22/04/15.
//  Copyright (c) 2015 Anton Karazeev. All rights reserved.
//

#ifndef __Undo_Redo__TextEdit__
#define __Undo_Redo__TextEdit__

#include <stdio.h>
#include <vector>
#include <stack>
#include <string>

using namespace std;

class action {
public:
    action(const action& a);
    action(string what);
    action(string what, char chr);
    action(string what, int pos);
    
    string what_;
    char chr_ = '\0';
    int pos_ = -1;
};

class textedit {
public:
    textedit();
    
    void left(bool flag);
    void right(bool flag);
    void up(bool flag, int pos);
    void down(bool flag, int pos);
    void nextstring(bool flag);
    
    void insert(char c, bool flag);
    void del(bool flag);
    void undo();
    void redo();
    
    int h_size(int i);
    int v_size();
    int I() const;
    int J() const;
    
    vector<char> operator[](int i);
    
    friend ostream& operator<<(ostream& stream, textedit& t);
private:
    vector<vector<char> > data_;
    stack<action> undo_;
    stack<action> redo_;
    int i_ = 0;
    int j_ = 0;
};

ostream& operator<<(ostream& stream, textedit& t);

#endif /* defined(__Undo_Redo__TextEdit__) */
