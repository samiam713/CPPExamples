//
//  BloomFilter.hpp
//  BloomFilter
//
//  Created by Samuel Donovan on 5/4/20.
//  Copyright © 2020 Samuel Donovan. All rights reserved.
//

#ifndef BloomFilter_hpp
#define BloomFilter_hpp

#include <functional>

class BloomFilter {
private:
    struct DumbHasher {
        inline int operator()(int entry) {return entry*m;}
        DumbHasher(int m) : m(m) {}
        DumbHasher() {}
    private:
        int m;
    };
    
public:
    
    BloomFilter(int numIndices, int numHashers);
    ~BloomFilter();
    
    void insert(int val);
    bool check(int val);
    
private:
    
    void setBit(int index);
    bool checkBit(int index);
    
    inline int hashToIndex(int value);
    
    int numIndices;
    int numHashers;
    
    DumbHasher* hashers;
    unsigned long boolArray;
};

#endif /* BloomFilter_hpp */
