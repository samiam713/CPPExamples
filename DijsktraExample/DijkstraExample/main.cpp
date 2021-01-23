//
//  main.cpp
//  WhatIsDecltype
//
//  Created by Samuel Donovan on 4/22/20.
//  Copyright © 2020 Samuel Donovan. All rights reserved.
//

#include <iostream>
#include "DirectedGraph.hpp"

using namespace std;

int main(int argc, const char * argv[]) {

    DirectedGraph graph(8);
    
    graph.addEdge(0, 1, 100);
    graph.addEdge(0, 7, 2);
    graph.addEdge(7, 6, 3);
    graph.addEdge(6, 2, 4);
    graph.addEdge(2, 4, 5);
    graph.addEdge(2, 5, 6);
    graph.addEdge(5, 4, 7);
    graph.addEdge(4, 3, 7);
    graph.addEdge(3, 1, 1);
    
    cout << graph.calculateDijsktra(0);
    
    return 0;
}
