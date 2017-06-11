//
//  main.cpp
//  Undo-Redo
//
//  Created by Anton Wetret on 22/04/15.
//  Copyright (c) 2015 Anton Karazeev. All rights reserved.
//

#include <iostream>
#include <vector>
#include "TextEdit.h"

using namespace std;

int main() {
    string s;
    s = "abcdef/nlol/^/>/>/>/|/^P/n/|/|/</</</</</</</</</</nulik /^/</#/#/@";
//    cin >> s;
    textedit t;
    
    for (int k = 0; k < s.length(); ++k) {
        if (s[k] == '/') {
            if (s[k+1] == 'n') {
                t.nextstring(1);
                ++k;
            }
            else if (s[k+1] == '<') {
                t.left(1);
                ++k;
            }
            else if (s[k+1] == '>') {
                t.right(1);
                ++k;
            }
            else if (s[k+1] == '^') {
                t.up(1, 0);
                ++k;
            }
            else if (s[k+1] == '|') {
                t.down(1, 0);
                ++k;
            }
            else if (s[k+1] == '#') {
                t.del(1);
                ++k;
            }
            else if (s[k+1] == '@') {
                t.undo();
                ++k;
            }
            else if (s[k+1] == '$') {
                t.redo();
                ++k;
            }
            else t.insert(s[k], 1);
        }
        else t.insert(s[k], 1);
    }
    
    cout << s << endl;
    cout << "-+-+-+-+-+-+-+-+-+-" << endl;
    cout << t << endl;
    cout << "-+-+-+-+-+-+-+-+-+-" << endl;
    cout << "Cursor ends at: " << t.I() << ' ' << t.J() << endl;
    
    return 0;
}
