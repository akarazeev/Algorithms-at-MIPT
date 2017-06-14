//
//  main.cpp
//  power_set
//
//  Created by Anton Karazeev on 12/06/2017.
//  Copyright © 2017 Anton Karazeev. All rights reserved.
//

#include <iostream>
#include <cmath>


void power_set(int set_size, char* set) {
    int power_set_size = std::pow(2, set_size);
    
    for (int i = 0; i < power_set_size; ++i) {
        std::cout << "set#" << i+1 << ": ";
        for (int j = 0; j < set_size; ++j) {
            if ((1 << j) & i) {
                std::cout << set[j] << ' ';
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    int size = 5;
    char set[] = {'a', 'b', 'c', 'd', 'e'};
    
    power_set(size, set);
    
    return 0;
}
