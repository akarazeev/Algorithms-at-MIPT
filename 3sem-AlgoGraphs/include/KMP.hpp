//
//  KMP.hpp
//  KMP
//
//  Created by Anton Wetret on 6/11/15.
//  Copyright © 2015 Anton Karazeev. All rights reserved.
//

#ifndef KMP_hpp
#define KMP_hpp

#include <string>
#include <vector>

std::vector<int> Pi(std::string& str) {
    std::vector<int> pi(str.length());
    for (int i = 1; i < str.length(); ++i) {
        int q = pi[i-1];
        while (q > 0 && str[i] != str[q]) {
            q = pi[q-1];
        }
        if (str[i] == str[q]) {
            ++q;
        }
        pi[i] = q;
    }
    return pi;
}

std::vector<int> KMP(std::string& text, std::string& pattrn){
    std::vector<int> pref_func (Pi(text));
    std::vector<int> res;
    
    for (int k = 0, i = 0; i < text.length(); ++i){
        while ((k>0) && (pattrn[k] != text[i])) {
            k = pref_func[k-1];
        }
        if (pattrn[k] == text[i]) {
            ++k;
        }
        if (k==pattrn.length()) {
            res.push_back(i - static_cast<int>(pattrn.length()) + 1);
        }
    }
    return res;
}

#endif /* KMP_h */
