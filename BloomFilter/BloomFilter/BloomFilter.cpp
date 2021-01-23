//
//  BloomFilter.cpp
//  BloomFilter
//
//  Created by Samuel Donovan on 5/4/20.
//  Copyright © 2020 Samuel Donovan. All rights reserved.
//

#include "BloomFilter.hpp"

BloomFilter::BloomFilter(int numIndices, int numHashers) :
numIndices(numIndices), numHashers(numHashers), boolArray((unsigned long)0), hashers(new DumbHasher[numHashers]()) {
    
    for (int i = 0; i < numHashers; ++i) {
        hashers[i] = DumbHasher(i);
    }
}

BloomFilter::~BloomFilter() {delete[] hashers;}

void BloomFilter::insert(int val) {
    for (int i = 0; i < numHashers; ++i) {
        setBit(hashToIndex(hashers[i](val)));
    }
}

bool BloomFilter::check(int val) {
    for (int i = 0; i < numHashers; ++i) {
        if (!checkBit(hashToIndex(hashers[i](val)))) {
            return false;
        }
    }
    return true;
}

void BloomFilter::setBit(int index) {
    boolArray |= (1<<index);
}

bool BloomFilter::checkBit(int index) {
    return (boolArray & 1<<index)>0;
}

inline int BloomFilter::hashToIndex(int value) {
    return value%numIndices;
}

