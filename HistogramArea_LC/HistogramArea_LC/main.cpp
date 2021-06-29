//
//  main.cpp
//  HistogramArea_LC
//
//  Created by Samuel Donovan on 6/5/21.
//

#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        size_t const n = heights.size();
        vector<int> lhsEnd(n,0);
        vector<int> rhsEnd(n,int(n-1));
        
        if (n <= 1) {
            if (n == 1) {
                return heights[0];
            } else {
                return 0;
            }
        }
        
        vector<int> possibleEnds;
        possibleEnds.push_back(0);
        
        // establishes the lhsEnd[i]
        for (int i = 1; i < n; i++) {
            int const currentHeight = heights[i];
            
            if (heights[i-1] < currentHeight) {
                lhsEnd[i] = i;
            } else {
                // we are going to take stuff off the stack until we know something that can stop us
                while (true) {
                    if (possibleEnds.empty()) {
                        break;
                    }
                    const int stackIndex = possibleEnds.back();
                    const int poppedHeight = heights[stackIndex];
                    
                    // this is not going to stop a rectangle with currentHeight
                    if (poppedHeight >= currentHeight) {
                        possibleEnds.pop_back();
                        if (poppedHeight == currentHeight) {
                            lhsEnd[i] = lhsEnd[stackIndex];
                            break;
                        }
                    }
                    // this index will stop our rectangle
                    else {
                        lhsEnd[i] = stackIndex+1;
                        break;
                    }
                }
            }
            
            possibleEnds.push_back(i);
        }
        
        possibleEnds.clear();
        possibleEnds.push_back(int(n-1));
        
        for (int i = int(n)-2; i >= 0; i--) {
            int const currentHeight = heights[i];
            
            if (heights[i+1] < currentHeight) {
                rhsEnd[i] = i;
            } else {
                // we are going to take stuff off the stack until we know something that can stop us
                while (true) {
                    if (possibleEnds.empty()) {
                        break;
                    }
                    const int stackIndex = possibleEnds.back();
                    const int poppedHeight = heights[stackIndex];
                    
                    // this is not going to stop a rectangle with currentHeight
                    if (poppedHeight >= currentHeight) {
                        possibleEnds.pop_back();
                        if (poppedHeight == currentHeight) {
                            rhsEnd[i] = rhsEnd[stackIndex];
                            break;
                        }
                    }
                    // this index will stop our rectangle
                    else {
                        rhsEnd[i] = stackIndex-1;
                        break;
                    }
                }
            }
            possibleEnds.push_back(i);
        }
        
        int maxArea = 0;
        for (int i = 0; i < n; i++) {
            int const width = rhsEnd[i] - lhsEnd[i] + 1;
            int const height = heights[i];
            int const area = width*height;
            if (area > maxArea) maxArea = area;
        }
        return maxArea;
    }
};

//int main() {
//    vector<int> heights {3,6,5,7,4,8,1,0};
//
//    Solution s;
//    const int ans = s.largestRectangleArea(heights);
//    cout << "Ans: " << ans << endl;
//}

