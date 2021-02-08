//
//  main.cpp
//  AsteroidGreedyAlgorithm
//
//  Created by Samuel Donovan on 2/7/21.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

/*
 You want to determine the chemical composition of an asteroid by shooting lasers at certain frequencies at the asteroid. There are n substances in the asteroid. Each substance si has a range [li, hi] (li ≤ hi) where it will react to the laser exactly if the frequency is in that range. Design an efficient algorithm to figure out the minimum number of frequencies you need to shoot the lasers at so that every substance will react to at least one frequency. Prove the correctness of your algorithm.
 */

struct Chemical {
    int id; // unique id 0..<N for finding in a vector
    int low;
    int high;
    
    Chemical(int id, int low, int high) :
    id(id), low(low), high(high) {}
};

struct ChemLowLT {
    bool operator() (Chemical lhs, Chemical rhs) {return lhs.low < rhs.low;}
};

struct ChemHighLT {
    bool operator() (Chemical lhs, Chemical rhs) {return lhs.high < rhs.high;}
};

int laserCount(vector<Chemical> const & range) {
    
    if (range.size() == 0) return 0;
    
    int numZaps {0};
    
    set<int> hasReacted;
    
    vector<Chemical> earlyStart(range);
    vector<Chemical> earlyFinish(range);
    
    sort(earlyStart.begin(), earlyStart.end(), ChemLowLT());
    sort(earlyFinish.begin(), earlyFinish.end(), ChemHighLT());
    
    vector<Chemical>::iterator earlyStartTraverser = earlyStart.begin();
    vector<Chemical>::iterator earlyFinishTraverser = earlyFinish.begin();
    
    while (true)  {
        
        // if this is the earliest active finisher
        if (hasReacted.find(earlyFinishTraverser->id) == hasReacted.end()) {
            ++numZaps;
            // traverse through earliest starts and react all of the ones applicable
            while (earlyStartTraverser->low <= earlyFinishTraverser->high) {
                hasReacted.insert(earlyStartTraverser->id);
                ++earlyStartTraverser;
                if (earlyStartTraverser == earlyStart.end()) goto loopEnd;
            }
        }
        ++earlyFinishTraverser;
    }
    
    loopEnd:
    
    return numZaps;
}

int main(int argc, const char * argv[]) {
    vector<Chemical> chemicals {Chemical(0,0,0),Chemical(1,0,1),Chemical(2,0,1),
        Chemical(3,1,2),Chemical(4,1,2),Chemical(5,2,2)};
    cout << laserCount(chemicals) << endl;
}
