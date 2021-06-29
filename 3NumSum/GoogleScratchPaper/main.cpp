//
//  main.cpp
//  GoogleScratchPaper
//
//  Created by Samuel Donovan on 1/13/21.
//

#include <iostream>
#include <unordered_set>
#include <set>
#include <vector>
#include "Solution.hpp"

using namespace std;

vector<vector<int>> threeSum(vector<int> const & nums);

int main(int argc, const char * argv[]) {
    
    for (int i = 0; i <= 16; i++) {
        cout << "i == " << i << " && sqrt(i) == " << Solution().mySqrt(i) << endl;
    }
    
//    for(char c = 'A'; c <= 'Z'; c++) cout << '\'' << c << '\'' << ',';
//    cout << endl;
//
//    for(char c = 'a'; c <= 'z'; c++) cout << '\'' << c << '\'' << ',';
//    cout << endl;
//
//    vector<int> const integers {0,1,-1,4,2,1,-5,-4,-20,10,10,0,13,-2,-6,-9,3,6,0};
//
//    const vector<vector<int>> ans = threeSum(integers);
//
//    for (auto const &v : ans) {
//        for (auto const i : v) {
//            cout << i << ' ';
//        }
//        cout << endl;
//    }
//
//    return 0;
}



// find all possible unique triplets of numbers that add up to 0
vector<vector<int>> threeSum(vector<int> const & nums) {
    
    vector<vector<int>> toReturn;
    
    if(nums.size() < 3) return toReturn;
    
    set<int> atLeastOne;
    unordered_set<int> duplicateNums;
    int zeroCount = 0;
    
    for (const auto num : nums) {
        if (num == 0) {
            zeroCount++;
            if (zeroCount == 3) toReturn.push_back(vector<int>{0,0,0});
        } else {
            if (atLeastOne.find(num) != atLeastOne.end()) duplicateNums.insert(num);
        }
        atLeastOne.insert(num);
    }
    
    
    // use iterator i to loop through each num
        // if necessary ((*i & 1) == 0) check in duplicate nums (-*i/2) to see if we got a duplicate that works
        // copy the iterator into j
        // iterate through the rest of the nums greater, checking for compliments in atLeastOne
        // efficiency/stop duplicates: stop when compliment to a num would be less than *j
    
    for (set<int>::const_iterator i = atLeastOne.cbegin(); i != atLeastOne.cend(); i++) {
        if ((*i & 1) == 0) {
            const int dupCompliment = -(*i)/2;
            if (duplicateNums.find(dupCompliment) != duplicateNums.end()) toReturn.push_back(vector<int>{*i,dupCompliment,dupCompliment});
        }
        
        set<int>::const_iterator j = i;
        j++;
        while (j != atLeastOne.cend()) {
            const int compliment = -*i - *j;
            if (compliment <= *j) break;
            if (atLeastOne.find(compliment) != atLeastOne.end()) toReturn.push_back(vector<int>{*i,*j,compliment});
            j++;
        }
    }
    
    return toReturn;
}
