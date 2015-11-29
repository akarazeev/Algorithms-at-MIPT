//
//  Graph.h
//  Graph
//
//  Created by Anton Wetret on 13/05/15.
//  Copyright (c) 2015 Anton Karazeev. All rights reserved.
//

#ifndef __Graph__Graph__
#define __Graph__Graph__

#define trace(x) std::cout << x << std::endl;

#include <vector>
#include <list>
#include <deque>
#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <set>
#include <stack>
#include <algorithm>
#include <bitset>
#include <tuple>
#include <assert.h>

const int INF = 1000000;

enum color{WHITE, GREY, BLACK};

template <typename T, typename S>
class vertex {
public:
    vertex();
    vertex(T val);
    void operator=(vertex& other);
    bool IsSink();
    
    bool exist_ = 0;
    T value_;
    int label_ = 0;
    int low_ = 0;
    /* Adjacency list with ID and weight of edge */
    std::list<std::pair<int, S> > adj_;
    int col_ = WHITE;
};

/*
 T - type of vertex
 S - type of weight of edge
 R - is oriented
 */
template <typename T, typename S, bool R = 0>
class graph {
public:
    graph();
    graph(int n);
    graph(const graph<T, S, R>& g);
    
    graph<T, S, R> Flipped();
    void Flip();
    int DataSize();
    int NumbOfVert();
    
    void DeleteVertex(T src);
    void DeleteEdge(T src1, T src2);
    
    void AddVertex(int x, vertex<T, S>& v);
    void AddVertex(int x, T val);
    void AddEdge(int x, int y);
    void AddEdgeVal(T val1, T val2, S weight);
    void AddEdgeVal(T val1, T val2);
    
    bool ExistVal(T val);
    bool ExistEdge(int x, int y);
    bool IsAllBlack();
    int GetNotBlackID();
    
    bool IsSinkVal(T val);
    bool IsSink(int x);
    bool IsSource(T val);
    bool HasWhiteAdjVertexVal(T val);
    bool HasWhiteAdjVertex(int x);
    
    void BFS(T val);
    void DFS(T val);
    std::vector<T> BFStoIt(T val);
    std::vector<T> DFStoIt(T val);
    void DFSToStrong(T val, std::set<std::pair<T, T> >& res);
    
    void Kosaraju();
    void StrongConnect(int x, int& step, std::stack<int>& stk, std::vector<std::set<T> >& scc);
    void Tarjan();
    // x - start searching from this vertex
    void BellmanFord(int x);
    void FloydWarshall();
    void Dijkstra(int x);
    
    void Prim();
    void Kruscal();
    
    std::set<std::pair<T, T> > ToStrong();
    
    std::vector<T> GetVertexFrom(T src) const;
    std::vector<T> GetVertexTo(T src) const;
    std::vector<std::pair<T, T> > GetEdgeFrom(T src) const;
    std::vector<std::pair<T, T> > GetEdgeTo(T src) const;
    std::map<T, int> GetExisted();
    std::set<T> GetDepend();
    std::set<T> GetSources();
    std::set<T> GetSinks();
    
////    FIXME: Doesn't work!
//        class bfs_const_iterator {
//        public:
//            bfs_const_iterator(std::vector<T>& bfs_vertex, typename std::vector<T>::const_iterator it);
//            bfs_const_iterator operator++();
//            bfs_const_iterator operator++(int);
//            T operator*() const;
//            bool operator!=(const bfs_const_iterator other) const;
//        private:
//            std::vector<T> bfs_vertex_;
//            typename std::vector<T>::const_iterator it_;
//        };
//    
//        bfs_const_iterator bfs_begin(T val) {
//            std::vector<T> vec = BFStoIt(val);
//            bfs_const_iterator it(vec, vec.cbegin());
//            return it;
//        }
//    
//        bfs_const_iterator bfs_end(T val) {
//            std::vector<T> vec = BFStoIt(val);
//            bfs_const_iterator it(vec, vec.cend());
//            return it;
//        }
    
    template <typename TT, typename SS, bool RR>
    friend std::ostream& operator<<(std::ostream& stream, graph<TT, SS, RR>& g);
    template <typename TT, typename SS, bool RR>
    friend std::istream& operator>>(std::istream& stream, graph<TT, SS, RR>& g);
private:
    std::vector<vertex<T, S> > data_; // Main structure of graph
    std::map<T, int> existed_; // Map of existed T values with their ID
    std::set<T> dependence_; // Here I write names of classes which are in cyclic dependence
    int n_; // Quantity of vertexes
    bool oriented_;
};

template <typename T, typename S, bool R>
std::istream& operator>>(std::istream& stream, graph<T, S, R>& g);

template <typename T, typename S, bool R>
std::ostream& operator<<(std::ostream& stream, graph<T, S, R>& g);

#pragma mark Implementation

//#pragma mark > Class BFS Iterator
//
//template <typename T, typename S, bool R>
//graph<T, S, R>::bfs_const_iterator::bfs_const_iterator(std::vector<T>& bfs_vertex,
//                                                      typename std::vector<T>::const_iterator it): bfs_vertex_(bfs_vertex),
//                                                                                                   it_(it) {
//
//}
//
//template <typename T, typename S, bool R>
//typename graph<T, S, R>::bfs_const_iterator graph<T, S, R>::bfs_const_iterator::operator++() {
//    ++it_;
//    return *this;
//}
//
//template <typename T, typename S, bool R>
//typename graph<T, S, R>::bfs_const_iterator graph<T, S, R>::bfs_const_iterator::operator++(int) {
//    ++it_;
//    bfs_const_iterator it2 = *this;
//    return it2;
//}
//
//template <typename T, typename S, bool R>
//T graph<T, S, R>::bfs_const_iterator::operator*() const {
//    return *it_;
//}
//
//template <typename T, typename S, bool R>
//bool graph<T, S, R>::bfs_const_iterator::operator!=(const bfs_const_iterator other) const {
//    return it_ != other.it_;
//}

#pragma mark > Class Vertex

template <typename T, typename S>
vertex<T, S>::vertex() {
    
}

template <typename T, typename S>
vertex<T, S>::vertex(T val): value_(val) {
    
}

template <typename T, typename S>
bool vertex<T, S>::IsSink() {
    return adj_.size() == 0;
}

template <typename T, typename S>
void vertex<T, S>::operator=(vertex<T, S>& other) {
    exist_ = other.exist_;
    value_ = other.value_;
    adj_ = other.adj_;
    col_ = other.col_;
}

#pragma mark > Class Graph

template <typename T, typename S, bool R>
graph<T, S, R>::graph(): oriented_(R) {
    
}

template <typename T, typename S, bool R>
graph<T, S, R>::graph(int n): n_(n), oriented_(R), data_(std::vector<vertex<T, S> >(n)) {
    
}

template <typename T, typename S, bool R>
graph<T, S, R>::graph(const graph<T, S, R>& g): data_(g.data_), n_(g.n_), oriented_(g.oriented_),
                                                existed_(g.existed_), dependence_(g.dependence_) {
    
}

template <typename T, typename S, bool R>
bool graph<T, S, R>::IsSink(int x) {
    return data_[x].adj_.size() == 0;
}

template <typename T, typename S, bool R>
bool graph<T, S, R>::IsSinkVal(T val) {
    return data_[existed_.find(val)->second].adj_.size() == 0;
}

template <typename T, typename S, bool R>
bool graph<T, S, R>::IsSource(T val) {
    graph<T, S, R> buf(this->Flipped());
    return buf.data_[buf.existed_.find(val)->second].adj_.size() == 0;
}

template <typename T, typename S, bool R>
bool graph<T, S, R>::HasWhiteAdjVertexVal(T val) {
    bool res = 0;
    int x = existed_.find(val)->second;
    for (auto it = data_[x].adj_.begin(); it != data_[x].adj_.end(); ++it) {
        if (data_[it->first].col_ == WHITE) {
            res = 1;
            break;
        }
    }
    return res;
}

template <typename T, typename S, bool R>
bool graph<T, S, R>::HasWhiteAdjVertex(int x) {
    bool res = 0;
    for (auto it = data_[x].adj_.begin(); it != data_[x].adj_.end(); ++it) {
        if (data_[it->first].col_ == WHITE) {
            res = 1;
            break;
        }
    }
    return res;
}

template <typename T, typename S, bool R>
void graph<T, S, R>::Flip() {
    if (oriented_ == 1) {
        std::vector<vertex<T, S> > data(n_);
        for (int i = 0; i < n_; ++i) {
            data[i].value_ = data_[i].value_;
            data[i].exist_ = data_[i].exist_;
        }
        for (int i = 0; i < n_; ++i) {
            for (auto it = data_[i].adj_.begin(); it != data_[i].adj_.end(); ++it) {
                data[it->first].adj_.push_back(std::pair<int, S>(i, it->second));
            }
        }
        data_ = data;
    }
}

template <typename T, typename S, bool R>
graph<T, S, R> graph<T, S, R>::Flipped() {
    graph<T, S, R> res(*this);
    if (res.oriented_ == 1) {
        std::vector<vertex<T, S> > data(n_);
        for (int i = 0; i < n_; ++i) {
            data[i].value_ = res.data_[i].value_;
        }
        for (int i = 0; i < n_; ++i) {
            for (auto it = res.data_[i].adj_.begin(); it != res.data_[i].adj_.end(); ++it) {
                data[it->first].adj_.push_back(std::pair<int, S>(i, it->second));
            }
        }
        res.data_ = data;
    }
    return res;
}

template <typename T, typename S, bool R>
int graph<T, S, R>::DataSize() {
    return n_;
}

template <typename T, typename S, bool R>
int graph<T, S, R>::NumbOfVert() {
    int res = 0;
    for (int i = 0; i < n_; ++i) {
        if (data_[i].exist_) {
            res += 1;
        }
    }
    return res;
}

template <typename T, typename S, bool R>
void graph<T, S, R>::DeleteEdge(T src1, T src2) {
    if (oriented_ == 1) {
        int x = existed_.find(src1)->second;
        int y = existed_.find(src2)->second;
        auto it = data_[x].adj_.begin();
        while (it->first != y && it != data_[x].adj_.end()) ++it;
        if (it != data_[x].adj_.end()) data_[x].adj_.erase(it);
    } else {
        int x = existed_.find(src1)->second;
        int y = existed_.find(src2)->second;
        
        auto it = data_[x].adj_.begin();
        while (it->first != y && it != data_[x].adj_.end()) ++it;
        if (it != data_[x].adj_.end()) data_[x].adj_.erase(it);
        
        it = data_[y].adj_.begin();
        while (it->first != x && it != data_[y].adj_.end()) ++it;
        if (it != data_[y].adj_.end()) data_[y].adj_.erase(it);
    }
}

template <typename T, typename S, bool R>
void graph<T, S, R>::DeleteVertex(T src) {
    int x = existed_.find(src)->second;
    existed_.erase(existed_.find(src));
    data_[x].value_ = NULL;
    data_[x].exist_ = 0;
    data_[x].adj_.clear();
    for (auto itdata = data_.begin(); itdata != data_.end(); ++itdata) {
        for (auto itlist = itdata->adj_.begin(); itlist != itdata->adj_.end(); ++itlist) {
            if (itlist->first == x) itdata->adj_.erase(itlist);
        }
    }
}

template <typename T, typename S, bool R>
std::map<T, int> graph<T, S, R>::GetExisted() {
    return existed_;
}

template <typename T, typename S, bool R>
std::set<T> graph<T, S, R>::GetDepend() {
    return dependence_;
}

template <typename T, typename S, bool R>
std::set<T> graph<T, S, R>::GetSources() {
    std::set<T> sources;
    for (auto it : existed_) {
        if (this->IsSource(it.first)) {
            sources.insert(it.first);
        }
    }
    return sources;
}

template <typename T, typename S, bool R>
std::set<T> graph<T, S, R>::GetSinks() {
    std::set<T> sinks;
    for (auto it : existed_) {
        if (this->IsSink(it.first)) {
            sinks.insert(it.first);
        }
    }
    return sinks;
}

template <typename T, typename S, bool R>
void graph<T, S, R>::AddVertex(int x, vertex<T, S>& v) {
    if (!ExistVal(v.value_)) {
        if (n_ < x + 1) {
            n_ = 1 + (3 * x)/2;
            data_.resize(n_);
            v.exist_ = 1;
            data_[x] = v;
            existed_.insert(std::pair<T, int>(v.value_, x));
        } else {
            v.exist_ = 1;
            data_[x] = v;
            existed_.insert(std::pair<T, int>(v.value_, x));
        }
    }
}

template <typename T, typename S, bool R>
void graph<T, S, R>::AddVertex(int x, T val) {
    if (!ExistVal(val)) {
        if (n_ < x + 1) {
            n_ = 1 + (3 * x)/2;
            data_.resize(n_);
            vertex<T, S> v(val);
            v.exist_ = 1;
            data_[x] = v;
            existed_.insert(std::pair<T, int>(val, x));
        } else {
            vertex<T, S> v(val);
            v.exist_ = 1;
            data_[x] = v;
            existed_.insert(std::pair<T, int>(val, x));
        }
    }
}

template <typename T, typename S, bool R>
bool graph<T, S, R>::ExistVal(T val) {
    return existed_.find(val) != existed_.end();
}

template <typename T, typename S, bool R>
bool graph<T, S, R>::ExistEdge(int x, int y) {
    auto it = data_[x].adj_.begin();
    for (; it != data_[x].adj_.end(); ++it) {
        if (it->first == y) break;
    }
    return it != data_[x].adj_.end();
}

template <typename T, typename S, bool R>
bool graph<T, S, R>::IsAllBlack() {
    bool res = 1;
    for (int i = 0; i < n_; ++i) {
        if (data_[i].exist_ && data_[i].col_ != BLACK) {
            res = 0;
            break;
        }
    }
    return res;
}

template <typename T, typename S, bool R>
int graph<T, S, R>::GetNotBlackID() {
    int res;
    for (int i = 0; i < n_; ++i) {
        if (data_[i].exist_ && data_[i].col_ != BLACK) {
            res = i;
            break;
        }
    }
    return res;
}

template <typename T, typename S, bool R>
void graph<T, S, R>::AddEdge(int x, int y) {
    if (!ExistEdge(x, y)) {
        if (oriented_ == 1) {
            data_[x].adj_.push_back(std::pair<int, int>(y, 0));
        } else {
            data_[x].adj_.push_back(std::pair<int, int>(y, 0));
            data_[y].adj_.push_back(std::pair<int, int>(x, 0));
        }
    }
}

template <typename T, typename S, bool R>
void graph<T, S, R>::AddEdgeVal(T val1, T val2, S weight) {
    int x = existed_.find(val1)->second;
    int y = existed_.find(val2)->second;
    
    if (!ExistEdge(x, y)) {
        if (oriented_ == 1) {
            data_[x].adj_.push_back(std::pair<int, int>(y, weight));
        } else {
            data_[x].adj_.push_back(std::pair<int, int>(y, weight));
            data_[y].adj_.push_back(std::pair<int, int>(x, weight));
        }
    }
}

template <typename T, typename S, bool R>
void graph<T, S, R>::AddEdgeVal(T val1, T val2) {
    int x = existed_.find(val1)->second;
    int y = existed_.find(val2)->second;
    
    if (!ExistEdge(x, y)) {
        if (oriented_ == 1) {
            data_[x].adj_.push_back(std::pair<int, int>(y, 0));
        } else {
            data_[x].adj_.push_back(std::pair<int, int>(y, 0));
            data_[y].adj_.push_back(std::pair<int, int>(x, 0));
        }
    }
}

template <typename T, typename S, bool R>
std::vector<std::pair<T, T> > graph<T, S, R>::GetEdgeFrom(T src) const {
    std::vector<std::pair<T, T> > res;
    int x = existed_.find(src)->second;
    for (auto it = data_[x].adj_.begin(); it != data_[x].adj_.end(); ++it) {
        res.push_back({src, data_[it->first].value_});
    }
    return res;
}

template <typename T, typename S, bool R>
std::vector<T> graph<T, S, R>::GetVertexFrom(T src) const {
    std::vector<T> res;
    int x = existed_.find(src)->second;
    for (auto it = data_[x].adj_.begin(); it != data_[x].adj_.end(); ++it) {
        res.push_back(data_[it->first].value_);
    }
    return res;
}

template <typename T, typename S, bool R>
std::vector<T> graph<T, S, R>::GetVertexTo(T src) const {
    if (oriented_ == 1) {
        std::vector<T> res;
        graph<T, S, R> g(*this);
        g.Flip();
        int x = existed_.find(src)->second;
        for (auto it = g.data_[x].adj_.begin(); it != g.data_[x].adj_.end(); ++it) {
            res.push_back(data_[it->first].value_);
        }
        return res;
    } else {
        std::vector<T> res;
        int x = existed_.find(src)->second;
        for (auto it = data_[x].adj_.begin(); it != data_[x].adj_.end(); ++it) {
            res.push_back(data_[it->first].value_);
        }
        return res;
    }
}

template <typename T, typename S, bool R>
std::vector<std::pair<T, T> > graph<T, S, R>::GetEdgeTo(T src) const {
    if (oriented_ == 1) {
        std::vector<std::pair<T, T> > res;
        graph<T, S, R> g(*this);
        g.Flip();
        int x = existed_.find(src)->second;
        for (auto it = g.data_[x].adj_.begin(); it != g.data_[x].adj_.end(); ++it) {
            res.push_back({data_[it->first].value_, src});
        }
        return res;
    } else {
        std::vector<std::pair<T, T> > res;
        int x = existed_.find(src)->second;
        for (auto it = data_[x].adj_.begin(); it != data_[x].adj_.end(); ++it) {
            res.push_back({data_[it->first].value_, src});
        }
        return res;
    }
}

template <typename T, typename S, bool R>
void graph<T, S, R>::BFS(T val) {
    std::deque<vertex<T, S> > deq;
    for (int i = 0; i < n_; ++i) {
        data_[i].col_ = WHITE;
    }
    int x = existed_.find(val)->second;
    data_[x].col_ = GREY;
    deq.push_back(data_[x]);
    while (!deq.empty()) {
        vertex<T, S> u = deq.front();
        deq.pop_front();
        std::cout << u.value_ << std::endl;
        for (auto it : u.adj_) {
            vertex<T, S> v = data_[it.first];
            if (v.col_ == WHITE) {
                v.col_ = GREY;
                data_[it.first].col_ = GREY;
                deq.push_back(v);
            }
        }
        if (u.value_ != val) {
            u.col_ = BLACK;
        }
    }
}

template <typename T, typename S, bool R>
std::vector<T> graph<T, S, R>::BFStoIt(T val) {
    std::vector<T> res;
    std::deque<vertex<T, S> > deq;
    for (int i = 0; i < n_; ++i) {
        data_[i].col_ = WHITE;
    }
    int x = existed_.find(val)->second;
    data_[x].col_ = GREY;
    deq.push_back(data_[x]);
    while (!deq.empty()) {
        vertex<T, S> u = deq.front();
        res.push_back(u.value_);
        deq.pop_front();
        for (auto it : u.adj_) {
            vertex<T, S> v = data_[it.first];
            if (v.col_ == WHITE) {
                v.col_ = GREY;
                data_[it.first].col_ = GREY;
                deq.push_back(v);
            }
        }
        if (u.value_ != val) u.col_ = BLACK;
    }
    return res;
}

template <typename T, typename S, bool R>
void graph<T, S, R>::DFS(T val) {
    std::stack<vertex<T, S> > stk;
    for (int i = 0; i < n_; ++i) {
        data_[i].col_ = WHITE;
    }
    int x = existed_.find(val)->second;
    data_[x].col_ = BLACK;
    stk.push(data_[x]);
    while (!stk.empty()) {
        vertex<T, S> u = stk.top();
        stk.pop();
        for (auto it : u.adj_) {
            vertex<T, S> v = data_[it.first];
            if (v.col_ == WHITE) {
                v.col_ = BLACK;
                stk.push(v);
                data_[it.first].col_ = BLACK;
            }
        }
    }
}

template <typename T, typename S, bool R>
void graph<T, S, R>::Kosaraju() {
    graph<T, S, R> flipped = this->Flipped();
    std::stack<int> stk;
    std::stack<int> pass_out;
    for (int i = 0; i < n_; ++i) {
        data_[i].col_ = WHITE;
    }
    //Find not black vertex and then start
    while (this->IsAllBlack() == 0) {
        int x = this->GetNotBlackID();
        data_[x].col_ = GREY;
        stk.push(x);
        while (stk.empty() == 0) {
            int u = stk.top();
            // Add vertex to pass_out if it has no adj vertexes or has no white adj vertex
            if (this->IsSink(u) == 1 || this->HasWhiteAdjVertex(u) == 0) {
                data_[u].col_ = BLACK;
                stk.pop();
                pass_out.push(u);
            } else {
                for (auto it : data_[u].adj_) {
                int v = it.first;
                    if (data_[v].col_ == WHITE) {
                        data_[v].col_ = GREY;
                        stk.push(v);
                        data_[v].col_ = GREY;
                        break;
                    }
                }
            }
        }
    }
    for (int i = 0; i < n_; ++i) {
        flipped.data_[i].col_ = WHITE;
    }
    std::vector<std::set<T> > scc;
    while (pass_out.empty() == 0) {
        int x = pass_out.top();
        pass_out.pop();
        if (flipped.data_[x].col_ == BLACK) {
            continue;
        }
        flipped.data_[x].col_ = BLACK;
        stk.push(x);
        std::set<T> tmp;
        while (stk.empty() == 0) {
            int u = stk.top();
            stk.pop();
            tmp.insert(flipped.data_[u].value_);
            for (auto it : flipped.data_[u].adj_) {
                int v = it.first;
                if (flipped.data_[v].col_ == WHITE) {
                    flipped.data_[v].col_ = BLACK;
                    stk.push(v);
                    flipped.data_[v].col_ = BLACK;
                }
            }
        }
        scc.push_back(tmp);
        tmp.clear();
    }
    // Output
    std::cout << scc.size() << std::endl;
    std::sort(scc.begin(), scc.end(), [](std::set<T> a, std::set<T> b) {
        if (a.size() == b.size()) {
            return *(a.begin()) < *(b.begin());
        } else {
            return a.size() < b.size();
        }
    });
    for (int i = 0; i < scc.size(); ++i) {
        for (auto it : scc[i]) {
            std::cout << it << ' ';
        }
        std::cout << std::endl;
    }
}

// This function is used in Tarjan algorithm
// x is an ID of Vertex
template <typename T, typename S, bool R>
void graph<T, S, R>::StrongConnect(int x, int& step, std::stack<int>& stk, std::vector<std::set<T> >& scc) {
    data_[x].low_ = step;
    data_[x].label_ = step;
    ++step;
    stk.push(x);
    data_[x].col_ = GREY;
    for (auto it : data_[x].adj_) {
        // it.first is ID of adj vertex
        if (data_[it.first].label_ == 0) {
            StrongConnect(it.first, step, stk, scc);
            data_[x].low_ = std::min(data_[x].low_, data_[it.first].low_);
        } else if (data_[it.first].col_ == GREY) {
            data_[x].low_ = std::min(data_[x].low_, data_[it.first].label_);
        }
    }
    if (data_[x].low_ == data_[x].label_) {
        std::set<T> tmp;
        while (stk.top() != x && stk.empty() == 0) {
            tmp.insert(data_[stk.top()].value_);
            data_[stk.top()].col_ = BLACK;
            stk.pop();
        }
        if (stk.top() == x) {
            tmp.insert(data_[x].value_);
            data_[x].col_ = BLACK;
            stk.pop();
        }
        scc.push_back(tmp);
    }
}

template <typename T, typename S, bool R>
void graph<T, S, R>::Tarjan() {
    for (int i = 0; i < n_; ++i) {
        data_[i].col_ = WHITE;
    }
    std::stack<int> stk;
    std::vector<std::set<T> > scc;
    int step = 1;
    for (int i = 0; i < n_; ++i) {
        if (data_[i].label_ == 0 && data_[i].exist_) {
            StrongConnect(i, step, stk, scc);
        }
    }
    std::cout << scc.size() << std::endl;
    std::sort(scc.begin(), scc.end(), [](std::set<T> a, std::set<T> b) {
        if (a.size() == b.size()) {
            return *(a.begin()) < *(b.begin());
        } else {
            return a.size() < b.size();
        }
    });
    for (int i = 0; i < scc.size(); ++i) {
        int j = 0;
        for (auto it : scc[i]) {
            std::cout << it;
            if (j != scc[i].size()-1) {
                std::cout << ' ';
            }
            ++j;
        }
        if (i != scc.size()-1) {
            std::cout << std::endl;
        }
    }
}


//FIXME: Doesn't work correctly
template <typename T, typename S, bool R>
void graph<T, S, R>::BellmanFord(int x) {
    std::vector<int> d(n_);
    for (int i = 0; i < n_; ++i) {
        d[i] = INF;
    }
    d[x] = 0;
    for (int i = 0; i < n_-1; ++i) {
        for (int j = 0; j < n_; ++j) {
            if (data_[j].exist_) {
                for (auto it : data_[j].adj_) {
                    if (d[it.first] > d[j] + it.second) {
                        d[it.first] = d[j] + it.second;
                    }
                }
            }
        }
    }
    // Output
    std::vector<std::string> answer;
    int real_size = 0;
    for (int i = 0; i < d.size(); ++i) {
        if (data_[i].exist_) {
            if (d[i] == INF) {
                answer.push_back(std::to_string(-1));
                ++real_size;
            } else {
                answer.push_back(std::to_string(d[i]));
                ++real_size;
            }
            if (i != d.size()-1) {
                answer.push_back("\n");
            }
        }
    }
    answer.pop_back();
    std::cout << real_size << std::endl;
    for (auto it : answer) {
        if (it == "\n") {
            std::cout << std::endl;
        } else {
            std::cout << it;
        }
    }
}

template <typename T, typename S, bool R>
void graph<T, S, R>::FloydWarshall() {
    std::vector<S> temp(n_, INF);
    std::vector<std::vector<S> > dist(n_, temp);
    for (int i = 0; i < n_; ++i) {
        if (data_[i].exist_){
            dist[i][i] = 0;
        }
    }
    for (int i = 0; i < n_; ++i) {
        if (data_[i].exist_) {
            for (auto it : data_[i].adj_) {
                dist[i][it.first] = it.second;
            }
        }
    }
    for (int i = 0; i < n_; ++i) {
        for (int j = 0; j < n_; ++j) {
            for (int k = 0; k < n_; ++k) {
                if (dist[j][k] > dist[j][i] + dist[i][k]) {
                    dist[j][k] = dist[j][i] + dist[i][k];
                }
            }
        }
    }
    // Output
    std::vector<std::string> answer;
    for (int i = 0; i < n_; ++i) {
        if (data_[i].exist_) {
            for (int j = 0; j < n_; ++j) {
                if (data_[j].exist_) {
                    if (dist[i][j] == INF) {
                        answer.push_back(std::to_string(-1));
                    } else {
                        answer.push_back(std::to_string(dist[i][j]));
                    }
                    answer.push_back(" ");
                }
            }
            if (answer[answer.size()-1] == " ") {
                answer.pop_back();
            }
            answer.push_back("\n");
        }
    }
    answer.pop_back();
    for (auto it : answer) {
        if (it == "\n") {
            std::cout << std::endl;
        } else {
            std::cout << it;
        }
    }
}

template <typename T, typename S, bool R>
void graph<T, S, R>::Dijkstra(int x) {
    //TODO: Update dist in heap. Add map[index] = shared_ptr
    std::vector<int> dist(n_, INF);
    dist[x] = 0;
    auto my_comp = [](std::pair<int, int> a, std::pair<int, int> b) {
        return a.second < b.second;
    };
    std::set<std::pair<int, int>, decltype(my_comp)> order(my_comp);
    order.insert({x, dist[x]});
    while (order.empty() == 0) {
        int myid = (order.begin())->first;
        order.erase(order.begin());
        for (auto it : data_[myid].adj_) {
            if (dist[it.first] > dist[myid] + it.second) {
                dist[it.first] = dist[myid] + it.second;
                order.insert({it.first, dist[it.first]});
            }
        }
    }
    // Output
    std::vector<int> real_dist;
    for (int i = 0; i < n_; ++i) {
        if (data_[i].exist_) {
            real_dist.push_back(dist[i]);
        }
    }
    std::cout << real_dist.size() << std::endl;
    for (int i = 0; i < real_dist.size(); ++i) {
        if (real_dist[i] == INF) {
            std::cout << -1;
            if (i != real_dist.size()-1) {
                std::cout << std::endl;
            }
        } else {
            std::cout << real_dist[i];
            if (i != real_dist.size()-1) {
                std::cout << std::endl;
            }
        }
    }
}

template <typename T, typename S, bool R>
void graph<T, S, R>::Prim() {
    /* Structure for storing pairs of Vertexes and Weight of edges */
    typedef std::tuple<std::pair<int, int>, S> mystruct;
    /* Find first existent vertex which has adjacent vertex */
    int first_id;
    for (int i = 0; i < n_; ++i) {
        if (data_[i].exist_ && data_[i].adj_.size() != 0) {
            first_id = i;
            break;
        }
    }
    /* Preparing */
    auto my_comp = [](mystruct a, mystruct b) {
        return std::get<1>(a) > std::get<1>(b);
    };
    std::priority_queue<mystruct, std::vector<mystruct>, decltype(my_comp)> order(my_comp);
    std::vector<mystruct> answer;
    std::vector<bool> marked(n_, 0);
    for (auto it : data_[first_id].adj_) {
        order.push(mystruct ({first_id, it.first}, it.second));
    }
    marked[first_id] = 1;
    /* Main cycle */
    while (order.size() != 0) {
        mystruct tmp = order.top();
        int myid = std::get<0>(order.top()).second;
        order.pop();
        if (marked[myid] == 0) {
            for (auto it : data_[myid].adj_) {
                if (marked[it.first] == 0) {
                    order.push(mystruct ({myid, it.first}, it.second));
                }
            }
            marked[myid] = 1;
            answer.push_back(tmp);
        }
    }
    /* Output */
    S res = 0;
    for (auto it : answer) {
        //        std::cout << std::get<0>(it).first << ' ' << std::get<0>(it).second << ' ' << std::get<1>(it) << std::endl;
        res += std::get<1>(it);
    }
    std::cout << res;
}

template <typename T>
class DisjointSet {
public:
    DisjointSet(int n): p(std::vector<int> (n)), rank(std::vector<int> (n)) {
        
    }
    void MakeSet(int x) {
        p[x] = x;
        rank[x] = 0;
    }
    int Find(int x) {
        return (x == p[x] ? x : p[x] = Find(p[x]));
    }
    void Union(int x, int y) {
        x = Find(x);
        y = Find(y);
        
        if (x == y) {
            return;
        }
        
        if (rank[x] < rank[y]) {
            p[x] = y;
        }
        else {
            p[y] = x;
        }
        
        if (rank[x] == rank[y]) {
            ++rank[x];
        }
    }
private:
    std::vector<int> p;
    std::vector<int> rank;
};

template <typename T, typename S, bool R>
void graph<T, S, R>::Kruscal() {
    typedef std::tuple<std::pair<int, int>, S> mystruct;
    /* Make Disjoint Set */
    DisjointSet<mystruct> dis_set(n_);
    for (int i = 0; i < n_; ++i) {
        if (data_[i].exist_) {
            dis_set.MakeSet(i);
        }
    }
    auto my_comp = [](mystruct a, mystruct b) {
        return std::get<1>(a) > std::get<1>(b);
    };
    std::priority_queue<mystruct, std::vector<mystruct>, decltype(my_comp)> order(my_comp);
    std::vector<mystruct> answer;
    /* Filling order with vertexes and edges */
    for (int i = 0; i < n_; ++i) {
        if (data_[i].exist_) {
            for (auto it : data_[i].adj_) {
                if (i < it.first) {
                order.push(mystruct ({i, it.first}, it.second));
                }
            }
        }
    }
    int numb = this->NumbOfVert();
    /* Main cycle */
    while (answer.size() != numb-1) {
        mystruct tmp = order.top();
        int vert1 = std::get<0>(tmp).first;
        int vert2 = std::get<0>(tmp).second;
        order.pop();
        if (dis_set.Find(vert1) != dis_set.Find(vert2)) {
            dis_set.Union(vert1, vert2);
            answer.push_back(tmp);
        }
    }
    /* Output */
    S res = 0;
    for (auto it : answer) {
//        std::cout << std::get<0>(it).first << ' ' << std::get<0>(it).second << ' ' << std::get<1>(it) << std::endl;
        res += std::get<1>(it);
    }
    std::cout << res;
}

template <typename T, typename S, bool R>
void graph<T, S, R>::DFSToStrong(T val, std::set<std::pair<T, T> >& res) {
    std::stack<vertex<T, S> > stk;
    for (int i = 0; i < n_; ++i) {
        data_[i].col_ = WHITE;
    }
    int x = existed_.find(val)->second;
    data_[x].col_ = BLACK;
    stk.push(data_[x]);
    while (!stk.empty()) {
        vertex<T, S> u = stk.top();
        stk.pop();
        if (u.IsSink()) {
            res.insert({u.value_, val});
        }
        for (auto it : u.adj_) {
            vertex<T, S> v = data_[it.first];
            if (v.col_ == WHITE) {
                v.col_ = BLACK;
                stk.push(v);
                data_[it.first].col_ = BLACK;
            }
        }
    }
}

template <typename T, typename S, bool R>
std::set<std::pair<T, T> > graph<T, S, R>::ToStrong() {
    std::set<std::pair<T, T> > res;
    auto src = this->GetSources();
    for (auto it : src) {
        this->DFSToStrong(it, res);
    }
    return res;
}

template <typename T, typename S, bool R>
std::vector<T> graph<T, S, R>::DFStoIt(T val) {
    std::vector<T> res;
    std::stack<vertex<T, S> > stk;
    for (int i = 0; i < n_; ++i) {
        data_[i].col_ = WHITE;
    }
    int x = existed_.find(val)->second;
    data_[x].col_ = BLACK;
    stk.push(data_[x]);
    while (!stk.empty()) {
        vertex<T, S> u = stk.top();
        res.push_back(u.value_);
        stk.pop();
        for (auto it : u.adj_) {
            vertex<T, S> v = data_[it.first];
            if (v.col_ == WHITE) {
                v.col_ = BLACK;
                stk.push(v);
                data_[it.first].col_ = GREY;
            }
        }
    }
    return res;
}

template <typename T, typename S, bool R>
std::istream& operator>>(std::istream& stream, graph<T, S, R>& g) {
    if (g.oriented_ == 1) {
        int count;
        stream >> count;
        for (int i = 0; i < count; ++i) {
            T from;
            stream >> from;
            T to;
            stream >> to;
            g.AddVertex(from, from);
            g.AddVertex(to, to);
            S weight;
            stream >> weight;
            g.AddEdgeVal(from, to, weight);
        }
        return stream;
    } else {
        int count;
        stream >> count;
        for (int i = 0; i < count; ++i) {
            T from;
            stream >> from;
            T to;
            stream >> to;
            g.AddVertex(from, from);
            g.AddVertex(to, to);
            S weight;
            stream >> weight;
            g.AddEdgeVal(from, to, weight);
            g.AddEdgeVal(to, from, weight);
        }
        return stream;
    }
}

template <typename T, typename S, bool R>
std::ostream& operator<<(std::ostream& stream, graph<T, S, R>& g) {
    for (int i = 0; i < g.n_; ++i) {
        // it is iterator over adjacency list
        // it->first is ID of adj. vertex
        // it->second is weight of the edge
        for (auto it : g.data_[i].adj_) {
            stream << g.data_[i].value_ << " -> " << g.data_[it.first].value_ << " w: " << it.second << std::endl;
        }
    }
    return stream;
}

#endif /* defined(__Graph__Graph__) */
