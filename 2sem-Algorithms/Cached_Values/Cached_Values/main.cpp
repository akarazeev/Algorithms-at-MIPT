//
//  main.cpp
//  Cached_Values
//
//  Created by Anton Wetret on 09/05/15.
//  Copyright (c) 2015 Anton Karazeev. All rights reserved.
//

#include <iostream>
#include <deque>

using namespace std;

template <typename A, typename V>
class CachedFunction {
public:
    CachedFunction(V (*func)(A), int M): func_(func) ,size_(M) {
        
    }
    V operator()(A x) {
        auto it = cach_.begin();
        while (it != cach_.end() && it->first != x) ++it;
        if (it == cach_.end()) {
            cout << 'N' << ' ';
            if (cach_.size() < size_) {
                V buf = func_(x);
                cach_.push_front(pair<A, V>(x, buf));
                return buf;
            }
            else {
                V buf = func_(x);
                cach_.pop_back();
                cach_.push_front(pair<A, V>(x, buf));
                return buf;
            }
        }
        else return it->second;
    }
private:
    deque<pair<A, V> > cach_;
    int size_;
    V (*func_)(A);
};

int f(int x) {
    return x==1 ? 1 : x * f(x-1);
}

int main() {
    CachedFunction<int, int> c(f, 3);
    cout << c(5) << endl;
    cout << c(4) << endl;
    cout << c(5) << endl;
    cout << c(3) << endl;
    cout << c(4) << endl;
    cout << c(2) << endl;
    cout << c(1) << endl;
    cout << c(5) << endl;
    
    return 0;
}
