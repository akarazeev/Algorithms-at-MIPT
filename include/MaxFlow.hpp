//
//  MaxFlow.hpp
//  MaxFlow
//
//  Created by Anton Wetret on 18/11/15.
//  Copyright © 2015 Anton Karazeev. All rights reserved.
//

#ifndef MaxFlow_hpp
#define MaxFlow_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include <assert.h>

const int Inf = 100000000;

class MaxFlow {
public:
    MaxFlow(int n);
    
    void AddEdge(int from, int to, int cap, int cost);
    
    void BellmanFord(std::vector<double>& dist, int s);
    void GetPath(std::vector<std::vector<std::pair<double, double> > >& flow, std::vector<int>& dist, std::vector<int>& path, double& df, int s, int t);
    
    std::pair<double, double> Flow(int s, int t, double max_flow);
    
    int Size();
    
    friend MaxFlow& operator>>(std::istream& stream, MaxFlow& m);
private:
    /* first - capacity, second - cost */
    std::vector<std::vector<std::pair<double, double> > > data_;
};

#endif /* MaxFlow_hpp */
