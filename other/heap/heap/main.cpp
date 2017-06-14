//
//  main.cpp
//  heap
//
//  Created by Anton Karazeev on 12/06/2017.
//  Copyright © 2017 Anton Karazeev. All rights reserved.
//

#include <iostream>
#include <vector>

class Heap {
public:
    Heap() {
        
    }
    
    Heap(std::vector<int> data) : data_(data) {
        // Heapify.
        for (int i = static_cast<int>(data_.size()) - 1; i >= 0; --i) {
            sift_up(i);
        }
    }
    
    void insert(int value) {
        data_.push_back(value);
        sift_up(static_cast<int>(data_.size()) - 1);
    }
    
    void sift_up(int index) {
        while (data_[index] < data_[(index - 1) / 2]) {
            std::swap(data_[index], data_[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }
    
    void sift_down(int index) {
        while ((2 * index) + 1 < data_.size()) {
            int index_left = 2 * index + 1;
            int index_right = 2 * index + 2;
            int index_tmp = index_left;
            
            if (index_right < data_.size() and data_[index_right] < data_[index_left]) {
                index_tmp = index_right;
            }
            if (data_[index] <= data_[index_tmp]) {
                return;
            }
            std::swap(data_[index], data_[index_tmp]);
            index = index_tmp;
        }
    }
    
    int extract_min() {
        int ans = data_[0];
        data_[0] = data_[static_cast<int>(data_.size()) - 1];
        data_.pop_back();
        sift_down(0);
        return ans;
    }
    
    void traverse() {
        for (int i = 0; i < data_.size(); ++i) {
            std::cout << data_[i] << " ";
        }
        std::cout << std::endl;
    }
    
    std::vector<int> get_data() {
        return data_;
    }
    
private:
    std::vector<int> data_;
};

int main() {
    Heap h;
    
    h.insert(4);
    h.insert(7);
    h.insert(2);
    h.insert(1);
    h.insert(5);
    h.insert(8);
    h.insert(9);
    
    h.traverse();
    
    std::cout << h.extract_min() << std::endl;
    h.traverse();
    
    std::cout << h.extract_min() << std::endl;
    h.traverse();
    
    std::vector<int> array = {4, 7, 2, 1, 10, 3};
    h = Heap(array);
    h.traverse();
    
    return 0;
}
