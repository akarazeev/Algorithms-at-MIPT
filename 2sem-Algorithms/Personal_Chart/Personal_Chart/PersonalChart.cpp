//
//  PersonalChart.cpp
//  Personal_Chart
//
//  Created by Anton Wetret on 06/05/15.
//  Copyright (c) 2015 Anton Karazeev. All rights reserved.
//

#include "PersonalChart.h"
#include <map>
#include <string>
#include <algorithm>

using namespace std;

PersonalChart::PersonalChart() {
    
}

bool PersonalChart::UserExist(const string& username) const {
    return data_.find(username) != data_.end();
}

bool PersonalChart::IDExist(const string& username, const int& trackID) {
    return data_[username].find(trackID) != data_[username].end();
}

void PersonalChart::VoteRecord(const string& username, const int& trackID) {
    if (UserExist(username)) {
        if (IDExist(username, trackID)) data_[username][trackID] += 1;
        else {
            data_[username].insert(pair<int, int>(trackID, 1));
        }
    }
    else {
        map<int, int> first;
        first.insert(pair<int, int>(trackID, 1));
        data_.insert(pair<string, map<int, int> >(username, first));
    }
}

int PersonalChart::GetHistorySize(const string& username) {
    int count = 0;
    for (auto it = data_[username].begin(); it != data_[username].end(); ++it) {
        count += it->second;
    }
    return count;
}

vector<int> PersonalChart::GetTop(const string& username, const int& topSize) {
    vector<pair<int,int> > temp(data_[username].begin(), data_[username].end());
    
    sort(temp.begin(), temp.end(), [](pair<int,int>& left, pair<int,int>& right) {
        if (left.second == right.second) return left.first < right.first;
        else return left.second > right.second;
    }
         );
    vector<int> res;
    for (int i = 0; i < (topSize>temp.size() ? temp.size() : topSize); ++i) {
        res.push_back(temp[i].first);
    }
    return res;
}

int PersonalChart::GetDistinctTrackSize(const string& username) {
    vector<pair<int, int> > temp(data_[username].begin(), data_[username].end());
    sort(temp.begin(), temp.end(), [](pair<int,int>& left, pair<int,int>& right) {
        return left.first < right.first;
    }
         );
    auto it = unique(temp.begin(), temp.end(), [](pair<int,int>& left, pair<int,int>& right) {
        return left.first == right.first;
    }
                     );
    temp.resize(distance(temp.begin(), it));
    return (int)temp.size();
}