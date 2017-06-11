//
//  main.cpp
//  Cycle
//
//  Created by Anton Wetret on 16/05/15.
//  Copyright (c) 2015 Anton Karazeev. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include "Graph.cpp"

int main() {
    ifstream fin("/Users/AntonWetret/Documents/XCode/Seminars/2 семестр/Tasks_2/Cycle/Cycle/test.txt");
    int n;
    fin >> n;
    graph<string, int, 1> g(n);
    
    string val1;
    string val2;
    int count = 0;
    int pn = 0;
    for (int i = 0; i < n; ++i) {
        fin >> val1;
        fin >> pn;
        for (int j = 0; j < pn; ++j) {
            fin >> val2;
            g.AddVertex(count, val1);
            ++count;
            g.AddVertex(count, val2);
            ++count;
            g.AddEdgeVal(val1, val2);
        }
    }
    
    map<string, int> existed = g.GetExisted();
    for (auto it : existed) {
        g.BFS(it.first);
        cout << endl;
    }
    
    cout << g << endl;
    cout << "The answer:" << endl;
    
    set<string> depend = g.GetDepend();
    for (auto it : depend) cout << it << endl;
    
    return 0;
}
