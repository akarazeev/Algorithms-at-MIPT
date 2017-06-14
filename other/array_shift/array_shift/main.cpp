//
//  main.cpp
//  array_shift
//
//  Created by Anton Karazeev on 12/06/2017.
//  Copyright © 2017 Anton Karazeev. All rights reserved.
//

#include <iostream>

int* array_shift(int* array, int array_size, int shift) {
    for (int num = 0; num < shift; ++num) {
        for (int i = array_size-1; i >= 1; --i) {
            std::swap(array[i-1], array[i]);
        }
    }
    
    return array;
}

int main() {
    int array[] = {1,2,3,4,5};
    
    int* ans = array_shift(array, 5, 2);
    
    for (int i = 0; i < 5; ++i) {
        std::cout << ans[i] << std::endl;
    }
    
    return 0;
}
