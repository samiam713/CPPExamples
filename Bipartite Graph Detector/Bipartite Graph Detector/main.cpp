//
//  main.cpp
//  Bipartite Graph Detector
//
//  Created by Samuel Donovan on 1/27/21.
//

#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

struct Node {
    int id;
    vector<Node*> children;
};

bool isBipartite(Node* startSearch) {
    unordered_set<int> encounteredAndOdd;
    
    unordered_set<int> encountered;
    encountered.insert(startSearch->id);
    
    queue<Node*> toSearch;
    
    while (!toSearch.empty()) {
        Node* searching = toSearch.front();
        toSearch.pop();
        
        // parentOdd <=> encounteredAndOdd contains searching
        bool parentOdd = encounteredAndOdd.find(searching->id) != encounteredAndOdd.end();
        
        for (Node* child : searching->children) {
            
            // if hasn't been encountered
            if (encountered.find(child->id) == encountered.end()) {
                // now has been encountered and must be searched
                encountered.insert(child->id);
                toSearch.push(child);
                
                // if the parent is even this one is oss
                if (!parentOdd) encounteredAndOdd.insert(child->id);
                
            } else { // else child has been encountered
                // ensure that is in opposite set
                bool childOdd = encounteredAndOdd.find(child->id) != encounteredAndOdd.end();
                if (parentOdd == childOdd) {
                    return false;
                }
            }
        }
    }
    
    return true;
}

int main(int argc, const char * argv[]) {
    cout << "the above function works in theory" << endl;
}
