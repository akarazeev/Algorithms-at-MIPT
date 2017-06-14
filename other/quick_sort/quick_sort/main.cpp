//
//  main.cpp
//  quick_sort
//
//  Created by Anton Karazeev on 12/06/2017.
//  Copyright © 2017 Anton Karazeev. All rights reserved.
//

#include <iostream>
#include <vector>

int partition(std::vector<int>& array, int left, int right) {
    int i = left;
    int j = right;
    int ref = array[(i + j) / 2];
    
    while (i < j) {
        while (ref < array[j]) {
            --j;
        }
        while (ref > array[i]) {
            ++i;
        }
        if (i < j) {
            std::swap(array[i], array[j]);
            --j;
            ++i;
        }
    }
    
//    return j;
    return (left + right) / 2;
}

int find_order_statistic(std::vector<int>& array, int k) {
    int left = 0;
    int right = static_cast<int>(array.size()) - 1;
    
    while (true) {
        int mid = partition(array, left, right);
        
        if (mid == k) {
            return array[mid];
        } else if (k < mid) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
}

void quick_sort(std::vector<int>& array, int left, int right) {
    if (left < right) {
        int tmp = partition(array, left, right);
        quick_sort(array, left, tmp);
        quick_sort(array, tmp + 1, right);
    }
}

void quick_sort(std::vector<int>& array) {
    quick_sort(array, 0, static_cast<int>(array.size()) - 1);
}

int main() {
    std::vector<int> array = {33, 42, 89, 23, 98, 11};
    
    int order = 2;
    std::cout << order << "_order statistic: " << find_order_statistic(array, order) << std::endl;
    
//    quick_sort(array);

    for (int i = 0; i < array.size(); ++i) {
        std::cout << array[i] << " " << std::endl;
    }
    
    return 0;
}
