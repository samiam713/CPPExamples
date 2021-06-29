//
//  main.cpp
//  WalmartInterviewCoinChallenge
//
//  Created by Samuel Donovan on 3/11/21.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>

using namespace std;

struct CachePairHash;

// a cache so we don't recalculate solutions to subproblems we've already calculated
typedef pair<size_t,int> CachePair;
typedef unordered_map<CachePair,int,CachePairHash> Cache;

// function to hash the pair that is the key in the cache
// C++ doesn't do this automatically so adapted this hash function from
// https://www.techiedelight.com/use-std-pair-key-std-unordered_map-cpp/
struct CachePairHash
{
    size_t operator() (const CachePair &pair) const
    {
        return hash<size_t>()(pair.first) ^ hash<int>()(pair.second);
    }
} cachePairHash;

// recursive version to solve subproblem
int leastNumCoins(vector<int> const & coinVals, size_t lowerBound, int target, Cache & cache);

// returns -1 iff no possible way to hit target
// returns -2 if bad input
// coinVals[i] >= 1
int leastNumCoinsDriver(vector<int> const & coinVals, int target) {
    
    // check for valid coinVals
    for (int const val : coinVals) {
        if (val < 1) {
            cout << "Invalid Coin Value" << endl;
            return -2;
        }
    }
    
    // guard that we get input valid for leastNumCoins
    if (coinVals.size() == 0)  return -1;
    if (target <= 0) {
        if (target == 0) return 0;
        else {
            cout << "Invalid Target Amount" << endl;
            return -2;
        }
    }
    
    // now we create the cache to save time spent recalculating subproblem
    Cache cache;
    
    // return the case of the subproblem that is the original problem
    return leastNumCoins(coinVals, 0, target, cache);
}

// returns -1 iff no possible way to hit target
// finds solution to subproblem of hitting target using only the coins in coinVals[lowerBound:]
// precondition is that target > 0 (I make sure to enforce this precondition whenever calling the function)
int leastNumCoins(vector<int> const & coinVals, size_t lowerBound, int target, Cache & cache) {
    
    // takes 0 coins to get 0 value
    if (target == 0) return 0;
    
    // base case:
    // we're on our last coin usable
    if (lowerBound == coinVals.size() - 1) {
        // if we can hit target using N coins, remainder will be 0
        if (target % coinVals[lowerBound] == 0) {
            return target / coinVals[lowerBound];
        }
        // if we can't hit target using some amount of this final coin, return -1
        else {
            return -1;
        }
    }
    
    // we check if we've cached this subproblem's solution:
    Cache::iterator potentialCachedSolution = cache.find(CachePair(lowerBound,target));
    if (potentialCachedSolution != cache.end()) return potentialCachedSolution->second;
    
    // recursive case:
    
    // currentMin will contain the value of the best solution we've found so far
    // we haven't found a solution yet, so we set it to -1
    int currentMin = -1;
    
    // now see if we can do better
    // try using as many of the coin at 'lowerBound' as possible, starting with using 0
    int usingCurrentCoin = 0;
    
    // current target will hold how many coins we are targeting in the subproblem,
    // taking into account we are using 'usingCurrentCoin' of the coin at 'lowerBound'
    int currentTarget;
    while ((currentTarget = target - usingCurrentCoin*coinVals[lowerBound]) >= 0) {
        // find solution to subproblem using 'usingCurrentCoin' of the current coin
        int const subProblemResult = leastNumCoins(coinVals, lowerBound + 1, currentTarget, cache);
        
        // if we find a solution in the subproblem, check it out,
        // otherwise directly skip to checking using one more of the current coin
        if (subProblemResult != -1) {
            
            // if made it past above statement, we've found a solution to the problem 'potentialMin', which is:
            // (the lowest number of coins usable in the subproblem targeting target - usingCurrentCoin*coinVals[lowerBound]) + (the number of the current coins we're using)
            int const potentialMin = subProblemResult + usingCurrentCoin;
            
            // now we check if this 'potentialMin' has used less coins than our 'currentMin'
            // if we haven't found a 'currentMin' or 'potentialMin' has used less coins than our 'currentMin',
            // 'potentialMin' becomes the 'currentMin' - the best solution we've found so far
            if (currentMin == -1 || potentialMin < currentMin) currentMin = potentialMin;
        }
        
        usingCurrentCoin++;
    }
    
    // every possible solution has now had the opportunity to overwrite currentMin if it is smaller,
    // therefore currentMin is the minimum number of coins usable to solve this subproblem
    cache[CachePair(lowerBound,target)] = currentMin;
    return currentMin;
}

int main(int argc, const char * argv[]) {
    
    vector<int> const test1Vals {1,5,2};
    vector<int> const test2Vals {6,2,7};
    vector<int> const test3Vals {3,100,2};
    
    cout << "Valid solution exists:" << endl;
    cout << leastNumCoinsDriver(test1Vals, 11) << endl;
    cout << leastNumCoinsDriver(test2Vals, 12) << endl;
    cout << leastNumCoinsDriver(test3Vals, 105) << endl << endl;
    
    cout << "Valid solution does not exist:" << endl;
    cout << leastNumCoinsDriver(test2Vals, 5) << endl << endl;
    
    cout << "For fun:" << endl;
    cout << leastNumCoinsDriver(test2Vals, 1<<14) << endl;
    
    return 0;
}
