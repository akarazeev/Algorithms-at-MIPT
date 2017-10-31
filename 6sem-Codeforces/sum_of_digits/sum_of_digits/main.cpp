//
//  main.cpp
//  M task - sum_of_digits
//
//  Created by Anton Karazeev on 19/08/2017.
//  Copyright © 2017 Anton Karazeev. All rights reserved.
//

/*
in:
4
9 81
12 9
6 10
7 9

out:
9
No solution
1122
111112
*/

#include <iostream>
#include <vector>

int main(){
    int max_len = 100; // max number of digits
    int max_sum = 9 * max_len; // max sum of digits
    int max_sq_sum = 81 * max_len; // max sum of squares

    /* Dynamic programming */
    std::vector<std::vector<int> > table(max_sum + 1, std::vector<int> (max_sq_sum + 1, -1)); // initialize matrix with -1
    table[0][0] = 0;
    
    // iterate over the table and fill with the number of digits of minimal number
    for (int i = 1; i <= max_sum; ++i){
        for (int j = 0; j <= max_sq_sum; ++j){
            // for each digit from 1 to 9
            for (int digit = 1; digit <= 9; ++digit){
                if (i >= digit and j >= (digit * digit) and table[i - digit][j - (digit * digit)] != -1) {
                    int tmp = 1 + table[i - digit][j - (digit * digit)]; // increase prev value by 1
                    
                    if (tmp <= max_len and (table[i][j] == -1 or tmp < table[i][j])) {
                        table[i][j] = tmp; // length of number with sum of digits i and sum of squares j
                    }
                }
            }
        }
    }
    
    int n; // number of tests
    std::cin >> n;
    
    std::vector<std::pair<int, int> > tests; // vector of input values
    
    /* Read input */
    for (int i = 0; i < n; ++i) {
        int s1;
        int s2;

        std::cin >> s1;
        std::cin >> s2;
        
        tests.push_back({s1, s2});
    }
    
    /* Main part */
    for (int i = 0; i < tests.size(); ++i) {
        int s1 = tests[i].first;
        int s2 = tests[i].second;

        if (s1 > max_sum or s2 > max_sq_sum or table[s1][s2] == -1) {
            std::cout << "No solution" << std::endl;
        } else {
            // move to the left upper corner while it is possible
            while (s1 != 0 or s2 != 0){
                // iterate from the lowest digit -- 1
                for (int digit = 1; digit <= 9; ++digit){
                    if (table[s1][s2] == 1 + table[s1 - digit][s2 - (digit * digit)] and
                        s1 >= digit and s2 >= (digit * digit)){
                        // output char by char
                        std::cout << char(digit + '0');
                        
                        s1 -= digit;
                        s2 -= digit * digit;
                        
                        break;
                    }
                }
            }
            std::cout << std::endl;
        }
    }
    
    return 0;
}
