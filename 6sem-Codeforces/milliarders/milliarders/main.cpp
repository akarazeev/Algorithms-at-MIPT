//
//  main.cpp
//  C task - milliarders
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

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>

template <typename T, typename COMP>
class Heap {
public:
    Heap() {
        
    }
    
    Heap(std::vector<T> data) : data_(data) {
        this->heapify();
    }
    
    void heapify() {
        for (int i = static_cast<int>(data_.size()) - 1; i >= 0; --i) {
            sift_up(i);
        }
    }
    
    void insert(T value) {
        data_.push_back(value);
        sift_up(static_cast<int>(data_.size()) - 1);
    }
    
    void sift_up(int index) {
        while (COMP()(data_[index], data_[(index - 1) / 2])) {
            std::swap(data_[index], data_[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }
    
    void sift_down(int index) {
        while ((2 * index) + 1 < data_.size()) {
            int index_left = 2 * index + 1;
            int index_right = 2 * index + 2;
            int index_tmp = index_left;
            
            if (index_right < data_.size() and COMP()(data_[index_right], data_[index_left])) {
                index_tmp = index_right;
            }
            
            if (COMP()(data_[index], data_[index_tmp])) {
                return;
            }

            std::swap(data_[index], data_[index_tmp]);
            index = index_tmp;
        }
    }
    
    T extract_min() {
        T ans = data_[0];
        data_[0] = data_[static_cast<int>(data_.size()) - 1];
        data_.pop_back();
        sift_down(0);
        return ans;
    }
    
    void erase(T val) {
        for (auto iter = data_.begin(); iter != data_.end(); ++iter) {
            if (*iter == val) {
                data_.erase(iter);
                break;
            }
        }
        this->heapify();
    }

    std::vector<T> data_;
};

class Location {
public:
    std::string name;
    long long money;
    int topdays;
};

class Milliarder {
public:
    std::string name;
    long long money;
    Location* location;
};

class cmp {
public:
    bool operator()(const Location* left, const Location* right) {
        if (left->money == right->money) {
            return left->name > right->name;
        } else {
            return left->money > right->money;
        }
    }
};

class cmp2 {
public:
    bool operator()(const std::pair<int, int> left, const std::pair<int, int> right) {
        return left.first > right.first;
    }
};

int main() {
    int max_mil = 10000; // max number of milliarders
    int max_mov = 50000; // max number of registered movements
    
    std::vector<Milliarder> milliarders(max_mil); // all milliarders
    std::vector<Location> locations(max_mil + max_mov); // all locations
    
    std::map<std::string, Milliarder*> milliarders_mapping; // milliarder_name -> milliarder
    std::map<std::string, Location*> location_mapping; // location_name -> location
//    std::set<Location*, cmp> answer; // pointer in order to increase first element when needed
    Heap<Location*, cmp> answer_heap;
    
    int n; // number of names to read
    std::cin >> n;
    
    int loc_counter = 0; // counter of unique locations

    /* Read name, initial location and money */
    for (int i = 0; i < n; ++i) {
        std::string milliarder_name;
        std::string location_name;
        long long money;
        
        std::cin >> milliarder_name;
        std::cin >> location_name;
        std::cin >> money;
        
        // link to i-th milliarder
        milliarders_mapping[milliarder_name] = &milliarders[i];
        
        // when new location is found
        if (!location_mapping[location_name]) {
            // link to loc_counter-th location
            location_mapping[location_name] = &locations[loc_counter];
            ++loc_counter;
        }
        
        milliarders[i].location = location_mapping[location_name];
        milliarders[i].money = money;
        location_mapping[location_name]->name = location_name;
        location_mapping[location_name]->money += money;
    }

    /* Insert all cities from location_mapping to answer */
    for (auto iter = location_mapping.begin(); iter != location_mapping.end(); ++iter) {
        // iter = {money, location}
//        answer.insert(iter->second);
        answer_heap.insert(iter->second);
    }

    int m; // total number of days with available data
    int k; // number of registered movements
    std::cin >> m;
    std::cin >> k;
    
    int prevday = 0;
    int day = -1;
    
    std::string milliarder_name;
    std::string location_name;

    /* Read registered movements */
    for (int i = 0; i < k; ++i) {
        std::cin >> day;
        std::cin >> milliarder_name;
        std::cin >> location_name;
        
        if (day != prevday) {
//            std::set<Location*, cmp>::iterator it2 = answer.begin();
//            std::set<Location*, cmp>::iterator it = it2;

            auto it_heap = answer_heap.data_.begin();
            auto it2_heap = it_heap;

            ++it2_heap;
            // check whether top element is the greatest
            if (it2_heap != answer_heap.data_.end()) {
                if ((*it2_heap)->money < (*std::next(it2_heap))->money) {
                    ++it2_heap;
                }
            }

//            ++it2;
//             check whether top element is the greatest
//            if (it2 == answer.end() or (*it)->money > (*it2)->money) {
//                (*it)->topdays += day - prevday;
//            }
            if (it2_heap == answer_heap.data_.end() or (*it_heap)->money > (*it2_heap)->money) {
                (*it_heap)->topdays += day - prevday;
            }
        }

        // when new location is found
        if (!location_mapping[location_name]) {
            location_mapping[location_name] = &locations[loc_counter];
            ++loc_counter;
            location_mapping[location_name]->name = location_name;
        }
        
        // get Milliarder corresponding to milliarder_name
        Milliarder* milliarder = milliarders_mapping[milliarder_name];
        
        // old location of milliarder
        Location* oldloc = milliarder->location;
        
        // get Location corresponding to location_name
        // new location milliarder
        Location* newloc = location_mapping[location_name];
        
        /* Update elements in answer */
        
        // update old location
//        answer.erase(oldloc);
        answer_heap.erase(oldloc);
        oldloc->money -= milliarder->money;
//        answer.insert(oldloc);
        answer_heap.insert(oldloc);
        
        // update new location
//        answer.erase(newloc);
        answer_heap.erase(newloc);
        newloc->money += milliarder->money;
//        answer.insert(newloc);
        answer_heap.insert(newloc);
        
        // milliarder moved to new location
        milliarder->location = newloc;
        prevday = day;
    }
    
    day = m;
    if (day != prevday) {
//        std::set<Location*, cmp>::iterator it2 = answer.begin();
//        std::set<Location*, cmp>::iterator it = it2;
        
        auto it_heap = answer_heap.data_.begin();
        auto it2_heap = it_heap;
        
        ++it2_heap;
        // check whether top element is the greatest
        if (it2_heap != answer_heap.data_.end()) {
            if ((*it2_heap)->money < (*std::next(it2_heap))->money) {
                ++it2_heap;
            }
        }
        
//        ++it2;
        // check whether top element is the greatest
//        if (it2 == answer.end() or (*it)->money > (*it2)->money) {
//            (*it)->topdays += day - prevday;
//        }
        if (it2_heap == answer_heap.data_.end() or (*it_heap)->money > (*it2_heap)->money) {
            (*it_heap)->topdays += day - prevday;
        }
    }
    
    /* Build output vector */
    std::vector<std::pair<std::string, int> > output;
//    for (auto iter = answer.begin(); iter != answer.end(); ++iter) {
//        // whether the location was at the top more than or equal to 1 time
//        if ((*iter)->topdays >= 1) {
//            output.push_back({(*iter)->name, (*iter)->topdays});
//        }
//    }
    for (auto iter = answer_heap.data_.begin(); iter != answer_heap.data_.end(); ++iter) {
        // whether the location was at the top more than or equal to 1 time
        if ((*iter)->topdays >= 1) {
            output.push_back({(*iter)->name, (*iter)->topdays});
        }
    }
    
    /* Sort output vector */
    std::sort(output.begin(), output.end());
    
    /* Output */
    for (int i = 0; i < output.size(); ++i) {
        std::cout << output[i].first << ' ' << output[i].second << std::endl;
    }
    
    return 0;
}
