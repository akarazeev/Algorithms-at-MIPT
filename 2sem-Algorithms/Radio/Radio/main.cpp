//
//  main.cpp
//  Radio
//
//  Created by Anton Wetret on 06/05/15.
//  Copyright (c) 2015 Anton Karazeev. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    map<int, int> data;
    string input;
    cin >> input;
    
    while (input != "EXIT") {
        if (input == "VOTE") {
            cin >> input;
            int track_id;
            cin >> track_id;
            int score;
            cin >> score;
            int time;
            cin >> time;
            if (data.find(track_id) != data.end()) {
                data[track_id] += score;
            }
            else {
                data.insert(pair<int, int>(track_id, score));
            }
        }
        else if (input == "GET") {
            vector<pair<int, int> > vtosort(data.begin(), data.end());
            sort(vtosort.begin(), vtosort.end(), [](pair<int, int>& left, pair<int, int>& right) {
                if (left.second == right.second) return left.first < right.first;
                else return left.second > right.second;
            }
                 );
            cout << vtosort[0].first << ' ' << vtosort[0].second << endl;
            data[vtosort[0].first] = -1;
        }
        cin >> input;
    }
    
    cout << "OK" << endl;
    
    return 0;
}
