//
//  main.cpp
//  fox_and_dinner
//
//  Created by Anton Karazeev on 07/08/2017.
//  Copyright © 2017 Anton Karazeev. All rights reserved.
//

#include <iostream>
#include <vector>

int main(int argc, const char* argv[]) {
    int n; // number of foxes
    
    std::cin >> n;
    
    std::vector<int> foxes;
    
    for (int i = 0; i < n; ++i) {
        int tmp;
        std::cin >> tmp;
        foxes.push_back(tmp);
    }
    
    for (int i = 0; i < foxes.size(); ++i) {
        std::cout << foxes[i] << ' ';
    }
    
    return 0;
}
