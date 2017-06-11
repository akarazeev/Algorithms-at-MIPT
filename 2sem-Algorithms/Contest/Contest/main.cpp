//
//  main.cpp
//  Contest
//
//  Created by Anton Wetret on 08/05/15.
//  Copyright (c) 2015 Anton Karazeev. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>

using namespace std;

class cmp {
public:
    bool operator()(const pair<string, int>& left, const pair<string, int>& right) const {
        if (left.second == right.second) return left.first < right.first;
        else return left.second < right.second;
    }
};

class cmpsolut {
public:
    bool operator()(const pair<int, int>& left, const pair<int, int>& right) const {
        if (left.second == right.second) return left.first < right.first;
        else return left.second < right.second;
    }
};

int main() {
    ifstream fin("/Users/AntonWetret/Documents/XCode/Seminars/2 семестр/Tasks_2/Contest/Contest/test.txt");
    int N;
    fin >> N;
    map<int, pair<int, int> > tasks;
    map<string, set<int> > studs;
    
    for (int i = 0; i < N; ++i) {
        int mark;
        fin >> mark;
        tasks[i+1] = pair<int, int>(mark, 0);
    }
    
    string input;
    fin >> input;
    
    while (input != "EXIT") {
        if (input == "SOLVED") {
            fin >> input;
            int task;
            fin >> task;
            studs[input].insert(task);
            tasks[task].second += 1;
        }
        else if (input == "STUD_STAT") {
            fin >> input;
            int sum = 0;
            for (auto it = studs[input].begin(); it != studs[input].end(); ++it) {
                sum += tasks[*it].first;
            }
            cout << studs[input].size() << ' ' << sum << endl;
        }
        else if (input == "STUDS_BY_TASKS") {
            vector<pair<string, int> > vtosort;
            for (auto itname = studs.begin(); itname != studs.end(); ++itname) {
                vtosort.push_back(pair<string, int>(itname->first, studs[itname->first].size()));
            }
            sort(vtosort.begin(), vtosort.end(), cmp());
            for (int i = 0; i < vtosort.size(); ++i) {
                cout << vtosort[i].first << ' ' << vtosort[i].second << endl;
            }
        }
        else if (input == "STUDS_BY_BALLS") {
            vector<pair<string, int> > vtosort;
            for (auto itname = studs.begin(); itname != studs.end(); ++itname) {
                int sum = 0;
                for (auto ittask = studs[itname->first].begin(); ittask != studs[itname->first].end(); ++ittask) {
                    sum += tasks[*ittask].first;
                }
                vtosort.push_back(pair<string, int>(itname->first, sum));
            }
            sort(vtosort.begin(), vtosort.end(), cmp());
            for (int i = 0; i < vtosort.size(); ++i) {
                cout << vtosort[i].first << ' ' << vtosort[i].second << endl;
            }
        }
        else if (input == "STUDS_MORE_TASKS") {
            int n;
            fin >> n;
            vector<pair<string, int> > vtosort;
            for (auto itname = studs.begin(); itname != studs.end(); ++itname) {
                if (studs[itname->first].size() >= n) vtosort.push_back(pair<string, int>(itname->first, studs[itname->first].size()));
            }
            sort(vtosort.begin(), vtosort.end(), cmp());
            for (int i = 0; i < vtosort.size(); ++i) {
                cout << vtosort[i].first << ' ' << vtosort[i].second << endl;
            }
        }
        else if (input == "STUDS_MORE_BALLS") {
            int n;
            fin >> n;
            vector<pair<string, int> > vtosort;
            for (auto itname = studs.begin(); itname != studs.end(); ++itname) {
                int sum = 0;
                for (auto ittask = studs[itname->first].begin(); ittask != studs[itname->first].end(); ++ittask) {
                    sum += tasks[*ittask].first;
                }
                if (sum >= n) vtosort.push_back(pair<string, int>(itname->first, sum));
            }
            sort(vtosort.begin(), vtosort.end(), cmp());
            for (int i = 0; i < vtosort.size(); ++i) {
                cout << vtosort[i].first << ' ' << vtosort[i].second << endl;
            }
        }
        else if (input == "TASKS_BY_SOLUTIONS") {
            vector<pair<int, int> > vtosort;
            for (auto it = tasks.begin(); it != tasks.end(); ++it) {
                vtosort.push_back(pair<int, int>(it->first, it->second.second));
            }
            sort(vtosort.begin(), vtosort.end(), cmpsolut());
            for (int i = 0; i < vtosort.size(); ++i) {
                cout << vtosort[i].first << ' ' << vtosort[i].second << endl;
            }
        }
        fin >> input;
    }
    
    return 0;
}
