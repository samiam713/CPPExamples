//
//  Graph.hpp
//  DijkstraBounded
//
//  Created by Samuel Donovan on 2/17/21.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <stdio.h>
#include <unordered_map>
#include <unordered_set>

typedef int Node;

struct WeightedEdge {
    Node node;
    int weight;
};

class Graph {
public:
    std::unordered_set<WeightedEdge> const & getOutgoingEdges(Node node) const {return outgoingEdges.find(node)->second;}
    size_t size() const {return outgoingEdges.size();}
private:
    std::unordered_map<Node,std::unordered_set<WeightedEdge>> outgoingEdges;
};

#endif /* Graph_hpp */
