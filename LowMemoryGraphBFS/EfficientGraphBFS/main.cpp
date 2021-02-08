//
//  main.cpp
//  EfficientGraphBFS
//
//  Created by Samuel Donovan on 1/25/21.
//

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

bool isChild(vector<int> const & graph, int parent, int child) {
    return graph[parent] >> child & 1;
}

struct SearchPair {
    int search;
    int distance;
    
    SearchPair(int search, int distance) :
    search(search), distance(distance) {}
};

int bfs(vector<int> graph, int source, int target) {
    
    if (source == target) return 0;
    
    int numChildren = int(graph.size());
    
    int encountered = 1 << source;
    
    queue<SearchPair> q;
    q.push(SearchPair(source,0));
    
    while (!q.empty()) {
        int examining = q.front().search;
        int nextDistance = q.front().distance+1;
        
        q.pop();
        
        for (int i = 0; i < numChildren; i++) {
            if (isChild(graph, examining, i) && !(encountered >> i == 1)) {
                if (i == target) return nextDistance;
                encountered |= (1 << i);
                q.push(SearchPair(i, nextDistance));
            }
        }
    }
    
    return -1;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
