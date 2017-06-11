//
//  main.cpp
//  Contacts
//
//  Created by Anton Wetret on 09/05/15.
//  Copyright (c) 2015 Anton Karazeev. All rights reserved.
//

#include <iostream>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>

using namespace std;

int main() {
    ifstream fin("/Users/AntonWetret/Documents/XCode/Seminars/2 семестр/Tasks_2/Contacts/Contacts/test.txt");
    map<string, string> numbers;
    map<string, pair<set<string>, string> > contacts;
    
    string input;
    fin >> input;
    while (input != "EXIT") {
        if (input == "ADD_NUMBER") {
            // По имени добавить номер
            string name;
            fin >> name;
            string number;
            fin >> number;
            if (contacts.find(name) != contacts.end()) {
                if (contacts[name].first.find(number) != contacts[name].first.end()) cout << "NUMBER ALREADY EXISTS" << endl;
                else {
                    contacts[name].first.insert(number);
                    numbers.insert(pair<string, string>(number, name));
                    cout << "OK" << endl;
                }
            }
            else {
                set<string> bufset;
                bufset.insert(number);
                pair<set<string>, string> bufpair(bufset, "0");
                contacts.insert(pair<string, pair<set<string>, string> >(name, bufpair));
                numbers.insert(pair<string, string>(number, name));
                cout << "OK" << endl;
            }
        }
        else if (input == "ADD_EMAIL") {
            // По имени добавить почту
            string name;
            fin >> name;
            string mail;
            fin >> mail;
            if (contacts.find(name) != contacts.end()) {
                contacts[name].second = mail;
                cout << "OK" << endl;
            }
            else {
                set<string> bufset;
                pair<set<string>, string> bufpair(bufset, mail);
                contacts.insert(pair<string, pair<set<string>, string> >(name, bufpair));
                cout << "OK" << endl;
            }
        }
        else if (input == "DEL") {
            // Удаление по имени
            string name;
            fin >> name;
            auto it = contacts.find(name);
            if (it != contacts.end()) {
                contacts.erase(it);
                cout << "OK" << endl;
            }
        }
        else if (input == "DEL_NUMBER") {
            // Удаление номера телефона по имени, указать порядковый номер телефона
            string name;
            fin >> name;
            int n;
            fin >> n;
            if (contacts.find(name) != contacts.end()) {
                auto it = contacts[name].first.begin();
                for (int i = 0; i < n-1; ++i, ++it);
                contacts[name].first.erase(it);
                cout << "OK" << endl;
            }
        }
        else if (input == "INFO") {
            // Вывод - все телефоны по фио
            string name;
            fin >> name;
            for (auto it = contacts[name].first.begin(); it != contacts[name].first.end(); ++it) {
                cout << name << ' ' << *it << endl;
            }
        }
        else if (input == "INFO_ALL") {
            // Вывод - все телефоны и email по фио
            string name;
            fin >> name;
            for (auto it = contacts[name].first.begin(); it != contacts[name].first.end(); ++it) {
                cout << name << ' ' << *it << endl;
            }
            if (contacts[name].second != "0") cout << name << ' ' << contacts[name].second << endl;
        }
        else if (input == "SHOW_ALL") {
            // Вывести все содержимое записной книги
            for (auto itcont = contacts.begin(); itcont != contacts.end(); ++itcont) {
                for (auto itnumb = itcont->second.first.begin(); itnumb != itcont->second.first.end(); ++itnumb) {
                    cout << itcont->first << ' ' << *itnumb << endl;
                }
                if (itcont->second.second != "0")
                    cout << itcont->first << ' ' << itcont->second.second << endl;            }
        }
        else if (input == "NUMBER") {
            // По номеру вывести фио
            string number;
            fin >> number;
            cout << number << ' ' << numbers[number] << endl;
        }
        fin >> input;
    }
    return 0;
}
