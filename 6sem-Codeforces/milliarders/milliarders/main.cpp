//
//  main.cpp
//  milliarders
//
//  Created by Anton Karazeev on 19/08/2017.
//  Copyright © 2017 Anton Karazeev. All rights reserved.
//

/*

in:
5
Abramovich London 150
Deripaska Moscow 100
Potanin Moscow 50
Berezovsky London 25
Khodorkovsky Chita 1
25 9
1 Abramovich Anadyr
5 Potanin Courchevel
10 Abramovich Moscow
11 Abramovich London
11 Deripaska StPetersburg
15 Potanin Norilsk
20 Berezovsky Tbilisi
21 Potanin StPetersburg
22 Berezovsky London
 
out:
Anadyr 5
London 14
Moscow 1
 
*/

#include <string>
#include <set>
#include <map>
#include <unordered_map>
#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>

const int maxn = 10000; // max number of milliarders
const int maxk = 50000; // max number of registered movements

struct City {
    long long money;
    int days; // Number of days being on the top
    std::string name;
} cities[maxn + maxk];

struct Person {
    std::string name;
    long long money;
    City* location;
} persons[maxn];

class cmp {
public:
    bool operator()(const std::pair<long long, City*>& left, const std::pair<long long, City*>& right) {
        if (left.first == right.first) {
            return left.second->name > right.second->name;
        } else {
            return left.first > right.first;
        }
    }
};

int main() {
    std::unordered_map<std::string, int> answer; // Cities and number of days being on the top
    std::unordered_map<std::string, Person*> personMap; // Maps names into people
    std::set<std::pair<long long, City*>, cmp> scoreBoard; // The cities ordered by money
    std::map<std::string, City*> cityMap; // Maps names into cities
    
    int n; // number of names to read
    std::cin >> n;
    
    int city_counter = 0;
    
    /* Read name, initial location and money */
    for (int i = 0; i < n; ++i) {
        std::string name;
        std::string location;
        long long money;
        
        std::cin >> name >> location >> money;
        
        personMap[name] = &persons[i];
        
        if(!cityMap[location]) {
            cityMap[location] = &cities[city_counter++];
        }
        
        persons[i].location = cityMap[location];
        persons[i].money = money;
        cityMap[location]->name = location;
        cityMap[location]->money += money;
    }

    for (auto c : cityMap) {
        // {money, city}
        scoreBoard.insert({c.second->money, c.second});
    }
    
    int m; // total number of days with available data
    int k; // number of registered movements
    
    std::cin >> m >> k;
    
    int prevday = 0;
    int day = -1;
    std::string name, place;
    
    /* Read registered movements */
    for (int i = 0; i < k; ++i) {
        std::cin >> day >> name >> place;
        
        if(day != prevday) {
            auto it2 = scoreBoard.begin();
            auto it = it2;
            ++it2;
            if(it2 == scoreBoard.end() || it->first > it2->first) {
                it->second->days += day - prevday;
                
                if (!answer[it->second->name]) {
                    answer[it->second->name] = 1;
                } else {
                    answer[it->second->name] += day - prevday;
                }
            }
        }

        if(!cityMap[place]) { // New city mentioned
            cityMap[place] = &cities[city_counter++];
            cityMap[place]->name = place;
        }
        
        // Update the set and the city data structure itself
        auto nextplace = cityMap[place];
        auto person = personMap[name];
        auto prevplace = person->location;
        auto prevmoney = prevplace->money;
        
        scoreBoard.erase({prevmoney, prevplace});
        prevplace->money -= person->money;
        scoreBoard.insert({prevplace->money, prevplace});
        
        scoreBoard.erase({nextplace->money, nextplace});
        nextplace->money += person->money;
        scoreBoard.insert({nextplace->money, nextplace});
        
        person->location = nextplace;
        prevday = day;
    }
    
    day = m;
    if(day != prevday) {
        auto it2 = scoreBoard.begin();
        auto it = it2;
        ++it2;
        if(it2 == scoreBoard.end() || it->first > it2->first) {
            it->second->days += day-prevday;
        }
    }
    
    /* Build output vector */
    std::vector<std::pair<std::string, int> > output;
    for(auto& r : scoreBoard) {
        if(r.second->days) {
            output.push_back({r.second->name, r.second->days});
        }
    }
    
    std::sort(output.begin(), output.end());
    
    for(auto& o : output) {
        std::cout << o.first << " " << o.second << std::endl;
    }
    
    return 0;
}
