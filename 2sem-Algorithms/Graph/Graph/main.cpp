//
//  main.cpp
//  Graph
//
//  Created by Anton Wetret on 13/05/15.
//  Copyright (c) 2015 Anton Karazeev. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include "Graph.cpp"

using namespace std;

class myclass {
public:
    int val;
};

int main() {
    ifstream fin("/Users/AntonWetret/Documents/XCode/Seminars/2 семестр/Tasks_2/Graph/Graph/test.txt");
    graph<int, int, 1> g(10);
    fin >> g;
//    g.DeleteVertex(2);
//    g.DeleteEdge(5,4);
//    g.AddVertex(1, 10);
    
    cout << g << endl;
    
    vector<int> v = g.GetVertexTo(2);
    
    return 0;
}