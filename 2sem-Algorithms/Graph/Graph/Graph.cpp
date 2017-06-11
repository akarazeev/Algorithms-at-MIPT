//
//  Graph.cpp
//  Graph
//
//  Created by Anton Wetret on 13/05/15.
//  Copyright (c) 2015 Anton Karazeev. All rights reserved.
//

#include "Graph.h"

template <typename T, typename S>
vertex<T, S>::vertex() {
    
}

template <typename T, typename S>
vertex<T, S>::vertex(T val): value_(val) {
    
}

template <typename T, typename S>
void vertex<T, S>::operator=(vertex<T, S>& other) {
    exist_ = other.exist_;
    value_ = other.value_;
    adj_ = other.adj_;
    col_ = other.col_;
}

template <typename T, typename S, bool R>
graph<T, S, R>::graph(): oriented_(R) {
    
}

template <typename T, typename S, bool R>
graph<T, S, R>::graph(int n): n_(n), oriented_(R), data_(vector<vertex<T, S> >(n)) {
    
}

template <typename T, typename S, bool R>
graph<T, S, R>::graph(const graph<T, S, R>& g): data_(g.data_), n_(g.n_), oriented_(g.oriented_) {
    
}

template <typename T, typename S, bool R>
void graph<T, S, R>::Flip() {
    if (oriented_ == 1) {
        vector<vertex<T, S> > data(n_);
        for (int i = 0; i < n_; ++i) {
            data[i].value_ = data_[i].value_;
        }
        for (int i = 0; i < n_; ++i) {
            for (auto it = data_[i].adj_.begin(); it != data_[i].adj_.end(); ++it) {
                data[it->first].adj_.push_back(pair<int, S>(i, it->second));
            }
        }
        data_ = data;
    }
}

template <typename T, typename S, bool R>
void graph<T, S, R>::DeleteEdge(int x, int y) {
    if (oriented_ == 1) {
        auto it = data_[x].adj_.begin();
        while (it->first != y && it != data_[x].adj_.end()) ++it;
        if (it != data_[x].adj_.end()) data_[x].adj_.erase(it);
    }
    else {
        auto it = data_[x].adj_.begin();
        while (it->first != y && it != data_[x].adj_.end()) ++it;
        if (it != data_[x].adj_.end()) data_[x].adj_.erase(it);
        
        it = data_[y].adj_.begin();
        while (it->first != x && it != data_[y].adj_.end()) ++it;
        if (it != data_[y].adj_.end()) data_[y].adj_.erase(it);
    }
}

template <typename T, typename S, bool R>
void graph<T, S, R>::DeleteVertex(int x) {
    data_[x].first = NULL;
    data_[x].adj_.clear();
    for (auto itdata = data_.begin(); itdata != data_.end(); ++itdata) {
        for (auto itlist = itdata->adj_.begin(); itlist != itdata->adj_.end(); ++itlist) {
            if (itlist->first == x) itdata->adj_.erase(itlist);
        }
    }
}

template <typename T, typename S, bool R>
map<T, int> graph<T, S, R>::GetExisted() {
    return existed_;
}

template <typename T, typename S, bool R>
set<T> graph<T, S, R>::GetDepend() {
    return dependence_;
}

template <typename T, typename S, bool R>
void graph<T, S, R>::AddVertex(int x, vertex<T, S>& v) {
    if (!ExistVal(v.value_)) {
        if (n_ < x + 1) {
            data_.resize(1 + (3 * x)/2);
            n_ = 1 + (3 * x)/2;
            v.exist_ = 1;
            data_[x] = v;
            existed_.push(pair<T, int>(v.value_, x));
        }
        else {
            v.exist_ = 1;
            data_[x] = v;
            existed_.push(pair<T, int>(v.value_, x));
        }
    }
    //    else cout << "EXISTED" << endl;
}

template <typename T, typename S, bool R>
void graph<T, S, R>::AddVertex(int x, T val) {
    if (!ExistVal(val)) {
        if (n_ < x + 1) {
            data_.resize(1 + (3 * x)/2);
            n_ = 1 + (3 * x)/2;
            vertex<T, S> v(val);
            v.exist_ = 1;
            data_[x] = v;
            existed_.insert(pair<T, int>(val, x));
        }
        else {
            vertex<T, S> v(val);
            v.exist_ = 1;
            data_[x] = v;
            existed_.insert(pair<T, int>(val, x));
        }
    }
    //    else cout << "EXISTED " << val << endl;
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
void graph<T, S, R>::AddEdge(int x, int y) {
    if (!ExistEdge(x, y)) {
        if (oriented_ == 1) {
            data_[x].adj_.push_back(pair<int, int>(y, 0));
        }
        else {
            data_[x].adj_.push_back(pair<int, int>(y, 0));
            data_[y].adj_.push_back(pair<int, int>(x, 0));
        }
    }
}

template <typename T, typename S, bool R>
void graph<T, S, R>::AddEdgeVal(T val1, T val2) {
    int x = existed_.find(val1)->second;
    int y = existed_.find(val2)->second;
    
    if (!ExistEdge(x, y)) {
        if (oriented_ == 1) {
            data_[x].adj_.push_back(pair<int, int>(y, 0));
        }
        else {
            data_[x].adj_.push_back(pair<int, int>(y, 0));
            data_[y].adj_.push_back(pair<int, int>(x, 0));
        }
    }
}

template <typename T, typename S, bool R>
vector<pair<int, int> > graph<T, S, R>::GetEdgeFrom(int x) const {
    vector<pair<int, int> > res;
    for (auto it = data_[x].adj_.begin(); it != data_[x].adj_.end(); ++it) {
        res.push_back(pair<int, int>(x, it->first));
    }
    return res;
}

template <typename T, typename S, bool R>
vector<int> graph<T, S, R>::GetVertexFrom(int x) const {
    vector<int> res;
    for (auto it = data_[x].adj_.begin(); it != data_[x].adj_.end(); ++it) {
        res.push_back(it->first);
    }
    return res;
}

template <typename T, typename S, bool R>
vector<int> graph<T, S, R>::GetVertexTo(int x) const {
    if (oriented_ == 1) {
        vector<int> res;
        graph<T, S, R> g(*this);
        g.Flip();
        for (auto it = g.data_[x].adj_.begin(); it != g.data_[x].adj_.end(); ++it) {
            res.push_back(it->first);
        }
        return res;
    }
    else {
        vector<int> res;
        for (auto it = data_[x].adj_.begin(); it != data_[x].adj_.end(); ++it) {
            res.push_back(it->first);
        }
        return res;
    }
}

template <typename T, typename S, bool R>
vector<pair<int, int> > graph<T, S, R>::GetEdgeTo(int x) const {
    if (oriented_ == 1) {
        vector<pair<int, int> > res;
        graph<T, S, R> g(*this);
        g.Flip();
        for (auto it = g.data_[x].adj_.begin(); it != g.data_[x].adj_.end(); ++it) {
            res.push_back(pair<int, int>(it->first, x));
        }
        return res;
    }
    else {
        vector<pair<int, int> > res;
        for (auto it = data_[x].adj_.begin(); it != data_[x].adj_.end(); ++it) {
            res.push_back(pair<int, int>(it->first, x));
        }
        return res;
    }
}

template <typename T, typename S, bool R>
void graph<T, S, R>::BFS(T val) {
    deque<vertex<T, S> > q;
    for (int i = 0; i < n_; ++i) {
        data_[i].col_ = WHITE;
    }
    int x = existed_.find(val)->second;
    //    data_[x].col_ = GREY; // Отключаю для поиска циклических зависимостей
    q.push_back(data_[x]);
    while (!q.empty()) {
        vertex<T, S> u = q.front();
        q.pop_front();
        for (auto it : u.adj_) {
            vertex<T, S> v = data_[it.first];
            if (v.value_ == val) {
                dependence_.insert(val);
                cout << "Found " << val << endl;
                break;
            }
            if (v.col_ == WHITE) {
                cout << v.value_ << ' ' << v.col_ << endl;
                v.col_ = GREY;
                data_[it.first].col_ = GREY;
                q.push_back(v);
            }
        }
        if (u.value_ != val) u.col_ = BLACK;
    }
}

template <typename T, typename S, bool R>
istream& operator>>(istream& stream, graph<T, S, R>& g) {
    if (g.oriented_ == 1) {
        int count;
        stream >> count;
        for (int i = 0; i < count; ++i) {
            int vert1;
            stream >> vert1;
            int vert2;
            stream >> vert2;
            g.data_[vert1].value_ = vert1;
            g.data_[vert2].value_ = vert2;
            g.data_[vert1].adj_.push_back(pair<int, int>(vert2, 0));
            g.data_[vert1].exist_ = 1;
            g.data_[vert2].exist_ = 1;
        }
        return stream;
    }
    else {
        int count;
        stream >> count;
        for (int i = 0; i < count; ++i) {
            int vert1;
            stream >> vert1;
            int vert2;
            stream >> vert2;
            g.data_[vert1].value_ = vert1;
            g.data_[vert1].adj_.push_back(pair<int, int>(vert2, 0));
            g.data_[vert1].exist_ = 1;
            g.data_[vert2].value_ = vert2;
            g.data_[vert2].adj_.push_back(pair<int, int>(vert1, 0));
            g.data_[vert2].exist_ = 1;
        }
        return stream;
    }
}

template <typename T, typename S, bool R>
ostream& operator<<(ostream& stream, graph<T, S, R>& g) {
    for (int i = 0; i < g.n_; ++i) {
        for (auto it = g.data_[i].adj_.begin(); it != g.data_[i].adj_.end(); ++it) {
            stream << g.data_[i].value_ << " -> " << g.data_[it->first].value_ << endl;
        }
    }
    return stream;
}