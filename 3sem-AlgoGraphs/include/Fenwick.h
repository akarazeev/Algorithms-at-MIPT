//
//  Fenwick.h
//  Fenwick
//
//  Created by Anton Wetret on 12/11/15.
//  Copyright © 2015 Anton Karazeev. All rights reserved.
//

#ifndef Fenwick_h
#define Fenwick_h

#include <vector>

template <typename T>
class Fenwick {
public:
    Fenwick(int n);
    Fenwick(std::vector<T> data);
    T PartSum(int x);
    T Sum(int l, int r);
    void Modify(int x, T d);
    void Set(int x, T val);
private:
    std::vector<T> data_;
    std::vector<T> partsum_;
};

template <typename T>
Fenwick<T>::Fenwick(int n): data_(std::vector<T> (n, 0)), partsum_(std::vector<T> (n, 0)) {
    
}

template <typename T>
Fenwick<T>::Fenwick(std::vector<T> data) {
    data_ = data;
    partsum_ = std::vector<T> (data_.size());
    for (int i = 0; i < data_.size(); ++i) {
        for (int j = i&(i+1); j <= i; ++j) {
            partsum_[i] += data_[j];
        }
    }
}

template <typename T>
T Fenwick<T>::PartSum(int x) {
    T res = 0;
    while (x >= 0) {
        res += partsum_[x];
        x = (x&(x+1)) - 1;
    }
    return res;
}

template <typename T>
T Fenwick<T>::Sum(int l, int r) {
    int res = PartSum(r) - PartSum(l-1);
    return res;
}

template <typename T>
void Fenwick<T>::Modify(int x, T d) {
    data_[x] += d;
    while (x < data_.size()) {
        partsum_[x] += d;
        x = x|(x+1);
    }
}

template <typename T>
void Fenwick<T>::Set(int x, T val) {
    int d = val - data_[x];
    data_[x] = val;
    Modify(x, d);
}

#endif /* Fenwick_h */
