//
//  main.cpp
//  MaximalSquareProblem
//
//  Created by Samuel Donovan on 3/8/21.
//

#include <iostream>
#include <vector>
#include <set>
using namespace std;

int maximalSquareProblem(vector<bool> const & matrix, int m, int n) {
#define access(what,i,j) what[(i)*n + (j)]
    vector<int> cols(m*n,0);
    vector<int> rows(m*n,0);
    
    for (int i = m - 1; i >= 0; i--) {
        int longestContiguous = 0;
        
        for (int j = n - 1; j >= 0; j--) {
            if (access(matrix,i,j)) {
                longestContiguous += 1;
                access(rows,i,j) = longestContiguous;
            } else {
                longestContiguous = 0;
            }
        }
    }
    
    for (int j = n - 1; j >= 0; j--) {
        int longestContiguous = 0;
        
        for (int i = m - 1; i >= 0; i--) {
            if (access(matrix,i,j)) {
                longestContiguous += 1;
                access(cols,i,j) = longestContiguous;
            }
        }
    }
    
    int largestSquareSize = 0;
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            // check i, j for largest square
            
            // start with small square size, try and grow it
            int currentSquareSize = 0;
            while (i + currentSquareSize < m && j + currentSquareSize < n &&
                   access(rows,i + currentSquareSize,j) >= currentSquareSize + 1 && access(cols,i,j + currentSquareSize) >= currentSquareSize + 1) {
                currentSquareSize++;
            }
            if (currentSquareSize > largestSquareSize) {
                largestSquareSize = currentSquareSize;
            }
        }
    }
    
    int largestSquareArea = largestSquareSize*largestSquareSize;
    return largestSquareArea;
#undef access
}

int main(int argc, const char * argv[]) {
    // m by n matrix represented by vector<bool>
    cout << maximalSquareProblem({
        1,0,1,0,1,
        0,1,1,1,1,
        0,1,1,1,0,
        1,1,1,1,0,
        1,1,0,1,1
    }, 5, 5) << endl;
}
