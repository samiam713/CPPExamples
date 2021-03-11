//
//  DijkstraBounded.cpp
//  DijkstraBounded
//
//  Created by Samuel Donovan on 2/17/21.
//

#include <stdio.h>
#include "Graph.hpp"
#include <vector>

using namespace std;

typedef unordered_map<int,unordered_set<Node>>::iterator iter;

struct NodeData {
    Node predecessor;
    int shortestPath;
    NodeData(Node predecessor, int shortestPath) : predecessor(predecessor), shortestPath(shortestPath) {}
};

vector<NodeData> dijkstraBounded(Graph const & graph, Node origin) {
    // if our shortest path is -1, we know we have never encountered this node
    // if shortestPath < finalizedLessThan, we have finalized
    vector<NodeData> toReturn(graph.size(),NodeData(-1,-1));
    toReturn[origin].shortestPath = 0;
    
    // distance to the set of nodes that distance away
    unordered_map<int,unordered_set<Node>> distanceToNodes;
    
    distanceToNodes[0].insert(origin);
    
    // we have finalized everything less than 0 (nothing)
    int finalizedLessThan = 0;
    
    size_t numEdgesAdded {0};
    size_t const numEdgesToAdd = graph.size()-1;
    
    while (numEdgesAdded < numEdgesToAdd) {
        // mark all edges "finalizedLessThan" away as finalized
        iter nodesToFinalize = distanceToNodes.find(finalizedLessThan);
        int const allInLoopThisFarAway = finalizedLessThan;
        ++finalizedLessThan;
        
        // if we have no edges to finalize here, go on
        if(nodesToFinalize == distanceToNodes.end()) continue;
        
        for (Node const nodeToFinalize : nodesToFinalize->second) {
            ++numEdgesAdded;
            for (WeightedEdge const edgeToCheck : graph.getOutgoingEdges(nodeToFinalize)) {
                const int distanceFromNodeToFinalize = allInLoopThisFarAway + edgeToCheck.weight;
                if (toReturn[edgeToCheck.node].shortestPath == -1) {
                    // never encountered
                    distanceToNodes[allInLoopThisFarAway + edgeToCheck.weight].insert(edgeToCheck.node);
                    toReturn[edgeToCheck.node] = NodeData(nodeToFinalize,distanceFromNodeToFinalize);
                } else if (toReturn[edgeToCheck.node].shortestPath > finalizedLessThan) {
                    // possibly updatable to new shortestPath
                    
                    // check if you should update
                    if (toReturn[edgeToCheck.node].shortestPath > distanceFromNodeToFinalize) {
                        // update
                        // transfer from old set to new set
                        distanceToNodes[toReturn[edgeToCheck.node].shortestPath].erase(edgeToCheck.node);
                        distanceToNodes[allInLoopThisFarAway + edgeToCheck.weight].insert(edgeToCheck.node);
                        toReturn[edgeToCheck.node] = NodeData(nodeToFinalize,distanceFromNodeToFinalize);
                    }
                } else {
                    // been finalized... do nothing
                }
            }
        }
    }
    
    return toReturn;
}
