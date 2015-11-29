//
//  Run.h
//  SCC
//
//  Created by Anton Wetret on 15/10/15.
//  Copyright © 2015 Anton Karazeev. All rights reserved.
//

#ifndef Run_h
#define Run_h

#include <fstream>
#include <functional>
#include "BinomialHeap.h"
#include "Aho-Corasick.h"
#include "MaxFlow.hpp"
#include "Graph.h"
#include "Puzzle.h"
#include "Fenwick.h"

void Run() {
    // Amount of tests
    int quant = 1;
    assert(quant != 0);
    for (int i = 0; i < quant; ++i) {
        /*
         w - id of algorithm
         n - amount of vertexes
         */
        int w;
        std::cin >> w;
        switch (w) {
            case 0: {
                int n;
                std::cin >> n;
                graph<int, int, 1> g(n);
                std::cin >> g;
                g.Tarjan();
                break;
            }
            case 1: {
                int n;
                std::cin >> n;
                graph<int, int, 1> g(n);
                std::cin >> g;
                g.Kosaraju();
                break;
            }
            case 2: {
                int n;
                std::cin >> n;
                graph<int, int, 1> g(n);
                std::cin >> g;
                int src;
                std::cin >> src;
                g.Dijkstra(src);
                break;
            }
            case 3: {
                int n;
                std::cin >> n;
                graph<int, int, 1> g(n);
                std::cin >> g;
                g.BellmanFord(3);
                break;
            }
            case 4: {
                int n;
                std::cin >> n;
                graph<int, int, 1> g(n);
                std::cin >> g;
                g.FloydWarshall();
                break;
            }
            case 5: {
                Puzzle p;
                std::cin >> p;
                p.Solve();
                break;
            }
            case 7: {
                int n;
                std::cin >> n;
                assert(n != 0);
                graph<int, int, 0> g(n);
                std::cin >> g;
                g.Kruscal();
                break;
            }
            case 8: {
                int n;
                std::cin >> n;
                graph<int, int, 0> g(n);
                std::cin >> g;
                g.Prim();
                break;
            }
            case 13: {
                AhoCorasick a(255, 30);
                int amount;
                std::cin >> amount;
                
                std::string s;
                for (int i = 0; i < amount; ++i) {
                    std::cin >> s;
                    a.add_string(s);
                }
                
                std::cin >> s;
                int res = a.count_entry(s);
                std::cout << res;
                break;
            }
            case 9: {
                int n;
                std::cin >> n;
                MaxFlow m(n);
                
                int t, s;
                std::cin >> t;
                std::cin >> s;
                
                std::cin >> m;
                std::pair<double, double> ans = m.Flow(t, s, Inf);
                std::cout << ans.first << ' ' << ans.second;
                break;
            }
            case 10: {
                //TODO: Do it!
                break;
            }
        }
    }
}

#endif /* Run_h */
