//
//  main.cpp
//  MedianDataStructure
//
//  Created by Samuel Donovan on 2/7/21.
//

#include <iostream>
#include "MedianDataStructure.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    vector<int> fantastic {1,6,3,4,7,2,5};
    
    MedianDataStructure mds(fantastic);
    
    cout << mds.getMedian() << endl;
    cout << mds.lesser.size() << ' ' << mds.greater.size() << endl;
    
    for (int i = 0; i < 7; i++) {
        mds.extractMedian();
        cout << mds.getMedian() << endl;
        cout << mds.lesser.size() << ' ' << mds.greater.size() << endl;
    }
    
    return 0;
}
