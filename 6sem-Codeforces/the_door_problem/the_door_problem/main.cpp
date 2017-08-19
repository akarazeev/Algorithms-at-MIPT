//
//  main.cpp
//  the_door_problem
//
//  Created by Anton Karazeev on 07/08/2017.
//  Copyright © 2017 Anton Karazeev. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <vector>

class Node {
public:
    Node() {
        
    }
    
    Node(int in_state) : state(in_state) {
        
    }
    
    /* Comparison of two Nodes */
    const bool operator==(const Node& other) const {
        if (other.state == this->state and
            other.visit == this->visit and
            other.list.size() == this->list.size()) {
            for (int i = 0; i < this->list.size(); ++i) {
                if (other.list[i] != this->list[i]) {
                    return false;
                }
            }
            return true;
        } else {
            return false;
        }
    }
    
    int state;
    int visit;
    
    std::vector<Node*> list;
};

bool dfs(Node* c, int as, int visit) {
    if (c->visit == visit) {
        return c->state == as;
    }
    c->visit = visit;
    c->state = as;

    for (auto d : c->list) {
        for (auto s : d->list) {
            if (not(s == c)) {
                if (!dfs(s, c->state ^ d->state ^ 1, visit)) {
                    return false;
                }
            }
        }
    }
    return true;
}

int main() {
    int n; // number of doors
    int m; // number of switches
    
    std::cin >> n;
    std::cin >> m;
    
    std::vector<Node> table(n + m);
    std::vector<Node> doors(n);
    std::vector<Node> switches(m);
    
    /* Read initial states of doors */
//    for (int i = 0; i < n + m; ++i) {
//        if (i < n) {
//            int init_state;
//            std::cin >> init_state;
//            table[i] = Node(init_state);
//        } else {
//            table[i] = Node(-1);
//        }
//    }
    for (int i = 0; i < n; ++i) {
        int init_state;
        std::cin >> init_state;
        doors[i] = Node(init_state);
    }
    for (int i = 0; i < m; ++i) {
        switches[i] = Node(-1);
    }
    
    /* Read doors and switches */
//    for (int i = 0; i < m; ++i) {
//        int num_doors; // number of doors controlled by switch i
//        std::cin >> num_doors;
//        
//        for (int j = 0; j < num_doors; ++j) {
//            int id_door; // door id
//            std::cin >> id_door;
//            id_door -= 1;
//            table[n + i].list.push_back(&table[id_door]); // add to switch i controlled door id_door
//            table[id_door].list.push_back(&table[n + i]); // add to id_door switch i
//        }
//    }
    for (int i = 0; i < m; ++i) {
        int num_doors; // number of doors controlled by switch i
        std::cin >> num_doors;
        
        /* Read num_doors */
        for (int j = 0; j < num_doors; ++j) {
            int id_door; // door id
            std::cin >> id_door;
            id_door -= 1;

            switches[i].list.push_back(&doors[id_door]); // add to switch i controlled door id_door
            doors[id_door].list.push_back(&switches[i]); // add to id_door switch i
        }
    }
    
    int visit = -1;
    
    /* Iterate over switches */
//    for (int i = 0; i < m; ++i) {
//        if (table[i + n].visit == 0) {
//            visit -= 1;
//            if (!dfs(&table[i + n], 0, visit)) {
//                std::cout << "NO";
//                return 0;
//            }
//        }
//    }
    for (int i = 0; i < m; ++i) {
        if (switches[i].visit == 0) {
            visit -= 1;
            if (!dfs(&switches[i], 0, visit)) {
                std::cout << "NO";
                return 0;
            }
        }
    }
    
    std::cout << "YES";

    return 0;
}
