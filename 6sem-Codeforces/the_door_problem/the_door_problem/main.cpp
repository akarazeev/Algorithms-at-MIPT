//
//  main.cpp
//  the_door_problem
//
//  Created by Anton Karazeev on 07/08/2017.
//  Copyright © 2017 Anton Karazeev. All rights reserved.
//

#include <iostream>
#include <vector>

int main(int argc, const char* argv[]) {
    int n; // number of rooms
    int m; // number of switches
    
    std::cin >> n >> m;
    
    std::vector<int> init_states;
    
    for (int i = 0; i < n; ++i) {
        int tmp;
        std::cin >> tmp;
        init_states.push_back(tmp);
    }
    
    std::vector<std::vector<int> > rooms;

    for (int i = 0; i < m; ++i) {
        int tmp;
        std::cin >> tmp;
        std::vector<int> tmp_vector;
        for (int j = 0; j < tmp; ++j) {
            int room_num;
            std::cin >> room_num;
            tmp_vector.push_back(room_num);
        }
        rooms.push_back(tmp_vector);
    }
    
    for (int i = 0; i < rooms.size(); ++i) {
        for (int j = 0; j < rooms[i].size(); ++j) {
            std::cout << rooms[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    
    return 0;
}
