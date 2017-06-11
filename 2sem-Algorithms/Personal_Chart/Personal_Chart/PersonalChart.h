//
//  PersonalChart.h
//  Personal_Chart
//
//  Created by Anton Wetret on 06/05/15.
//  Copyright (c) 2015 Anton Karazeev. All rights reserved.
//

#ifndef __Personal_Chart__PersonalChart__
#define __Personal_Chart__PersonalChart__

#include <stdio.h>
#include <vector>
#include <map>
#include <string>

using namespace std;

class PersonalChart {
public:
    PersonalChart();
    void VoteRecord(const string& username, const int& trackID);
    vector<int> GetTop(const string& username, const int& topSize);
    int GetHistorySize(const string& username);
    int GetDistinctTrackSize(const string& username);
    bool UserExist(const string& username) const;
    bool IDExist(const string& username, const int& trackID);
private:
    map<string, map<int, int> > data_;
};

#endif /* defined(__Personal_Chart__PersonalChart__) */
