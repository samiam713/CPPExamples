//
//  main.cpp
//  Stocks3
//
//  Created by Samuel Donovan on 6/1/21.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// You are given an array prices where prices[i] is the price of a given stock on the ith day.
// Find the maximum profit you can achieve.
// You may complete at most two transactions.
// Note: You may not engage in multiple transactions simultaneously
// (i.e., you must sell the stock before you buy again).


class Solution {
public:
    int maxProfit(vector<int>& prices) {
        
        const size_t n = prices.size();
        
        if (n < 2) return 0;
        
        // check for decreasing...cheat I don't like it
        vector<int>::iterator curr = prices.begin();
        int last = *curr;
        curr++;
        
        while (true) {
            if (curr == prices.end()) return 0;
            if (*curr > last) break;
            else {
                last = *curr;
                curr++;
            }
        }
        
        // cout << "nice" << endl;
        
        // the real way is to save previous diagonal only... this uses n memory rather than n^2
        
        // ideally this is a dynamically allocated int* using a shared_ptr
        vector<int> lastDiagonal(n-1,0);
        vector<int> bufferDiagonal(n-2,0);
        
        vector<int> lowerBounded;
        vector<int> upperBounded;
        
        lowerBounded.reserve(n-1);
        upperBounded.reserve(n-1);
        
        // boundsToBest[i][j] is the best price doing one transaction in prices[i...j]
        // whenever j-i+1 >= 3,
        // boundsToBest[i][j] == max[boundsToBest[i+1][j],boundsToBest[i][j-1], prices[j] - prices[i]]
        
        // whenever j-i == 1 (ie j == i+1), boundsToBest[i][j] = prices[j] - prices[i]
        
        // we're gonna fill this in diagonally
        for (int i = 0; i < n - 1; i++) {
            const int ans = prices[i+1] - prices[i];
            lastDiagonal[i] = ans > 0 ? ans : 0;
        }
        
        lowerBounded.push_back(lastDiagonal[0]);
        upperBounded.push_back(lastDiagonal[n-2]);
        
        for (int k = 2; k < n; k++) {
            for (int i = 0; i < n - k; i++) {
                int const j = i+k;
                bufferDiagonal[i] = max(lastDiagonal[i], max(lastDiagonal[i+1], prices[j] - prices[i]));
            }
            
            copy(bufferDiagonal.begin(), bufferDiagonal.begin()+(n-k), lastDiagonal.begin());
            lowerBounded.push_back(lastDiagonal[0]);
            upperBounded.push_back(lastDiagonal[n-k-1]);
        }
        
        const int oneTransaction = lastDiagonal[0];
        
        int best = oneTransaction;
        
        for (auto x : lowerBounded) {
            cout << x << ' ';
        }
        cout << endl;
        
        for (auto x : upperBounded) {
            cout << x << ' ';
        }
        cout << endl;
        
        for (int offset = 1; offset < n - 2; offset++) {
            int const twoTransaction = upperBounded[offset-1] + lowerBounded[n-2-offset];

              cout << "Offset: " << offset << "; Two Transaction: " << twoTransaction << endl;
            if (twoTransaction>best) best = twoTransaction;
        }
            
        return best;
    }
};


int main(int argc, const char * argv[]) {
    vector<int> test0 {1,3,5,4,3,2,1,7,2,4};
    
    Solution solver;
    
    int ans0 = solver.maxProfit(test0);
    
    cout << "test0: " << ans0 << endl;
    
//    vector<int> test1;
//
//    for (int i = 10000; i >= 0; i--) {
//        test1.push_back(i);
//    }
//    for (int i = 10000; i >= 0; i--) {
//        test1.push_back(0);
//    }
//
//    int ans1 = solver.maxProfit(test1);
//
//    cout << "test1: " << ans1 << endl;
    
    return 0;
}

