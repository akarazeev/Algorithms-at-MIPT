//
//  Run.h
//  SCC
//
//  Created by Anton Wetret on 15/10/15.
//  Copyright © 2015 Anton Karazeev. All rights reserved.
//

#ifndef Run_h
#define Run_h

#define READ 0

void Run() {
    std::ifstream fin("test.txt");
    // Amount of tests
    int quant;
    if (READ) {
        fin >> quant;
    } else {
        std::cin >> quant;
    }
    assert(quant != 0);
    for (int i = 0; i < quant; ++i) {
//        std::cout << "Test #" << i+1 << std::endl;
        /*
         w - id of algorithm
         n - amount of vertexes
         */
        int w;
        if (READ) {
            fin >> w;
        } else {
            std::cin >> w;
        }
        switch (w) {
            case 0: {
                int n;
                fin >> n;
                graph<int, int, 1> g(n);
                fin >> g;
                g.Tarjan();
                break;
            }
            case 1: {
                int n;
                fin >> n;
                graph<int, int, 1> g(n);
                fin >> g;
                g.Kosaraju();
                break;
            }
            case 2: {
                int n;
                fin >> n;
                graph<int, int, 1> g(n);
                fin >> g;
                int src;
                fin >> src;
                g.Dijkstra(src);
                break;
            }
            case 3: {
                int n;
                fin >> n;
                graph<int, int, 1> g(n);
                fin >> g;
                std::vector<int> table;
                g.BellmanFord(3, table);
                for (int it : table) {
                    trace(it);
                }
                break;
            }
            case 4: {
                int n;
                fin >> n;
                graph<int, int, 1> g(n);
                fin >> g;
                g.FloydWarshall();
                break;
            }
            case 5: {
                Puzzle p;
                fin >> p;
                p.Solve();
                break;
            }
            case 6: {
                int n;
                fin >> n;
                graph<int, int, 0> g(n);
                fin >> g;
                g.Prim();
                break;
            }
            case 7: {
                int n;
                if (READ) {
                    fin >> n;
                } else {
                    std::cin >> n;
                }
                assert(n != 0);
                graph<int, int, 0> g(n);
                if (READ) {
                    fin >> g;
                } else {
                    std::cin >> g;
                }
                g.Kruscal();
                break;
            }
        }
//        std::cout << std::endl;
    }
}

#endif /* Run_h */
