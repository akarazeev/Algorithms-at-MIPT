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
#include "KMP.hpp"

enum Algo {
    TARJAN = 0,
    KOSARAJU = 1,
    DIJKSTRA = 2,
    BELLMAN_FORD = 3,
    FLOYD_WARSHALL = 4,
    PUZZLE = 5,
    KRUSCAL = 7,
    PRIM = 8,
    MAX_FLOW = 9,
    DIJKSTRA_BIN_HEAP = 11,
    AHO_CORASICK = 13,
    KMP_ALG = 14
};

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
            case TARJAN: {
                int n;
                std::cin >> n;
                graph<int, int, 1> g(n);
                std::cin >> g;
                g.Tarjan();
                break;
            }
            case KOSARAJU: {
                int n;
                std::cin >> n;
                graph<int, int, 1> g(n);
                std::cin >> g;
                g.Kosaraju();
                break;
            }
            case DIJKSTRA: {
                int n;
                std::cin >> n;
                graph<int, int, 1> g(n);
                std::cin >> g;
                int src;
                std::cin >> src;
                g.Dijkstra(src);
                break;
            }
            case BELLMAN_FORD: {
                int n;
                std::cin >> n;
                graph<int, int, 1> g(n);
                std::cin >> g;
                int src;
                std::cin >> src;
                g.BellmanFord(src);
                break;
            }
            case FLOYD_WARSHALL: {
                int n;
                std::cin >> n;
                graph<int, int, 1> g(n);
                std::cin >> g;
                g.FloydWarshall();
                break;
            }
            case PUZZLE: {
                Puzzle p;
                std::cin >> p;
                p.Solve();
                break;
            }
            case KRUSCAL: {
                int n;
                std::cin >> n;
                assert(n != 0);
                graph<int, int, 0> g(n);
                std::cin >> g;
                g.Kruscal();
                break;
            }
            case PRIM: {
                int n;
                std::cin >> n;
                graph<int, int, 0> g(n);
                std::cin >> g;
                g.Prim();
                break;
            }
            case MAX_FLOW: {
                int n;
                std::cin >> n;
                MaxFlow m(n);
                
                int t, s;
                std::cin >> t;
                std::cin >> s;
                
                std::cin >> m;
                std::pair<double, double> ans = m.Flow(t, s, MaxFlow::kInf);
                std::cout << ans.first << ' ' << ans.second;
                break;
            }
            case DIJKSTRA_BIN_HEAP: {
                int n;
                std::cin >> n;
                graph<int, int, 1> g(n);
                std::cin >> g;
                int src;
                std::cin >> src;
                g.DijkstraBinHeap(src);
                break;
            }
            case AHO_CORASICK: {
                AhoCorasick a;
                
                std::string s;
                std::cin >> s;
                std::ifstream fin(s);
                assert(fin);
                int amount;
                std::cin >> amount;
                assert(amount != 0);
                for (int i = 0; i < amount; ++i) {
                    std::cin >> s;
                    assert(s != "");
                    a.add_string(s);
                }
                std::string content;
                while (std::getline(fin, s)) {
                    content += s;
                    content.push_back('\n');
                }
                assert(content != "");
//                auto res = a.count_seq(content);
//                for (auto it : res) {
//                    std::cout << it.first << std::endl;
//                }
                auto res = a.count_seq_sorted(content);
                for (auto it : res) {
                    std::cout << it.first << ' ';
                    for (auto it2 : it.second) {
                        std::cout << it2 << ' ';
                    }
                    std::cout << std::endl;
                }
                break;
            }
            case KMP_ALG:
                std::string s;
//                std::cin >> s;
//                std::ifstream fin(s);
                std::ifstream fin("tests/data1.txt");
                assert(fin);
                std::string content;
                while (std::getline(fin, s)) {
                    content += s;
                    content.push_back('\n');
                }
                assert(content != "");
                
                std::cin >> s;
                
                auto res = KMP(content, s);
                for_each(res.begin(), res.end(), [](int x) {
                    std::cout << x << ' ';
                });
                break;
        }
    }
}

#endif /* Run_h */
