//
//  main.cpp
//  Beauty-Contest_2
//
//  Created by Anton Wetret on 04/05/15.
//  Copyright (c) 2015 Anton Karazeev. All rights reserved.
//

#include <iostream>
#include <set>
#include <string>
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

int main() {
    set<call> data;
    set<name> names;
    string input;
    
    name l("asdag");
    names.insert(l);
    name k("vvvvv");
    names.insert(k);
    name x("vvvv");
    auto it = names.find(x);
    
    cin >> input;
    while (input != "EXIT") {
        cout << 1;
        if (input == "reg") {
            cin >> input;
            name n(input);
            auto it = names.find(n);
            
            if (names.find(n) != names.end() && names.size() != 0) cout << "ALREADY REGISTERED";
            else names.insert(n);
        }
        else if (input == "vip") {
            cin >> input;
            call c(input);
            c.make_vip();
            auto it = data.find(c);
            if (it != data.end() && it->is_vip() && data.size() != 0) cout << "ALREADY VIP";
            else if (it != data.end() && data.size() != 0) {
                call buf(*it);
                buf.make_vip();
                data.erase(it);
                data.insert(it, buf);
            }
            else data.insert(c);
        }
        else if (input == "vot") {
            cin >> input;
            name n(input);
            cin >> input;
            call c(input);
            auto itn = names.find(n);
            auto itd = data.find(c);
            if (itn == names.end() && names.size() != 0) cout << "NOT REGISTERED";
            else if (itn != names.end() && names.size() != 0) {
                // Имя найдено
                if (itd == data.end() || data.size() == 0) {
                    // Номера нету, записываем его
                    c.count_inc();
                    data.insert(c);
                    name bufname(*itn);
                    bufname.score_inc();
                    //                    names.insert(itn, bufname);
                    names.erase(itn);
                    names.insert(bufname);
                }
                else if (itd != data.end() && data.size() != 0 && itd->is_allow()) {
                    // Найден номер и allow = true
                    name bufname(*itn);
                    call bufcall(*itd);
                    
                    bufname.score_inc();
                    bufcall.count_inc();
                    
                    data.erase(itd);
                    names.erase(itn);
                    
                    //                    data.insert(itd, bufcall);
                    //                    names.insert(itn, bufname);
                    data.insert(bufcall);
                    names.insert(bufname);
                }
                else if (itd != data.end() && data.size() != 0 && !(itd->is_allow())) cout << "NO MORE VOTES";
            }
        }
        cin >> input;
    }
    
    return 0;
}
