//
//  main.cpp
//  HeapExample
//
//  Created by Samuel Donovan on 4/21/20.
//  Copyright © 2020 Samuel Donovan. All rights reserved.
//

#include <iostream>
#include "Heap.h"
#include <iostream>
#include <limits.h>

using namespace std;

int main(int argc, const char * argv[]) {
        
    vector<int> const vec = {14, 3, 18, 48, 23, 21, 13, 4, 25, 33};
    
    Heap<int,less<int>> myHeap(vec);
    
    cout << myHeap << endl;
    
    return 0;
}
