//
//  Puzzle.h
//  Puzzle
//
//  Created by Anton Wetret on 10/3/15.
//  Copyright © 2015 Anton Karazeev. All rights reserved.
//

#ifndef Puzzle_h
#define Puzzle_h

#define trace(x) std::cout << x << std::endl;

#include <set>
#include <vector>
#include <map>
#include <queue>
#include <fstream>
#include <assert.h>
#include <math.h>

class Puzzle {
public:
    Puzzle();
    
    bool IsSolv() const;
    
    int CalcManh() const;
    int CalcEdge() const;
    int Solve();
    
    template <typename A, typename B, typename C, typename D>
    friend void MakeMoves(Puzzle& current, std::priority_queue<std::pair<Puzzle, int>, std::vector<std::pair<Puzzle, int> >, C>& seq, std::set<Puzzle, A>& openset, std::set<Puzzle, A>& closedset, std::map<Puzzle, int, B>& dist, std::map<Puzzle, Puzzle, D>& came_from);
    
    template <typename D>
    friend std::vector<Puzzle> ReconstructPath(std::map<Puzzle, Puzzle, D>& came_from, Puzzle goal);
    
    Puzzle& operator=(const Puzzle& p);
    friend std::ifstream& operator>>(std::ifstream& stream, Puzzle& p);
    friend std::ostream& operator<<(std::ostream& stream, Puzzle p);
private:
    /* Dimension of Puzzle */
    int dim_ = 4;
    /* Position of Zero */
    int c_;
    /* Grid */
    std::vector<int> grid_;
};

#pragma mark Implementation

#pragma mark > Class Puzzle

Puzzle::Puzzle() {
    
}

bool Puzzle::IsSolv() const {
    int res = 0;
    for (int i = 0; i < dim_*dim_; ++i) {
        for (int j = i+1; j < dim_*dim_; ++j) {
            if (grid_[i] != 0 && grid_[j] != 0 && grid_[i] > grid_[j]) {
                res += 1;
            }
        }
    }
    return ((res % 2) == 0 && (dim_-(c_/dim_)) % 2 == 1) || ((res % 2) == 1 && (dim_-(c_/dim_)) % 2 == 0);;
}

int Puzzle::CalcManh() const {
    int res = 0;
    for (int i = 0; i < dim_*dim_; ++i) {
        if (grid_[i] != 0) {
            res += abs((i/dim_) - ((grid_[i]-1)/dim_));
            res += abs((i%dim_) - ((grid_[i]-1)%dim_));
        } else {
            res += abs((i/dim_) - dim_ + 1);
            res += abs((i%dim_) - dim_ + 1);
        }
    }
    return res;
}

int Puzzle::CalcEdge() const {
    int res = 0;
    if (grid_[1] == 2 && grid_[4] == 5 && grid_[0] != 1) {
        res += 2;
    }
    if (grid_[8] == 9 && grid_[13] == 14 && grid_[12] != 13) {
        res += 2;
    }
    if (grid_[2] == 3 && grid_[7] == 8 && grid_[3] != 4) {
        res += 2;
    }
    if (grid_[14] == 15 && grid_[11] == 12 && grid_[15] != 0) {
        res += 2;
    }
    if (grid_[0] != 1) {
        res += 1;
    }
    if (grid_[12] != 13) {
        res += 1;
    }
    if (grid_[3] != 4) {
        res += 1;
    }
    if (grid_[15] != 0) {
        res += 1;
    }
    return res;
}

template <typename A, typename B, typename C, typename D>
void MakeMoves(Puzzle& current, std::priority_queue<std::pair<Puzzle, int>, std::vector<std::pair<Puzzle, int> >, C>& seq, std::set<Puzzle, A>& openset, std::set<Puzzle, A>& closedset, std::map<Puzzle, int, B>& dist, std::map<Puzzle, Puzzle, D>& came_from) {
    for (int i = 0; i < 4; ++i) {
        Puzzle tmp = current;
        if (i == 0 && current.c_/current.dim_ > 0) {
            tmp.grid_[tmp.c_] = tmp.grid_[tmp.c_-tmp.dim_];
            tmp.grid_[tmp.c_-tmp.dim_] = 0;
            tmp.c_ -= tmp.dim_;
        }
        if (i == 1 && current.c_%current.dim_ > 0) {
            tmp.grid_[tmp.c_] = tmp.grid_[tmp.c_-1];
            tmp.grid_[tmp.c_-1] = 0;
            tmp.c_ -= 1;
        }
        if (i == 2 && current.c_/current.dim_ < current.dim_-1) {
            tmp.grid_[tmp.c_] = tmp.grid_[tmp.c_+tmp.dim_];
            tmp.grid_[tmp.c_+tmp.dim_] = 0;
            tmp.c_ += tmp.dim_;
        }
        if (i == 3 && current.c_%current.dim_ < current.dim_-1) {
            tmp.grid_[tmp.c_] = tmp.grid_[tmp.c_+1];
            tmp.grid_[tmp.c_+1] = 0;
            tmp.c_ += 1;
        }
        
        if (closedset.count(tmp) == 0) {
            int tentative = dist[current] + 1;
            if (openset.count(tmp) || dist.count(tmp) == 0 || tentative < dist[tmp]) {
                dist[tmp] = tentative;
                came_from[tmp] = current;
                if (openset.count(tmp) == 0) {
                    seq.push({tmp, dist[tmp] + 2*tmp.CalcManh() + 3*tmp.CalcEdge()});
                    openset.insert(tmp);
                }
            }
        }
    }
}

template <typename D>
std::vector<Puzzle> ReconstructPath(std::map<Puzzle, Puzzle, D>& came_from, Puzzle current) {
    std::vector<Puzzle> total_path;
    while (came_from.find(current) != came_from.end()) {
        total_path.push_back(current);
        current = came_from[current];
    }
    return total_path;
}


int Puzzle::Solve() {
    if (this->IsSolv()) {
        auto mycomp = [](Puzzle a, Puzzle b) {
            return a.grid_ < b.grid_;
        };
        std::set<Puzzle, decltype(mycomp)> closedset(mycomp);
        std::set<Puzzle, decltype(mycomp)> openset(mycomp);
        openset.insert(*this);
        
        auto mycomp_c = [](const Puzzle& a, const Puzzle& b) {
            return a.grid_ < b.grid_;
        };
        /* came_from - to reconstruct path */
        std::map<Puzzle, Puzzle, decltype(mycomp_c)> came_from(mycomp_c);
        
        auto mycomp_d = [](const Puzzle& a, const Puzzle& b) {
            return a.grid_ < b.grid_;
        };
        
        /* dist - Shortest path to X state */
        std::map<Puzzle, int, decltype(mycomp_d)> dist(mycomp_d);
        dist[*this] = 0;
        
        auto mycomp_s = [](const std::pair<Puzzle, int>& a, const std::pair<Puzzle, int>& b) {
            return a.second > b.second;
        };
        /* seq - Priority queue of sorted puzzles by their heuristics */
        std::priority_queue<std::pair<Puzzle, int>, std::vector<std::pair<Puzzle, int> >, decltype(mycomp_s)> seq(mycomp_s);
        seq.push({*this, this->CalcEdge() + this->CalcManh() + dist[*this]});
        
        while (seq.size() != 0) {
            //            trace(seq.top().second)
            //            trace(seq.top().first)
            //            trace(' ')
            
            Puzzle current = seq.top().first;
            seq.pop();
            closedset.insert(current);
            
            if (current.CalcManh() == 0) {
                trace(current)
                trace("<-----------Success!------------>")
                std::vector<Puzzle> total_path = ReconstructPath(came_from, current);
                trace(dist[current] + 1)
                trace(this->c_)
                for (auto it = total_path.rbegin(); it != total_path.rend(); ++it) {
                    trace(it->c_)
                }
                return 2;
            }
            if (openset.count(current)) {
                openset.erase(openset.find(current));
            }
            MakeMoves(current, seq, openset, closedset, dist, came_from);
        }
        
        trace("Fail")
        return 2;
    } else {
        trace(-1)
        return -1;
    }
}

Puzzle& Puzzle::operator=(const Puzzle& p) {
    c_ = p.c_;
    grid_ = p.grid_;
    return *this;
}

std::ifstream& operator>>(std::ifstream& stream, Puzzle& p) {
    p.grid_.clear();
    for (int i = 0; i < p.dim_*p.dim_; ++i) {
        int x;
        stream >> x;
        if (x == 0) {
            p.c_ = i;
        }
        p.grid_.push_back(x);
    }
    return stream;
}

std::ostream& operator<<(std::ostream& stream, Puzzle p) {
    for (int i = 0; i < p.dim_*p.dim_; ++i) {
        if (i%p.dim_ == 0 && i != 0) {
            std::cout << std::endl;
        }
        std::cout << p.grid_[i] << ' ';
    }
    return stream;
}

#endif /* Puzzle_h */
