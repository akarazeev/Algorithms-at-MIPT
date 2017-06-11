//
//  main.cpp
//  Lazy
//
//  Created by Anton Wetret on 05/05/15.
//  Copyright (c) 2015 Anton Karazeev. All rights reserved.
//

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class letter {
public:
    letter() {
        
    }
    letter(string sur, string reas, int tim): surname(sur), reason(reas), time(tim) {
        
    }
    letter(int tim): time(tim) {
        
    }
    bool operator==(const letter& other) const {
        return time == other.time;
    }
    bool operator<(const letter& other) const {
        return time < other.time;
    }
    string surname;
    string reason;
    int time;
};

class cmp {
public:
    bool operator()(const letter & left, const letter & right) const {
        return left.surname < right.surname;
    }
};

class cmpfire {
public:
    bool operator()(const pair<string, int>& left, const pair<string, int>& right) const {
        if (left.second == right.second) return left.first < right.first;
        else return left.second > right.second;
    }
};

int main() {
    set<letter> letters;
    set<letter> delletters;
    int N;
    cin >> N;
    string input;
    cin >> input;
    while (input != "EXIT") {
        if (input == "ADD") {
            static int mintime = 10001;
            static int maxtime = 0;
            string surname;
            string reason;
            int time;
            cin >> surname;
            cin >> reason;
            cin >> time;
            if (time < mintime) mintime = time;
            if (time > maxtime) maxtime = time;
            cout << mintime << '/' << maxtime << endl;
            // Здесь запускаем уборку старых писем
            if (maxtime - mintime > N) {
                // Надо не удалять, а перемещать их в удаленные письма
                cout << "DELETE" << endl;
                letter letdel(maxtime);
                auto it = letters.find(letdel);
                delletters.insert(*it);
                letters.erase(letters.begin(), it);
                maxtime = 0;
                if (letters.size() != 0) mintime = letters.begin() -> time;
                else mintime = 10001;
            }
            letter let(surname, reason, time);
            letters.insert(let);
        }
        if (input == "BAD") {
            int k;
            cin >> k;
            if (k < letters.size()) {
                vector<string> vtosort;
                int count = 0;
                for (auto it = letters.begin(); count < k; ++it) {
                    vtosort.push_back(it->surname);
                    ++count;
                }
                sort(vtosort.begin(), vtosort.end());
                for (int i = 0; i < k; ++i) {
                    cout << vtosort[i] << endl;
                }
                for (auto it = letters.begin(); count < k; ++it) {
                    letters.erase(it);
                    ++count;
                }
            }
            else if (k >= letters.size()) {
                vector<letter> vtosort(letters.begin(), letters.end());
                sort(vtosort.begin(), vtosort.end(), cmp());
                for (int i = 0; i < k; ++i) {
                    cout << vtosort[i].surname << endl;
                }
                letters.erase(letters.begin(), letters.end());
            }
            else if (letters.size() == 0) cout << "NOBODY" << endl;
        }
        else if (input == "MANAGE") {
            cin >> input;
            int count = 0;
            for (auto it = letters.begin(); it != letters.end(); ++it) {
                if (it->surname == input) ++count;
            }
            for (auto it = delletters.begin(); it != delletters.end(); ++it) {
                if (it->surname == input) ++count;
            }
            cout << count;
        }
        else if (input == "FIRE") {
            int number;
            cin >> number;
            set<string> unnames;
            //Получаю имена (все по одному)
            for (auto it = letters.begin(); it != letters.end(); ++it) {
                unnames.insert(it->surname);
            }
            for (auto it = delletters.begin(); it != delletters.end(); ++it) {
                unnames.insert(it->surname);
            }
            //Подсчет числа вхождений имен
            vector<pair<string, int> > vtofire;
            for (auto it = unnames.begin(); it != unnames.end(); ++it) {
                int count = 0;
                for (auto itsearch = letters.begin(); itsearch != letters.end(); ++itsearch) {
                    if (*it == itsearch->surname) ++count;
                }
                for (auto itsearch = delletters.begin(); itsearch != delletters.end(); ++itsearch) {
                    if (*it == itsearch->surname) ++count;
                }
                pair<string, int> pairfire(*it, count);
                vtofire.push_back(pairfire);
            }
            sort(vtofire.begin(), vtofire.end(), cmpfire());
            int mincount = vtofire[number>vtofire.size() ? vtofire.size()-1 : number-1].second;
            auto it = vtofire.begin();
            while (it->second >= mincount) {
                cout << it->first << ' ' << it->second << endl;
                ++it;
            }
        }
        cin >> input;
    }
    
    return 0;
}
