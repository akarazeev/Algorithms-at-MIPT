//
//  main.cpp
//  String_Pool
//
//  Created by Anton Wetret on 09/05/15.
//  Copyright (c) 2015 Anton Karazeev. All rights reserved.
//

#include <iostream>
#include <unordered_map>
#include <string>
#include <stdlib.h>

using namespace std;

class StringPool {
public:
    StringPool(int n): n_(n) {
        
    }
    void Insert(string word) {
        data_.insert(pair<int, string>(abs((int)hash<string>()(word) % n_), word));
    }
    int GetId(const string& word) {
        return abs((int)hash<string>()(word) % n_);
    }
    string GetWord(int id) {
        return data_[id];
    }
private:
    unordered_map<int, string> data_;
    int n_;
};

int main() {
    StringPool s(10);
    s.Insert("lala");
    s.Insert("houseofthesun");
    cout << s.GetWord(0);
    
    return 0;
}
