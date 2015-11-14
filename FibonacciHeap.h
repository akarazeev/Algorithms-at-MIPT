//
//  FibonacciHeap.h
//  SCC
//
//  Created by Anton Wetret on 10/2/15.
//  Copyright © 2015 Anton Karazeev. All rights reserved.
//

#ifndef FibonacciHeap_h
#define FibonacciHeap_h

#define trace(x) std::cout << x << std::endl;

#include <list>

template <typename T, typename C>
struct Node {
    Node();
    Node(T key);
    Node(T key, int new_degree);
    Node(Node<T, C>& other);
    
    int degree;
    T key;
    std::shared_ptr<Node<T, C> > p;       // pointer to parent Node
    bool mark;
    std::list<std::shared_ptr<Node<T, C> > > children;
};

template <typename T, typename C = std::less<int> >
class FibHeap {
public:
    FibHeap();
    
    void Insert(T x);
    void Merge(FibHeap<T, C>& other_heap);
    std::shared_ptr<Node<T, C> > ExtractMin();
    void Consolidate();
private:
    int size_;
    std::shared_ptr<Node<T, C> > min_; // pointer to Node with min key
    std::list<std::shared_ptr<Node<T, C> > > roots_;
};

#pragma mark Implementation

#pragma mark > Class Node

template <typename T, typename C>
Node<T, C>::Node() {
    
}

template <typename T, typename C>
Node<T, C>::Node(T val): key(val) {
    
}

template <typename T, typename C>
Node<T, C>::Node(T val, int new_degree): key(val), degree(new_degree) {
    
}

template <typename T, typename C>
Node<T, C>::Node(Node<T, C>& other): key(other.key), degree(other.degree), children(other.children) {
    
}

#pragma mark > Class FibHeap

template <typename T, typename C>
FibHeap<T, C>::FibHeap(): size_(0) {
    
}

template <typename T, typename C>
void FibHeap<T, C>::Insert(T x) {
    std::shared_ptr<Node<T, C> > p (new Node<T, C>(x, 0));
    if (roots_.size() == 0) {
        roots_.push_front(p);
        min_ = *roots_.begin();
        size_ = 1;
    } else {
        FibHeap<T, C> tmp;
        tmp.roots_.push_front(p);
        tmp.min_ = p;
        tmp.size_ = 1;
        this->Merge(tmp);
    }
}

template <typename T, typename C>
std::shared_ptr<Node<T, C> > FibHeap<T, C>::ExtractMin() {
//    Fib_Heap_Extract_Min(H)
//    1 z ← min[H]
//    2 if z ≠ NULL
//    3    then for для каждого дочернего по отношению к z узла x
//    4             do Добавить x в список корней H
//    5                p[x] ← NULL
//    6         Удалить z из списка корней H
//    7         if z = right[z]
//    8            then min[H] ← NULL
//    9            else min[H] ← right[z]
//   10                 Consolidate(H)
//   11         n[H] ← n[H] - 1
//   12 return z
    std::shared_ptr<Node<T, C> > res = min_;
    if (res != 0) {
        for (auto it = res->children.begin(); it != res->children.end(); ++it) {
            roots_.push_front(*it);
        }
        auto to_del = std::find(roots_.begin(), roots_.end(), res);
        auto right = std::next(to_del);
        roots_.erase(to_del);
        
        
        if (res == *right) {
            min_ = nullptr;
        } else {
            min_ = *right;
            this->Consolidate();
        }
        size_ -= 1;
    }
    return res;
}

template <typename T, typename C>
void FibHeap<T, C>::Merge(FibHeap<T, C>& other_heap) {
    roots_.merge(other_heap.roots_);
    if (other_heap.min_->key < min_->key) {
        min_ = other_heap.min_;
    }
    size_ += other_heap.size_;
}

template <typename T, typename C>
void FibHeap<T, C>::Consolidate() {
    std::vector<std::shared_ptr<Node<T, C> > > a(size_);
    for (auto it = roots_.begin(); it != roots_.end();) {
        std::shared_ptr<Node<T, C> > x = *it;
        ++it;
        if (x != 0) {
            int d = x->degree;
            while (a[d] != 0) {
                std::shared_ptr<Node<T, C> > y = a[d];
                if (x->key > y->key) {
                    std::swap(x, y);
                }
                
                auto to_del = std::find(roots_.begin(), roots_.end(), y);
                roots_.erase(to_del);
                x->children.push_front(y);
                x->degree += 1;
                y->mark = false;
                
                a[d] = nullptr;
                ++d;
            }
            a[d] = x;
        }
    }
    min_ = nullptr;
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] != nullptr) {
            roots_.push_front(a[i]);
            if (min_ == nullptr || a[i]->key < min_->key) {
                min_ = a[i];
            }
        }
    }
}

#endif /* FibonacciHeap_h */
