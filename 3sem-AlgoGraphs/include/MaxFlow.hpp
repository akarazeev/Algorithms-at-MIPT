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

class MaxFlow {
public:
    typedef std::vector<std::vector<std::pair<double, double> > >
    TableOfPairs;
    
    constexpr const static double kInf = 100000000;
    
    MaxFlow(int n);
    
    void AddEdge(int from, int to, double cap, double cost);
    
    void GetPath(TableOfPairs& flow,
                 std::vector<int>& dist,
                 std::vector<int>& path,
                 double& df, int s, int t);
    
    std::pair<double, double> Flow(int s, int t, double max_flow);
    
    int Size();
    
    friend MaxFlow& operator>>(std::istream& stream, MaxFlow& m);
private:
    /* first - capacity, second - cost */
    TableOfPairs data_;
};

#endif /* MaxFlow_hpp */
