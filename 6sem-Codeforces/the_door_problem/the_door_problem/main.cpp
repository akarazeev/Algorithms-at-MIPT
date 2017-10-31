//
//  main.cpp
//  L task - the_door_problem
//
//  Created by Anton Karazeev on 07/08/2017.
//  Copyright © 2017 Anton Karazeev. All rights reserved.
//

/*
 
in:
3 3
1 0 1
2 1 3
2 1 2
2 2 3
 
out:
NO
 

in:
3 3
1 0 1
3 1 2 3
1 2
2 1 3
 
out:
YES
 
 
in:
3 3
1 0 1
3 1 2 3
2 1 2
1 3

out:
NO
 
*/

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
    
    /* Internal state */
    int state = 0;
    int visit = 0;
    
    /* List of corresponding doors/switches */
    std::vector<Node*> list;
};

bool dfs(Node* switch_node, int state, int visit) {
    // whether c->state == state
    if (switch_node->visit == visit) {
        return switch_node->state == state;
    }

    /* Change visit and internal state */
    switch_node->visit = visit;
    switch_node->state = state;

    // iterate over doors controlled by switch_node
    for (int i = 0; i < switch_node->list.size(); ++i) {
        // iterate over switches corresponding to door switch_node->list[i]
        for (int j = 0; j < switch_node->list[i]->list.size(); ++j) {
            // switch switch_node->list[i]->list[j] controls door switch_node->list[i]
            // 2-SAT
            if (not(switch_node->list[i]->list[j] == switch_node) and
                !dfs(switch_node->list[i]->list[j],
                     switch_node->state ^ switch_node->list[i]->state ^ 1, // xor operation
                     visit)) {
                return false;
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

    std::vector<Node> doors(n);
    std::vector<Node> switches(m);
    
    /* Read initial states of doors */
    for (int i = 0; i < n; ++i) {
        int init_state;
        std::cin >> init_state;
        doors[i] = Node(init_state);
    }
    for (int i = 0; i < m; ++i) {
        switches[i] = Node(-1);
    }

    /* Read doors and switches */
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
    for (int i = 0; i < m; ++i) {
        if (switches[i].visit == 0) {
            visit -= 1;
            if (!dfs(&switches[i], 0, visit)) {
                std::cout << "NO" << std::endl;
                return 0;
            }
        }
    }
    
    std::cout << "YES" << std::endl;

    return 0;
}
