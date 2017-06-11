//
//  main.cpp
//  Personal_Chart
//
//  Created by Anton Wetret on 06/05/15.
//  Copyright (c) 2015 Anton Karazeev. All rights reserved.
//

#include <iostream>
#include <vector>
#include "PersonalChart.h"

int main() {
    PersonalChart pc;
    pc.VoteRecord("lala", 34);
    pc.VoteRecord("lala", 34);
    pc.VoteRecord("lala", 34);
    
    pc.VoteRecord("lala", 36);
    
    pc.VoteRecord("lala", 35);
    
    pc.VoteRecord("lala", 2);
    
    pc.VoteRecord("lala", 37);
    pc.VoteRecord("lala", 37);
    
    pc.VoteRecord("lala", 39);
    
    auto vec = pc.GetTop("lala", 4);
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << endl;
    }
    
    cout << pc.GetDistinctTrackSize("lala");
    
    return 0;
}
