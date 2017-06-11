//
//  main.cpp
//  Beauty_Contest
//
//  Created by Anton Wetret on 04/05/15.
//  Copyright (c) 2015 Anton Karazeev. All rights reserved.
//

#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

class call {
public:
    call() {
        
    }
    call(string number): number_(number) {
        
    }
    call(const call& c): number_(c.number_), count_(c.count_), vip_(c.vip_) {
        
    }
    call(string number, bool vip): number_(number), vip_(vip) {
        
    }
    void make_vip() {
        vip_ = 1;
        count_ = 0;
    }
    void count_inc() {
        ++count_;
    }
    bool is_vip() const {
        return vip_;
    }
    bool is_allow() const {
        return (count_ == 0 && vip_ == 0) || (count_ < 3 && vip_ == 1);
    }
    bool operator==(const call& other) const {
        return number_ == other.number_;
    }
    bool operator<(const call& other) const {
        return number_ < other.number_;
    }
private:
    string number_;
    int count_ = 0;
    bool vip_ = 0;
};

class name {
public:
    name() {
        
    }
    name(string name):name_(name) {
        
    }
    void score_inc() {
        ++score_;
    }
    int score() const {
        return score_;
    }
    string nameof() const {
        return name_;
    }
    bool operator==(const name& other) const {
        return name_ == other.name_;
    }
    bool operator<(const name& other) const {
        return name_ < other.name_;
    }
private:
    string name_;
    int score_ = 0;
};

class cmp {
public:
    bool operator()(const name& left, const name& right) const {
        if (left.score() == right.score()) return left.nameof() > right.nameof();
        else return left.score() < right.score();
    }
};

int main() {
    ifstream fin("/Users/AntonWetret/Documents/XCode/Seminars/2 семестр/Tasks_2/Beauty_Contest/Beauty_Contest/test.txt");
    set<call> data;
    set<name> names;
    string input;
    
    fin >> input;
    while (input != "EXIT") {
        if (input == "REGISTER") {
            fin >> input;
            name n(input);
            if (names.find(n) != names.end() && names.size() != 0) cout << "ALREADY REGISTERED" << endl;
            else {
                names.insert(n);
                cout << "OK" << endl;
            }
        }
        else if (input == "VIP") {
            fin >> input;
            call c(input);
            c.make_vip();
            auto it = data.find(c);
            if (it != data.end() && it->is_vip() && data.size() != 0) cout << "ALREADY VIP" << endl;
            else if (it != data.end() && data.size() != 0) {
                call buf(*it);
                buf.make_vip();
                data.erase(it);
                data.insert(buf);
                cout << "OK" << endl;
            }
            else {
                data.insert(c);
                cout << "OK" << endl;
            }
        }
        else if (input == "VOTE") {
            fin >> input;
            name n(input);
            fin >> input;
            call c(input);
            auto itn = names.find(n);
            auto itd = data.find(c);
            
            if ((itn == names.end() && names.size() != 0) || names.size() == 0) cout << "NOT REGISTERED" << endl;
            else if (itn != names.end() && names.size() != 0) {
                // Имя найдено
                if (itd == data.end() || data.size() == 0) {
                    // Номера нету, записываем его
                    c.count_inc();
                    data.insert(c);
                    
                    name bufname(*itn);
                    bufname.score_inc();
                    names.erase(itn);
                    names.insert(bufname);
                    cout << bufname.score() << endl;
                }
                else if (itd != data.end() && data.size() != 0 && itd->is_allow()) {
                    // Найден номер и allow = true
                    name bufname(*itn);
                    call bufcall(*itd);
                    
                    bufname.score_inc();
                    bufcall.count_inc();
                    
                    data.erase(itd);
                    names.erase(itn);
                    
                    data.insert(bufcall);
                    names.insert(bufname);
                    cout << bufname.score() << endl;
                }
                else if (itd != data.end() && data.size() != 0 && !(itd->is_allow())) cout << "NO MORE VOTES" << endl;
            }
        }
        else if (input == "KICK") {
            fin >> input;
            name n(input);
            auto it = names.find(n);
            if ((it == names.end() && names.size() != 0) || names.size() == 0) cout << "NOT REGISTERED" << endl;
            else {
                names.erase(it);
                cout << "OK" << endl;
            }
        }
        else if (input == "TOP") {
            int q;
            fin >> q;
            if (names.size() != 0) {
                vector<name> d(names.begin(), names.end());
                sort(d.begin(), d.end(), cmp());
                for (auto it = d.rbegin(); it != d.rend() && it != d.rbegin()+q; ++it) {
                    cout << it->nameof() << ' ' << it->score() << endl;
                }
            }
        }
        fin >> input;
    }
    
    cout << "OK" << endl;
    
    return 0;
}
