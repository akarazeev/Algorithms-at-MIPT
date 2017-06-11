//
//  Graph.h
//  Graph
//
//  Created by Anton Wetret on 13/05/15.
//  Copyright (c) 2015 Anton Karazeev. All rights reserved.
//

#ifndef __Graph__Graph__
#define __Graph__Graph__

#include <vector>
#include <list>
#include <deque>
#include <iostream>
#include <map>
#include <string>
#include <set>

enum {WHITE, GREY, BLACK};

using namespace std;

template <typename T, typename S>
class vertex {
public:
    vertex();
    vertex(T val);
    void operator=(vertex& other);
    bool exist_ = 0;
    T value_;
    list<pair<int, S> > adj_;
    int col_ = WHITE;
};

template <typename T, typename S, bool R = 0>
class graph {
public:
    graph();
    graph(int n);
    graph(const graph<T, S, R>& g);
    
    void Flip();
    void DeleteVertex(int x);
    void DeleteEdge(int x, int y);
    void AddVertex(int x, vertex<T, S>& v);
    void AddVertex(int x, T val);
    void AddEdge(int x, int y);
    void AddEdgeVal(T val1, T val2);
    bool ExistVal(T val);
    bool ExistEdge(int x, int y);
    
    void BFS(T val);
    
    vector<int> GetVertexFrom(int x) const;
    vector<int> GetVertexTo(int x) const;
    vector<pair<int, int> > GetEdgeFrom(int x) const;
    vector<pair<int, int> > GetEdgeTo(int x) const;
    map<T, int> GetExisted();
    set<T> GetDepend();
    
    template <typename TT, typename SS, bool RR>
    friend ostream& operator<<(ostream& stream, graph<TT, SS, RR>& g);
    template <typename TT, typename SS, bool RR>
    friend istream& operator>>(istream& stream, graph<TT, SS, RR>& g);
private:
    vector<vertex<T, S> > data_;
    map<T, int> existed_;
    set<T> dependence_;
    int n_;
    bool oriented_;
};

template <typename T, typename S, bool R>
istream& operator>>(istream& stream, graph<T, S, R>& g);

template <typename T, typename S, bool R>
ostream& operator<<(ostream& stream, graph<T, S, R>& g);

#endif /* defined(__Graph__Graph__) */
