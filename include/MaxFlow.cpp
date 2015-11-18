////
////  MaxFlow.cpp
////  MaxFlow
////
////  Created by Anton Wetret on 18/11/15.
////  Copyright © 2015 Anton Karazeev. All rights reserved.
////
//
//#include "MaxFlow.hpp"
//
//MaxFlow::MaxFlow(int n): data_(std::vector<std::vector<std::pair<double, double> > > (n, std::vector<std::pair<double, double> > (n, std::pair<double, double> ()))) {
//    
//}
//
//void MaxFlow::AddEdge(int from, int to, int cap, int cost) {
//    data_[from][to] = {cap, cost};
//    data_[to][from] = {0, -cost};
//}
//
//void MaxFlow::BellmanFord(std::vector<double>& dist, int s) {
//    for (int i = 0; i < this->Size(); ++i) {
//        dist[i] = Inf;
//    }
//    std::vector<int> pred(this->Size(), Inf);
//    dist[s] = 0;
//    
//    for (int i = 0; i < this->Size(); ++i) {
//        for (int v = 0; v < this->Size(); ++v) {
//            for (int u = 0; u < this->Size(); ++u) {
//                static std::pair<double, double> tmp (0, 0);
//                if (data_[u][v] != tmp && dist[v] > dist[u] + data_[u][v].second) {
//                    dist[v] = dist[u] + data_[u][v].second;
//                    pred[v] = u;
//                }
//            }
//        }
//    }
//}
//
//void MaxFlow::GetPath(std::vector<std::vector<std::pair<double, double> > >& flow, std::vector<int>& dist, std::vector<int>& path, double& df, int s, int t) {
//    dist = std::vector<int> (this->Size(), Inf);
//    std::vector<int> pred(this->Size(), Inf);
//    dist[s] = 0;
//    
//    for (int i = 0; i < this->Size(); ++i) {
//        for (int v = 0; v < this->Size(); ++v) {
//            for (int u = 0; u < this->Size(); ++u) {
//                static std::pair<double, double> tmp (0, 0);
//                if (data_[u][v] != tmp && flow[u][v].second < data_[u][v].first && dist[v] > dist[u] + data_[u][v].second) {
//                    dist[v] = dist[u] + data_[u][v].second;
//                    pred[v] = u;
//                }
//            }
//        }
//    }
//    
//    path.clear();
//    
//    if (dist[t] >= Inf) {
//        return;
//    }
//    assert(dist[t] < Inf);
//    df = Inf;
//    for (int i = t; i != s; i = pred[i]) {
//        path.push_back(i);
//        assert(pred[i] < Inf);
//        if (df > flow[pred[i]][i].first-flow[pred[i]][i].second) {
//            df = flow[pred[i]][i].first-flow[pred[i]][i].second;
//        }
//    }
//    path.push_back(s);
//}
//
//std::pair<double, double> MaxFlow::Flow(int s, int t, double max_flow) {
//    /* first - capacity, second - flow */
//    std::vector<std::vector<std::pair<double, double> > > flow(data_);
//    for (int i = 0; i < this->Size(); ++i) {
//        for (int j = 0; j < this->Size(); ++j) {
//            flow[i][j].second = 0;
//        }
//    }
//    std::vector<int> path;
//    std::vector<int> dist;
//    double curflow = 0;
//    double flow_cost = 0;
//    double df = 0;
//    
//    while (curflow < max_flow) {
//        this->GetPath(flow, dist, path, df, s, t);
//        if (dist[t] == Inf) {
//            break;
//        }
//        assert(df > 0);
//        int psize = static_cast<int>(path.size());
//        for (int i = 0; i < psize-1; ++i) {
//            assert(psize-i-1 >= 0);
//            assert(psize-i-2 >= 0);
//            std::cout << psize-i-2 << std::endl;
//            int from = path[psize-i-1];
//            int to = path[psize-i-2];
//            
//            flow[from][to].second += df;
//            flow[to][from].second -= df;
//            
//            flow_cost += data_[from][to].second * df;
//        }
//        curflow += df;
//    }
//    
//    return {curflow, flow_cost};
//}
//
//int MaxFlow::Size() {
//    return static_cast<int>(data_.size());
//}
//
//MaxFlow& operator>>(std::istream& stream, MaxFlow& m) {
//    int quant;
//    stream >> quant;
//    for (int i = 0; i < quant; ++i) {
//        static int from;
//        stream >> from;
//        static int to;
//        stream >> to;
//        static double cap;
//        stream >> cap;
//        static double cost;
//        stream >> cost;
//        m.AddEdge(from, to, cap, cost);
//        
//    }
//    return m;
//}
//
