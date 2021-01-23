//
//  main.cpp
//  BloomFilter
//
//  Created by Samuel Donovan on 5/4/20.
//  Copyright © 2020 Samuel Donovan. All rights reserved.
//

#include <iostream>
#include "BloomFilter.hpp"

using namespace::std;

#define CHECK(value) cout << bloomFilter.check( value ) << endl;

int main(int argc, const char * argv[]) {
    
    BloomFilter bloomFilter(61, 4);
    
    bloomFilter.insert(5);
    bloomFilter.insert(6);
    bloomFilter.insert(20);
    bloomFilter.insert(30);
    
    cout.setf(ios_base::boolalpha);
    
    CHECK(5)
    CHECK(6)
    CHECK(7)
    CHECK(20)
    CHECK(21)
    
    return 0;
}
