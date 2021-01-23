//
//  DirectedGraph.hpp
//  WhatIsDecltype
//
//  Created by Samuel Donovan on 4/23/20.
//  Copyright © 2020 Samuel Donovan. All rights reserved.
//

#ifndef DirectedGraph_hpp
#define DirectedGraph_hpp

#include <iostream>
#include <vector>
#include <limits>

const size_t INF = std::numeric_limits<size_t>::max();

struct Edge {
    Edge(size_t destination, size_t weight) :
    destination(destination), weight(weight) {}
    
    size_t destination;
    size_t weight;
};

struct Dijsktra {
    Dijsktra(size_t size, size_t start) {
        minWeight.resize(size, INF);
        predecessor.resize(size, INF);
        minWeight[start] = 0;
        minWeight[start] = 0;
    }
    
    std::vector<size_t> minWeight;
    std::vector<size_t> predecessor;
    
    friend std::ostream& operator<<(std::ostream& os, Dijsktra d) {
        for (size_t i = 0; i < d.minWeight.size(); i++) {
            os << i << "'s minWeight: " << d.minWeight[i] << "; predecessor: " << d.predecessor[i] << ";" << std::endl;
        }
        return os;
    }
};

class DirectedGraph {
public:
    
    DirectedGraph(size_t size) {
        outgoing.resize(size, std::vector<Edge>());
        
    }
    
    void addEdge(size_t from, size_t to, size_t weight) {
        outgoing[from].push_back(Edge(to,weight));
    }
    
    Dijsktra calculateDijsktra(size_t start) const;
    
private:
    std::vector<std::vector<Edge>> outgoing;
};

#endif /* DirectedGraph_hpp */
