//
//  main.cpp
//  K task - fox_and_dinner
//
//  Created by Anton Karazeev on 07/08/2017.
//  Copyright © 2017 Anton Karazeev. All rights reserved.
//

/*
 
in:
4
3 4 8 9

out:
1
4 1 2 4 3


in:
5
2 2 2 2 2

out:
Impossible


in:
12
2 3 4 5 6 7 8 9 10 11 12 13

out:
1
12 1 2 3 6 5 12 9 8 7 10 11 4


in:
24
2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25

out:
3
6 1 2 3 6 5 4
10 7 8 9 12 15 14 13 16 11 10
8 17 18 23 22 19 20 21 24
 
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <queue>

const long long INF = 99999999;

int is_prime(int number) {
    for (int i = 2; i <= sqrt(number + 1); ++i) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

class DinicAlgorithm {
public:
    class Edge {
    public:
        Edge(int to, int cap, int flow, Edge* back) : to(to), cap(cap),
                                                      flow(flow), back(back) {
            
        }
        
        bool remain() const {
            return flow < cap;
        }
        
        void add_flow(int f) {
            flow += f;
            back->flow -= f;
        }
        
        int to;
        int cap;
        int flow;
        Edge* back;
    };
    
    DinicAlgorithm(int n, int src_in, int sink_in) : table(n), memo(n), level(n),
                                                     src(src_in), sink(sink_in) {
        
    }
    
    void add_edge(int from, int to, int cap) {
        Edge* e = new Edge(to, cap, 0, nullptr);
        Edge* r = new Edge(from, 0, 0, e);
        
        e->back = r;
        
        table[from].push_back(e);
        table[to].push_back(r);
    }
    
    int augmenting(int v, int cap) {
        if (v == sink) {
            return cap;
        }
        
        int v_size = static_cast<int>(table[v].size());
        
        for (int i = memo[v]; i < v_size; ++i) {
            const auto& e = table[v][i];
            if (level[e->to] != level[v]+1) {
                continue;
            }
            if (!e->remain()) {
                continue;
            }
            const int f = augmenting(e->to, std::min(cap, e->cap - e->flow));
            if (f > 0) {
                e->add_flow(f);
                memo[v] = i+1;
                return f;
            }
        }
        
        return 0;
    }
    
    int calc() {
        int flow = 0;
        while (true) {
            // depth of each vertex
            for (int i = 0; i < level.size(); ++i) {
                level[i] = -1;
            }
            std::queue<int> myqueue;
            myqueue.push(src);
            level[src] = 0;
            while (!myqueue.empty()) {
                const int v = myqueue.front();
                myqueue.pop();
                for (int i = 0; i < table[v].size(); ++i) {
                    if (table[v][i]->remain() and level[table[v][i]->to] == -1) {
                        level[table[v][i]->to] = level[v] + 1;
                        myqueue.push(table[v][i]->to);
                    }
                }
            }
            
            // residual path of shortest length
            bool is_updated = false;

            for (int i = 0; i < memo.size(); ++i) {
                memo[i] = 0;
            }
            
            while (1) {
                int add = augmenting(src, INF);

                if (add == 0) {
                    break;
                }

                flow += add;
                is_updated = true;
            }
            
            if (is_updated == false) {
                break;
            }
        }
        return flow;
    }
    
    std::vector<std::vector<Edge*> > table;
    std::vector<int> memo;
    std::vector<int> level;
    int src;
    int sink;
};

int main() {
    int n; // number of foxes
    std::cin >> n;
    
    /* Read foxes' years */
    std::vector<int> nodes;
    
    for (int i = 0; i < n; ++i) {
        int tmp;
        std::cin >> tmp;
        nodes.push_back(tmp);
    }
    
    /* Build network of flow */
    // (number of vertexes, source id, sink id)
    DinicAlgorithm dinic(n + 2, n, n + 1);
    
    int flow = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            // if the sum is prime number then
            // add edge between foxes i and j
            if (is_prime(nodes[i] + nodes[j])) {
                // add edge i->j if fox i has even age
                if (nodes[i] % 2 == 0) {
                    dinic.add_edge(i, j, 1);
                } else {
                    dinic.add_edge(j, i, 1);
                }
            }
        }
        // add edge n->i if fox i has even
        // age and increase flow by 2
        if (nodes[i] % 2 == 0) {
            dinic.add_edge(n, i, 2);
            flow += 2;
        } else {
            dinic.add_edge(i, n+1, 2);
        }
    }
    /* First Case */
    // it is impossible to correclty separate foxes
    if (flow != n or dinic.calc() != flow) {
        std::cout << "Impossible" << std::endl;
    } else {
        /* Second Case */

        /* Take network of flow from dinic object */
        const auto& graph = dinic.table;
        std::vector<bool> used(n, false);
        std::vector<std::vector<int> > components;
        
        /* Iterate over unused vertexes (foxes) and find corresponding component */
        for (int i = 0; i < n; ++i) {
            if (used[i]) {
                continue;
            }

            int cur = i;
            used[i] = true;
            components.push_back(std::vector<int>());

            // While possible - find component (neighbours) of the selected fox
            while (1) {
                components.back().push_back(cur+1);
                for (int j = 0; j < graph[cur].size(); ++j) {
                    if (graph[cur][j]->flow != 0 and graph[cur][j]->to < n and
                        !used[graph[cur][j]->to]) {
                        used[graph[cur][j]->to] = true;
                        cur = graph[cur][j]->to;
                        break;
                    }
                }
                if (cur + 1 == components.back().back()) {
                    break;
                }
            }
        }
        
        /* Output answer */
        std::cout << components.size() << std::endl;
        for(int i = 0; i < components.size(); ++i) {
            std::cout << components[i].size() << ' ';
            for (int j = 0; j < components[i].size(); ++j) {
                std::cout << components[i][j];
                if (j < components[i].size() - 1) {
                    std::cout << ' ';
                }
            }
            std::cout << std::endl;
        }
    }
    return 0;
}
