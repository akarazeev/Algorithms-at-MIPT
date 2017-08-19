////
////  main.cpp
////  milliarders
////
////  Created by Anton Karazeev on 19/08/2017.
////  Copyright © 2017 Anton Karazeev. All rights reserved.
////
//
//#include <string>
//#include <set>
//#include <map>
//#include <unordered_map>
//#include <iostream>
//#include <functional>
//#include <vector>
//#include <algorithm>
//
//const int maxn = 10000;
//const int maxk = 50000;
//
//struct City {
//    long long money;
//    int days; // Number of days on the top
//    std::string name;
//} cities[maxn+maxk];
//
//struct Person {
//    std::string name;
//    long long money;
//    City* location;
//} persons[maxn];
//
//std::unordered_map<std::string, Person*> personMap; // Maps names into people
//std::map<std::string, City*> cityMap; // Maps names into cities
//
//class cmp {
//public:
//    bool operator()(const std::pair<long long, City*>& left, const std::pair<long long, City*>& right) {
//        return left.second->money > right.second->money;
//    }
//};
//
//std::set<std::pair<long long, City*>, cmp> scoreBoard; // The cities ordered by money
//
//int main() {
//    int n;
//    std::cin >> n;
//    int city_counter = 0;
//    
//    for (int i = 0; i < n; ++i) {
//        std::string tmp_name;
//        std::string tmp_city;
//        long long tmp_cash;
//        
//        std::cin >> tmp_name;
//        std::cin >> tmp_city;
//        std::cin >> tmp_cash;
//        
//        personMap[tmp_name] = &persons[i];
//
//        if(!cityMap[tmp_city]) {
//            cityMap[tmp_city] = &cities[++city_counter];
//        }
//
//        persons[i].location = cityMap[tmp_city];
//        persons[i].money = tmp_cash;
//        cityMap[tmp_city]->name = tmp_city;
//        cityMap[tmp_city]->money += tmp_cash;
//
//    }
//    for(auto c : cityMap) {
//        scoreBoard.insert({c.second->money, c.second});
//    }
//    
//    int m; // number of days
//    int k; // number of movements
//    std::cin >> m >> k;
//    
//    int prevday = 0;
//    
//    for (int i = 0; i < k+1; ++i) {
//        int tmp_day = 0;
//        std::string tmp_name;
//        std::string tmp_city;
//        
//        if (i < k) {
//            std::cin >> tmp_day;
//            std::cin >> tmp_name;
//            std::cin >> tmp_city;
//        }
//        
//        bool finished = (i == k);
//        
//        if(finished) { // Zoom to the last day m (the last entry could be many days prior)
//            tmp_day = m;
//        }
//        if(tmp_day != prevday) {
//            auto it2 = scoreBoard.begin();
//            auto it = it2++;
//            if(it2 == scoreBoard.end() || it->first > it2->first) {
//                it->second->days += tmp_day - prevday;
//            }
//        }
//        if(finished) {
//            break;
//        }
//        if(!cityMap[tmp_city]) { // New city mentioned
//            cityMap[tmp_city] = &cities[city_counter++];
//            cityMap[tmp_city]->name = tmp_city;
//        }
//
//        // Update the set and the city data structure itself
//        auto nextplace = cityMap[tmp_city];
//        auto person = personMap[tmp_name];
//        auto prevplace = person->location;
//        auto prevmoney = prevplace->money;
//
//        scoreBoard.erase({prevmoney, prevplace});
//        prevplace->money -= person->money;
//        scoreBoard.insert({prevplace->money, prevplace});
//        scoreBoard.erase({nextplace->money, nextplace});
//        nextplace->money += person->money;
//        scoreBoard.insert({nextplace->money, nextplace});
//        person->location = nextplace;
//        prevday = tmp_day;
//    }
//    
//    std::vector<std::pair<std::string, int> > output;
//    for(auto& iter : scoreBoard) {
//        if(iter.second->days) {
//            output.push_back(std::make_pair(iter.second->name, iter.second->days));
//        }
//    }
//
//    std::sort(output.begin(), output.end());
//    
//    for(auto& iter : output) {
//        std::cout << iter.first << " " << iter.second << "n";
//    }
//    
//    return 0;
//}

#include <string>
#include <set>
#include <map>
#include <unordered_map>
#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>

const int maxn = 10000, maxm = 50000, maxk = 50000;

struct City
{
    long long money;
    int days; // Number of days on the top
    std::string name;
} cities[maxn+maxk];

struct Person
{
    std::string name;
    long long money;
    City* location;
} persons[maxn];

std::unordered_map<std::string, Person*> personMap; // Maps names into people
std::map<std::string, City*> cityMap; // Maps names into cities

class cmp {
public:
    bool operator()(const std::pair<long long, City*>& left, const std::pair<long long, City*>& right) {
        return left.second->money > right.second->money;
    }
};

std::set<std::pair<long long, City*>, cmp> scoreBoard; // The cities ordered by money

int main()
{
    std::ios::sync_with_stdio(false);
    int n, m, k, c = 0;
    std::cin >> n;
    for(int i = 0; i < n; i++)
    {
        std::string name, location; long long money;
        std::cin >> name >> location >> money;
        personMap[name] = &persons[i];
        if(!cityMap[location])
            cityMap[location] = &cities[c++];
        persons[i].location = cityMap[location];
        persons[i].money = money;
        cityMap[location]->name = location;
        cityMap[location]->money += money;
    }
    for(auto c : cityMap)
        scoreBoard.insert( { c.second->money, c.second } );
    std::cin >> m >> k;
    int prevday = 0, day;
    std::string name, place;
    while(true)
    {
        bool finished = (!(std::cin >> day >> name >> place));
        if(finished) // Zoom to the last day m (the last entry could be many days prior)
            day = m;
        if(day != prevday)
        {
            auto it2 = scoreBoard.begin();
            auto it = it2++;
            if(it2 == scoreBoard.end() || it->first > it2->first)
                it->second->days += day-prevday;
        }
        if(finished)
            break;
        if(!cityMap[place]) // New city mentioned
        {
            cityMap[place] = &cities[c++];
            cityMap[place]->name = place;
        }
        
        // Update the set and the city data structure itself
        auto nextplace = cityMap[place];
        auto person = personMap[name];
        auto prevplace = person->location;
        auto prevmoney = prevplace->money;
        scoreBoard.erase( { prevmoney, prevplace } );
        prevplace->money -= person->money;
        scoreBoard.insert( { prevplace->money, prevplace } );
        scoreBoard.erase( { nextplace->money, nextplace } );
        nextplace->money += person->money;
        scoreBoard.insert( { nextplace->money, nextplace } );
        person->location = nextplace;
        prevday = day;
    }
    std::vector<std::pair<std::string, int>> output;
    for(auto& r : scoreBoard)
        if(r.second->days)
            output.push_back( std::make_pair(r.second->name, r.second->days));
    std::sort(output.begin(), output.end());
    for(auto& o : output)
        std::cout << o.first << " " << o.second << "n";
}

//int main() {
//    std::ios::sync_with_stdio(false);
//    int n, m, k, c = 0;
//    std::cin >> n;
//    
//    for (int i = 0; i < n; i++) {
//        std::string name, location;
//        long long money;
//        
//        std::cin >> name >> location >> money;
//        
//        personMap[name] = &persons[i];
//        
//        if(!cityMap[location]) {
//            cityMap[location] = &cities[c++];
//        }
//        
//        persons[i].location = cityMap[location];
//        persons[i].money = money;
//        cityMap[location]->name = location;
//        cityMap[location]->money += money;
//    }
//    
//    for(auto c : cityMap) {
//        scoreBoard.insert( { c.second->money, c.second } );
//    }
//
//    std::cin >> m >> k;
//    int prevday = 0, day;
//    std::string name, place;
//




//    while(true)
//    {
//        bool finished = (!(std::cin >> day >> name >> place));
//        if(finished) // Zoom to the last day m (the last entry could be many days prior)
//            day = m;
//        if(day != prevday)
//        {
//            auto it2 = scoreBoard.begin();
//            auto it = it2++;
//            if(it2 == scoreBoard.end() || it->first > it2->first)
//                it->second->days += day-prevday;
//        }
//        if(finished)
//            break;
//        if(!cityMap[place]) // New city mentioned
//        {
//            cityMap[place] = &cities[c++];
//            cityMap[place]->name = place;
//        }
//        
//        // Update the set and the city data structure itself
//        auto nextplace = cityMap[place];
//        auto person = personMap[name];
//        auto prevplace = person->location;
//        auto prevmoney = prevplace->money;
//        scoreBoard.erase( { prevmoney, prevplace } );
//        prevplace->money -= person->money;
//        scoreBoard.insert( { prevplace->money, prevplace } );
//        scoreBoard.erase( { nextplace->money, nextplace } );
//        nextplace->money += person->money;
//        scoreBoard.insert( { nextplace->money, nextplace } );
//        person->location = nextplace;
//        prevday = day;
//    }
//    
//    std::vector<std::pair<std::string, int> > output;
//    for(auto& r : scoreBoard)
//        if(r.second->days)
//            output.push_back( std::make_pair(r.second->name, r.second->days));
//    std::sort(output.begin(), output.end());
//    for(auto& o : output)
//        std::cout << o.first << " " << o.second << "n";
//}
