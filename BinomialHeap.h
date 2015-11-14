//
//  BinomialHeap.h
//  SCC
//
//  Created by Anton Wetret on 25/09/15.
//  Copyright © 2015 Anton Karazeev. All rights reserved.
//

#ifndef BinomialHeap_h
#define BinomialHeap_h

#define trace(x) std::cout << x << std::endl;

#include <list>
#include <iterator>
#include <algorithm>

template <typename T, typename C>
struct Node {
    Node();
    Node(T key);
    Node(T key, int new_degree);
    Node(Node<T, C>& other);
    
    int degree;
    T key;
    std::list<std::shared_ptr<Node<T, C> > > children;
};

template <typename T, typename C = std::less<int> >
class BinHeap {
public:
    BinHeap();
    
    void Merge(BinHeap<T, C>& other_heap);
    void push(T x);
    void pop();
    const T& top();
    int size();
    std::shared_ptr<Node<T, C> > GetMin();
    T ExtractMin();
    //TODO: Add delete_key and decrease_key
    
private:
    int size_;
    typename std::list<std::shared_ptr<Node<T, C> > >::iterator min_;
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

#pragma mark > Class BinHeap

template <typename T, typename C>
BinHeap<T, C>::BinHeap(): size_(0) {
    
}

template <typename T, typename C>
void BinHeap<T, C>::push(T x) {
    std::shared_ptr<Node<T, C> > p (new Node<T, C>(x, 0));
    if (roots_.size() == 0) {
        roots_.push_front(p);
        min_ = roots_.begin();
        size_ = 1;
    } else {
        BinHeap<T, C> tmp;
        tmp.roots_.push_front(p);
        tmp.size_ = 1;
        this->Merge(tmp);
    }
}

template <typename T, typename C>
std::shared_ptr<Node<T, C> > BinHeap<T, C>::GetMin() {
    return min_;
}

template <typename T, typename C>
const T& BinHeap<T, C>::top() {
    return (*min_)->key;
}

template <typename T, typename C>
int BinHeap<T, C>::size() {
    return size_;
}

template <typename T, typename C>
void BinHeap<T, C>::Merge(BinHeap<T, C>& other_heap) {
    auto it1 = (this->roots_).begin();
    auto it2 = other_heap.roots_.begin();
    size_ += other_heap.size_;
    while (it1 != (this->roots_).end() && it2 != other_heap.roots_.end()) {
        if ((*it1)->degree < (*it2)->degree) {
            ++it1;
            this->roots_.insert(it1, std::shared_ptr<Node<T, C> > (new Node<T, C> (**it2)));
            ++it2;
        } else if((*it1)->degree >= (*it2)->degree) {
            this->roots_.insert(it1, std::shared_ptr<Node<T, C> > (new Node<T, C> (**it2)));
            ++it2;
            ++it1;
        }
    }
    if (it1 == this->roots_.end()) {
        while (it2 != other_heap.roots_.end()) {
            this->roots_.insert(it1, std::shared_ptr<Node<T, C> > (new Node<T, C> (**it2)));
            ++it2;
        }
    }
    auto it = this->roots_.begin();
    while (std::next(it) != this->roots_.end()) {
        if ((*it)->degree == (*std::next(it))->degree) {
            auto tmp = std::next(it);
            if (C()((*it)->key, (*tmp)->key)) {
                (*it)->children.push_front(*tmp);
                (*it)->degree += 1;
                this->roots_.erase(tmp);
                continue;
            } else {
                (*tmp)->children.push_front(*it);
                (*tmp)->degree += 1;
                this->roots_.erase(it);
                continue;
            }
        }
        ++it;
    }
    min_ = std::min_element(this->roots_.begin(), this->roots_.end(), [](std::shared_ptr<Node<T, C> > a, std::shared_ptr<Node<T, C> > b) {
        return C()(a->key, b->key);
    });
}

template <typename T, typename C>
T BinHeap<T, C>::ExtractMin() {
    T res = (*min_)->key;
    BinHeap<T, C> tmp;
    for (auto it : (*min_)->children) {
        tmp.roots_.push_front(it);
    }
    roots_.erase(min_);
    size_ -= 1;
    this->Merge(tmp);
    return res;
}

template <typename T, typename C>
void BinHeap<T, C>::pop() {
    BinHeap<T, C> tmp;
    for (auto it : (*min_)->children) {
        tmp.roots_.push_front(it);
    }
    roots_.erase(min_);
    size_ -= 1;
    this->Merge(tmp);
}

#endif /* BinomialHeap_h */
