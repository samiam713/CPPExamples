//
//  main.cpp
//  QuickSort
//
//  Created by Samuel Donovan on 4/24/20.
//  Copyright © 2020 Samuel Donovan. All rights reserved.
//

#include <iostream>
#include <random>

using namespace std;

typedef vector<int>::iterator iter;

void qs(iter low, iter high) {
    const long length = high - low;
    
    // if distance <= 2, manually sort and end recursion
    if (length <= 2) {if (length == 2 && *high < *low) swap(*high, *low); return;}
    else {
        int const pivotValue = *high;
        iter rTraverser = high-1;
        iter lTraverser = low;
        while (lTraverser != rTraverser) {
            if (*lTraverser <= pivotValue) {
                ++lTraverser;
            } else {
                swap(*lTraverser, *(rTraverser--));
            }
        }
        
        // put pivot at x so that high values are in [x+1,high]
        // sort the subsections
        if (*lTraverser <= pivotValue) lTraverser++;
        swap(*lTraverser, *high);
        qs(low, lTraverser-1);
        qs(lTraverser+1,high);
    }
}

void qs(vector<int>& v) {qs(v.begin(), v.end()-1);}

constexpr int SIZE = 20;
int main(int argc, const char * argv[]) {
    
    random_device rd;
    vector<int> sortMe(SIZE);
    uniform_int_distribution<int> dist(1,100);
    
    for (int& integer : sortMe) integer = dist(rd);
    
    for (const auto& item : sortMe) cout << item << ' '; cout << endl;
    
    qs(sortMe);
    
    for (const auto& item : sortMe) cout << item << ' '; cout << endl;
    
    return 0;
}
