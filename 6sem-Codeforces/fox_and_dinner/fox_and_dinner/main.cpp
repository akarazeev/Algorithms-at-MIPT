//
//  main.cpp
//  fox_and_dinner
//
//  Created by Anton Karazeev on 07/08/2017.
//  Copyright © 2017 Anton Karazeev. All rights reserved.
//

#include <iostream>
#include <limits.h>
#include <string.h>
#include <vector>
#include <queue>
#include <math.h>
#include <iomanip>

std::vector<std::vector<int> > rGraph;

int is_prime(int number) {
    for (int i = 2; i <= sqrt(number + 1); ++i) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

bool bfs(std::vector<std::vector<int> > rGraph, int s, int t, int parent[]) {
    bool visited[rGraph.size()];
    memset(visited, 0, sizeof(visited));
    
    std::queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v = 0; v < rGraph.size(); v++) {
            if (visited[v] == false and rGraph[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    
    return (visited[t] == true);
}

int fordFulkerson(std::vector<std::vector<int> > graph, int s, int t) {
    int u, v;
    
    for (u = 0; u < graph.size(); ++u) {
        for (v = 0; v < graph.size(); ++v) {
            rGraph[u][v] = graph[u][v];
        }
    }
    
    int parent[rGraph.size()];
    
    int max_flow = 0;
    
    while (bfs(rGraph, s, t, parent)) {
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = std::min(path_flow, rGraph[u][v]);
        }
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
        max_flow += path_flow;
    }
    return max_flow;
}

int main() {
    
    /* Read Foxes */
    
    int n; // number of foxes
    
    std::cin >> n;
    
    std::vector<int> foxes;
    
    int n_even = 0;
    int n_odd = 0;
    
    for (int i = 0; i < n; ++i) {
        int tmp;
        std::cin >> tmp;
        if (tmp % 2 == 0) {
            ++n_even;
        } else {
            ++n_odd;
        }
        foxes.push_back(tmp);
    }
    
    if (n_even != n_odd) {
        std::cout << "Impossible" << std::endl;
        return 0;
    }
    
    /* Build Graph */
    
    std::vector<std::vector<int> > graph(n + 2, std::vector<int> (n + 2, 0));
    rGraph = std::vector<std::vector<int> > (n + 2, std::vector<int> (n + 2, 0));
    
    // Fill capacity with 1 if the sum of numbers is prime number
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (is_prime(foxes[i-1] + foxes[j-1])) {
                graph[i][j] = 1;
                graph[j][i] = 1;
            }
        }
    }
    
    // Fill capacity with 2 if number is even
    for (int i = 1; i <= n; ++i) {
        if (foxes[i - 1] % 2 == 0) {
            graph[n + 1][i] = 2;
            graph[i][n + 1] = 2;
        } else {
            graph[0][i] = 2;
            graph[i][0] = 2;
        }
    }
    
    int t = 0;
    int s = n + 1;
    
    /* Find Max Flow */
    
    int max_flow = fordFulkerson(graph, t, s);

//    // Print Matrix of Capacity
//    std::cout << "_CAPACITY_" << std::endl;
//    for (int i = 0; i < graph.size(); ++i) {
//        for (int j = 0; j < graph.size(); ++j) {
//            std::cout << graph[i][j] << ' ';
//        }
//        std::cout << std::endl;
//    }
    std::vector<std::vector<int> > flow(graph);
    for (int i = 0; i < graph.size(); ++i) {
        for (int j = 0; j < graph.size(); ++j) {
            flow[i][j] -= rGraph[i][j]; // subtract capacity of the edge
        }
        
    }
    // Print Matrix of Residual Graph
//    std::cout << "_FLOW_" << std::endl;
//    for (int i = 0; i < flow.size(); ++i) {
//        for (int j = 0; j < flow.size(); ++j) {
//            std::cout << std::setw(2) << flow[i][j] << ' ';
//        }
//        std::cout << std::endl;
//    }
//    std::cout << "Max flow: " << max_flow << std::endl;
//    if (max_flow < n) {
//        std::cout << "Impossible" << std::endl;
//        return 0;
//    }
    
    /* Find Groups of Foxes */
    
    std::vector<bool> used(n + 2, false);
    
    int prev_neighbor = -1;
    int cur_neighbor = -1;
    
    std::vector<std::vector<int> > tables;
    
    for (int cur_v = 1; cur_v <= n; ++cur_v) {
        if (used[cur_v] == true) {
            continue;
        }
        
        bool found = false;
        
        // Find Neighbor
        for (int i = 1; i <= n; ++i) {
            if (flow[cur_v][i] != 0 and i != cur_v and used[i] == false) {
                prev_neighbor = cur_v;
                cur_neighbor = i;
                found = true;
                break;
            }
        }
        if (found == false) {
            continue;
        }
        std::vector<int> cur_table;
        std::vector<int> tmp_used;
        
        used[cur_v] = true;
        cur_table.push_back(cur_v);
        tmp_used.push_back(cur_v);
        
        while(cur_neighbor != cur_v) {
            cur_table.push_back(cur_neighbor);
            
            used[cur_neighbor] = true;
            tmp_used.push_back(cur_neighbor);
            
            int next_neighbor = -1;
            
            found = false;
            for (int j = 1; j <= n; ++j) {
                if (flow[cur_neighbor][j] != 0 and j != prev_neighbor and used[j] == false) {
                    next_neighbor = j;
                    found = true;
                    break;
                }
            }
            if (found == false) {
                break;
            }
            prev_neighbor = cur_neighbor;
            cur_neighbor = next_neighbor;
        }
        if (cur_table.size() >= 3) {
            tables.push_back(cur_table);
        } else {
            for (int i = 0; i < tmp_used.size(); ++i) {
                used[tmp_used[i]] = false;
            }
        }
    }
    
    std::cout << tables.size() << std::endl;
    for (int i = 0; i < tables.size(); ++i) {
        std::cout << tables[i].size() << ' ';
        for (int j = 0; j < tables[i].size(); ++j) {
            std::cout << tables[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    
    return 0;
}
