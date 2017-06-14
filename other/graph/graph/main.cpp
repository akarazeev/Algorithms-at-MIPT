//
//  main.cpp
//  graph
//
//  Created by Anton Karazeev on 13/06/2017.
//  Copyright © 2017 Anton Karazeev. All rights reserved.
//

#include <iostream>
#include <utility>
#include <vector>
#include <list>
#include <set>
#include <map>

class Vertex {
public:
    Vertex(int value_arg) : value(value_arg) {
        
    }
    
    int value;
    
    // List of (id, weight)-pairs.
    std::list<std::pair<int, int> > adjacency_;
};

class Graph {
public:
    Graph() {
        
    }
    
    
    
    // Graph is oriented.
    void add_edge(int a, int b, int weight) {
        data_
    }
    
private:
    std::vector<Vertex> data_;
    
};

int main() {
    Graph g;
    
    return 0;
}
