//
//  main.cpp
//  MedianOfTwoSortedArrays
//
//  Created by Samuel Donovan on 1/28/21.
//

#include <iostream>
#include <vector>

using namespace std;

typedef vector<int>::iterator iter;

double median(iter lb, iter ub) {
    long length = (ub-lb);
    
    if ((length&1) == 1) {
        // array length is odd:
        return double(lb[length/2]);
    } else {
        // array length is even:
        return double(lb[length/2] + lb[length/2 - 1])/2.0;
    }
}

// precondition: takes in range of values vec[lb..<ub] that has length > 0
// returns the iterator lt such that vec[lb..<lt] are all less than value (lt is first greater than value)
iter searchForIndexLessThan(iter lb, iter ub, int value) {
    // search for toReturn such that [lb..<toReturn] is less than value
    // and [toReturn..<ub] is greater than value
    long const length = ub-lb;
    if (length < 1) return lb;
    if (length == 1) return (*lb < value) ? ub : lb;
    if (value < *lb) return lb;
    if (value > *(ub-1)) return ub;
    
    iter mid = lb + length/2;
    iter lhAns = searchForIndexLessThan(lb, mid, value);
    if (lhAns == mid) return searchForIndexLessThan(mid, ub, value);
    return lhAns;
}

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    
    iter lb1 = nums1.begin();
    iter ub1 = nums1.end();
    
    iter lb2 = nums2.begin();
    iter ub2 = nums2.end();
    
    long const length1 = ub1 - lb1;
    long const length2 = ub2 - lb2;
    long const length = length1 + length2;
    
    bool lengthOdd = (length&1) == 1;
    long const thisManyLessThanMedian = length/2;
    
    // error:
    if (length1 == 0 && length2 == 0) return -1;
    
    // test if one array has zero length
    if (length1 == 0) return median(lb2, ub2);
    if (length2 == 0) return median(lb1, ub1);
    
    // now we know that both arrays have elements in them
    
    // binary search array1 for the legendary pair i1 and i2
    // (the upper bounds on the regions of v1 and v2 that contain all elements less than the median
    
    // binary search lb1 and ub1
    iter lb = lb1;
    iter ub = ub1;
    
    iter i1;
    iter i2;
    
    // loop invariant:
    // if i1 exists, it must be in subarray v1[lb1..<ub1]
    while (ub - lb > 0) {
        // guess i1 by taking the middleIndex mid of v1[lb1..<ub1]
        i1 = lb + (ub-lb)/2;
        
        // calculate i2 for i1 guess.
        i2 = searchForIndexLessThan(lb2, ub2, *i1);
        
        // if i1+i2 == tmltm, we found our i1 and i2
        const long sum = (i1-lb1) + (i2-lb2);
        if (sum == thisManyLessThanMedian) {
            
            // calculate smallest valid upperbound:
            
            // if odd, the smallest valid upperbound (*i1 or *i2) is the median
            if (lengthOdd) return  double(*i1);
            
            // if even and >= 2, average of smallest valid upperbound and largest valid of smaller half is the median
            if (i2 == lb2) return double(*(i1-1) + *i1)/2;
            else if (i1 == lb1) return double(*(i2-1) + *i1)/2;
            return double(max(*(i1-1), *(i2-1)) + *i1)/2;
            
        }
        if (sum < thisManyLessThanMedian) {
            // i1+i2 < tmltm, therefore i1 is in half above if it exists: v1[(mid+1)..<ub1]
            lb = i1+1;
        } else {
            // i1+i2 > tmltm, there i1 is in the half below if it exists: v1[lb1..<mid)
            ub = i1;
        }
    }
    // i1 is not in v1
    
    // do process for v2
    
    lb = lb2;
    ub = ub2;
    while (ub - lb > 0) {
        i1 = lb + (ub-lb)/2;
        i2 = searchForIndexLessThan(lb1, ub1, *i1);
        const long sum = (i1-lb2) + (i2-lb1);
        if (sum == thisManyLessThanMedian) {
            if (lengthOdd) return  double(*i1);
            
            // if even and >= 2, average of smallest valid upperbound and largest valid of smaller half is the median
            if (i2 == lb1) return double(*(i1-1) + *i1)/2;
            else if (i1 == lb2) return double(*(i2-1) + *i1)/2;
            return double(max(*(i1-1), *(i2-1)) + *i1)/2;
        }
        if (sum < thisManyLessThanMedian) {
            lb = i1+1;
        } else {
            ub = i1;
        }
    }
    
    cout << "FATAL ERROR: CHECK FOR REPEATS" << endl;
    return -1;
}

int main(int argc, const char * argv[]) {
    vector<int> v1 {0,2,4,7,11}; // 5
    vector<int> v2 {1,3,5,6,8,9,10}; // 7
    // there are 12 elements
    
    cout << findMedianSortedArrays(v1, v2) << endl;
    
    return 0;
    // [0,6)
    // [6,12)
}
