//
//  main.cpp
//  fox_and_dinner
//
//  Created by Anton Karazeev on 07/08/2017.
//  Copyright © 2017 Anton Karazeev. All rights reserved.
//
//
//#include <iostream>
//#include <limits.h>
//#include <string.h>
//#include <vector>
//#include <queue>
//#include <math.h>
//#include <iomanip>
//
//std::vector<std::vector<int> > rGraph;
//
//int is_prime(int number) {
//    for (int i = 2; i <= sqrt(number + 1); ++i) {
//        if (number % i == 0) {
//            return false;
//        }
//    }
//    return true;
//}
//
//bool bfs(std::vector<std::vector<int> > rGraph, int s, int t, int parent[]) {
//    bool visited[rGraph.size()];
//    memset(visited, 0, sizeof(visited));
//    
//    std::queue <int> q;
//    q.push(s);
//    visited[s] = true;
//    parent[s] = -1;
//    
//    while (!q.empty()) {
//        int u = q.front();
//        q.pop();
//        
//        for (int v = 0; v < rGraph.size(); v++) {
//            if (visited[v] == false and rGraph[u][v] > 0) {
//                q.push(v);
//                parent[v] = u;
//                visited[v] = true;
//            }
//        }
//    }
//    
//    return (visited[t] == true);
//}
//
//int fordFulkerson(std::vector<std::vector<int> > graph, int s, int t) {
//    int u, v;
//    
//    for (u = 0; u < graph.size(); ++u) {
//        for (v = 0; v < graph.size(); ++v) {
//            rGraph[u][v] = graph[u][v];
//        }
//    }
//    
//    int parent[rGraph.size()];
//    
//    int max_flow = 0;
//    
//    while (bfs(rGraph, s, t, parent)) {
//        int path_flow = INT_MAX;
//        for (v = t; v != s; v = parent[v]) {
//            u = parent[v];
//            path_flow = std::min(path_flow, rGraph[u][v]);
//        }
//        for (v = t; v != s; v = parent[v]) {
//            u = parent[v];
//            rGraph[u][v] -= path_flow;
//            rGraph[v][u] += path_flow;
//        }
//        max_flow += path_flow;
//    }
//    return max_flow;
//}
//
//int main() {
//    
//    /* Read Foxes */
//    
//    int n; // number of foxes
//    
//    std::cin >> n;
//    
//    std::vector<int> foxes;
//    
//    int n_even = 0;
//    int n_odd = 0;
//    
//    for (int i = 0; i < n; ++i) {
//        int tmp;
//        std::cin >> tmp;
//        if (tmp % 2 == 0) {
//            ++n_even;
//        } else {
//            ++n_odd;
//        }
//        foxes.push_back(tmp);
//    }
//    
//    if (n_even != n_odd) {
//        std::cout << "Impossible" << std::endl;
//        return 0;
//    }
//    
//    /* Build Graph */
//    
//    std::vector<std::vector<int> > graph(n + 2, std::vector<int> (n + 2, 0));
//    rGraph = std::vector<std::vector<int> > (n + 2, std::vector<int> (n + 2, 0));
//    
//    // Fill capacity with 1 if the sum of numbers is prime number
//    for (int i = 1; i <= n; ++i) {
//        for (int j = 1; j <= n; ++j) {
//            if (is_prime(foxes[i-1] + foxes[j-1])) {
//                graph[i][j] = 1;
//                graph[j][i] = 1;
//            }
//        }
//    }
//    
//    // Fill capacity with 2 if number is even
//    for (int i = 1; i <= n; ++i) {
//        if (foxes[i - 1] % 2 == 0) {
//            graph[n + 1][i] = 2;
//            graph[i][n + 1] = 2;
//        } else {
//            graph[0][i] = 2;
//            graph[i][0] = 2;
//        }
//    }
//    
//    int t = 0;
//    int s = n + 1;
//    
//    /* Find Max Flow */
//    
//    int max_flow = fordFulkerson(graph, t, s);
//
////    // Print Matrix of Capacity
////    std::cout << "_CAPACITY_" << std::endl;
////    for (int i = 0; i < graph.size(); ++i) {
////        for (int j = 0; j < graph.size(); ++j) {
////            std::cout << graph[i][j] << ' ';
////        }
////        std::cout << std::endl;
////    }
//    std::vector<std::vector<int> > flow(graph);
//    for (int i = 0; i < graph.size(); ++i) {
//        for (int j = 0; j < graph.size(); ++j) {
//            flow[i][j] -= rGraph[i][j]; // subtract capacity of the edge
//        }
//        
//    }
//    // Print Matrix of Residual Graph
////    std::cout << "_FLOW_" << std::endl;
////    for (int i = 0; i < flow.size(); ++i) {
////        for (int j = 0; j < flow.size(); ++j) {
////            std::cout << std::setw(2) << flow[i][j] << ' ';
////        }
////        std::cout << std::endl;
////    }
////    std::cout << "Max flow: " << max_flow << std::endl;
////    if (max_flow < n) {
////        std::cout << "Impossible" << std::endl;
////        return 0;
////    }
//    
//    /* Find Groups of Foxes */
//    
//    std::vector<bool> used(n + 2, false);
//    
//    int prev_neighbor = -1;
//    int cur_neighbor = -1;
//    
//    std::vector<std::vector<int> > tables;
//    
//    for (int cur_v = 1; cur_v <= n; ++cur_v) {
//        if (used[cur_v] == true) {
//            continue;
//        }
//        
//        bool found = false;
//        
//        // Find Neighbor
//        for (int i = 1; i <= n; ++i) {
//            if (flow[cur_v][i] != 0 and i != cur_v and used[i] == false) {
//                prev_neighbor = cur_v;
//                cur_neighbor = i;
//                found = true;
//                break;
//            }
//        }
//        if (found == false) {
//            continue;
//        }
//        std::vector<int> cur_table;
//        std::vector<int> tmp_used;
//        
//        used[cur_v] = true;
//        cur_table.push_back(cur_v);
//        tmp_used.push_back(cur_v);
//        
//        while(cur_neighbor != cur_v) {
//            cur_table.push_back(cur_neighbor);
//            
//            used[cur_neighbor] = true;
//            tmp_used.push_back(cur_neighbor);
//            
//            int next_neighbor = -1;
//            
//            found = false;
//            for (int j = 1; j <= n; ++j) {
//                if (flow[cur_neighbor][j] != 0 and j != prev_neighbor and used[j] == false) {
//                    next_neighbor = j;
//                    found = true;
//                    break;
//                }
//            }
//            if (found == false) {
//                break;
//            }
//            prev_neighbor = cur_neighbor;
//            cur_neighbor = next_neighbor;
//        }
//        if (cur_table.size() >= 3) {
//            tables.push_back(cur_table);
//        } else {
//            for (int i = 0; i < tmp_used.size(); ++i) {
//                used[tmp_used[i]] = false;
//            }
//        }
//    }
//    
//    std::cout << tables.size() << std::endl;
//    for (int i = 0; i < tables.size(); ++i) {
//        std::cout << tables[i].size() << ' ';
//        for (int j = 0; j < tables[i].size(); ++j) {
//            std::cout << tables[i][j] << ' ';
//        }
//        std::cout << std::endl;
//    }
//    
//    return 0;
//}

/**
 * Since all primes except 2 are odd, the neighboring numbers must be
 * one odd and one even (note that a_i >= 2).
 * This results in bipartite graph.
 * Our goal is to decompose this graph into circular graphs.
 *
 * All vertices in circular graph has degree of 2, and in this problem,
 * all vertices in given graph would have just degree of 2 in decomposed graph.
 * We can use bipartity of given graph, putting 2 units of flow into each left
 * node and pull 2 units of flow from each right node.
 * If 2*N flow can be pushed into the graph the edges with flow must form
 * circular graphs, because considering only edges with flow, all vertices has
 * degree of 2.
 *
 * The algorithm described above runs in O(N^2).
 */

//
//  main.cpp
//  fox_and_dinner
//
//  Created by Anton Karazeev on 07/08/2017.
//  Copyright © 2017 Anton Karazeev. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <queue>

// Sieve of eratosthenes.
// Runs in O(N log log N).
std::vector<bool> eratosthenes(int N) {
    std::vector<bool> is_prime(N+1, true);
    is_prime[0] = is_prime[1] = false;
    
    const int LIM = static_cast<int>(sqrt(N));
    for(long long i = 2; i <= LIM; ++i) {
        if(is_prime[i]) {
            for(long long j = i*i; j <= N; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return is_prime;
}

// Dinic's algorithm.
// This solves maximum flow problem efficiently.
// Runs in O(V^2 E)
// (In practice, this algorithm is faster than expected from theoretical analysis.)
//
template<typename T, T INF, bool directed=true>
struct Dinic {
    struct Edge {
        int to;
        T cap, flow;
        Edge *back;
        Edge(int to, T cap, T flow, Edge *back) : to(to), cap(cap), flow(flow), back(back) {}
        
        bool remain() const {
            return flow < cap;
        }
        
        void add_flow(T f) {
            flow += f;
            back->flow -= f;
        }
    };
    
    std::vector<std::vector<Edge*> > g_;
    std::vector<int> memo_, level_;
    int src_, sink_;
    
    Dinic(int N, int src, int sink) : g_(N), memo_(N), level_(N), src_(src), sink_(sink) {}
    ~Dinic() {
        for (auto &row : g_) {
            for (auto e : row) {
                delete e;
            }
        }
    }
    
    T dinic_augment(int v, T cap) {
        if(v == sink_) return cap;
        
        const int N = g_[v].size();
        for(int i = memo_[v]; i < N; ++i) {
            const auto &e = g_[v][i];
            if(level_[e->to] != level_[v]+1) continue;
            if(!e->remain()) continue;
            const T f = dinic_augment(e->to, std::min(cap, e->cap - e->flow));
            if(f > 0) {
                e->add_flow(f);
                memo_[v] = i+1;
                return f;
            }
        }
        return 0;
    }
    
    void add_edge(int from, int to, T cap) {
        //cout << from << ' ' << to << endl;
        Edge *e = new Edge(to, cap, 0, nullptr);
        Edge *r = new Edge(from, directed ? 0 : cap, 0, e);
        e->back = r;
        g_[from].push_back(e);
        g_[to].push_back(r);
    }
    
    T calc() {
        T flow = 0;
        while(true) {
            // Calculate depth of each vertex
            fill(begin(level_), end(level_), -1);
            std::queue<int> q;
            q.push(src_);
            level_[src_] = 0;
            while(!q.empty()) {
                const int v = q.front();
                q.pop();
                for (const auto &e : g_[v]) {
                    if(e->remain() && level_[e->to] == -1) {
                        level_[e->to] = level_[v] + 1;
                        q.push(e->to);
                    }
                }
            }
            
            // Search for the residual path of shortest length
            bool updated = false;
            fill(begin(memo_), end(memo_), 0);
            while(true) {
                T add = dinic_augment(src_, INF);
                if(add == 0) break;
                flow += add;
                updated = true;
            }
            if(!updated) break;
        }
        return flow;
    }
};

// ostream support for vector.
template<typename T>
std::ostream& operator <<(std::ostream &os, const std::vector<T> &v) {
    bool first = true;
    for(const T &t : v) {
        if(!first) {
            std::cout << ' ';
        }
        os << t;
        first = false;
    }
    return os;
}

std::vector<bool> is_prime = eratosthenes(20000);

bool solve(bool first) {
    int N;
    if(!(std::cin >> N)) return false;
    if(!N) return false;
    
    std::vector<int> nodes(N);
    for(int i = 0; i < N; ++i) {
        std::cin >> nodes[i];
    }
    
    Dinic<int,10000> dinic(N+2, N, N+1);
    int flow = 0;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < i; ++j) {
            if(is_prime[nodes[i] + nodes[j]]) {
                if(nodes[i] % 2 == 0) dinic.add_edge(i, j, 1);
                else dinic.add_edge(j, i, 1);
            }
        }
        if(nodes[i] % 2 == 0) {
            dinic.add_edge(N, i, 2);
            flow += 2;
        } else {
            dinic.add_edge(i, N+1, 2);
        }
    }
    if(flow != N || dinic.calc() != flow) {
        std::cout << "Impossible" << std::endl;
    } else {
        const auto &graph = dinic.g_;
        std::vector<bool> used(N, false);
        std::vector<std::vector<int> > components;
        for(int i = 0; i < N; ++i) {
            if(used[i]) continue;
            int cur = i;
            used[i] = true;
            components.push_back(std::vector<int>());
            while(true) {
                components.back().push_back(cur+1);
                for(auto e : graph[cur]) {
                    if(e->flow != 0 && e->to < N && !used[e->to]) {
                        used[e->to] = true;
                        cur = e->to;
                        break;
                    }
                }
                if(cur+1 == components.back().back()) break;
            }
        }
        std::cout << components.size() << std::endl;
        for(const auto &c : components) {
            std::cout << c.size() << ' ';
            std::cout << c << std::endl;
        }
    }
    
    return true;
}

int main() {
    bool first = true;
    while(solve(first)) {
        first = false;
    }
    return 0;
}
