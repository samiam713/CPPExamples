//
//  DirectedGraph.cpp
//  WhatIsDecltype
//
//  Created by Samuel Donovan on 4/23/20.
//  Copyright © 2020 Samuel Donovan. All rights reserved.
//

#include "DirectedGraph.hpp"

using namespace::std;

Dijsktra DirectedGraph::calculateDijsktra(size_t start) const {
    const size_t SIZE = outgoing.size();
    Dijsktra baby(SIZE, start);
    vector<bool> searched;
    searched.resize(SIZE, false);
    
    size_t current = start;
    bool haveOneToSearch = true;
    while (haveOneToSearch) {
        
        searched[current] = true;
        
        // update all other nodes
        for (const auto & edge : outgoing[current]) {
            
            const size_t candidateWeight = baby.minWeight[current] + edge.weight;
            
            if (baby.minWeight[edge.destination] > candidateWeight) {
                baby.minWeight[edge.destination] = candidateWeight;
                baby.predecessor[edge.destination] = current;
            }
        }
        
        // find the next node to search
        size_t currentMin = INF;
        haveOneToSearch = false;
        for (size_t i = 0; i < SIZE; i++) {
            if (!searched[i] && (baby.minWeight[i] < currentMin)) {
                current = i;
                currentMin = baby.minWeight[i];
                haveOneToSearch = true;
            }
        }
    }
    
    return baby;
}
