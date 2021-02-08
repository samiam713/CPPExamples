//
//  MedianDataStructure.cpp
//  MedianDataStructure
//
//  Created by Samuel Donovan on 2/7/21.
//

#include "MedianDataStructure.hpp"

void MedianDataStructure::extractMedian() {
    // there is no median
    if (sizeZero) return;
    
    if (size() == 1) {sizeZero = true; return;}
    
    bool const replaceUsingLesser = lesser.size() == greater.size();
    
    if (replaceUsingLesser) {
        // replace using lesser
        auto const lesserLast = --lesser.end();
        median = *lesserLast;
        lesser.erase(lesserLast);
    }
    else {
        // replace using greater
        auto greaterFirst = greater.begin();
        median = *greaterFirst;
        greater.erase(greaterFirst);
    }
    // correctImbalances();
}

void MedianDataStructure::insert(int i) {
    if (sizeZero) {median = i; sizeZero = false; return;}

    if (i <= median) {
        lesser.insert(i);
    } else {
        greater.insert(i);
    }
    correctImbalances();
}

bool MedianDataStructure::remove(int i) {
    if (sizeZero) return false;
    
    if (i == median) {
        extractMedian();
        return true;
    }
    // i potentially in lesser
    else if (i < median) {
        size_t const removed = lesser.erase(i);
        if(removed == 0) return false;
    }
    // i potentially in greater
    else {
        size_t const removed = greater.erase(i);
        if(removed == 0) return false;
    }
    correctImbalances();
    return true;
}

void MedianDataStructure::correctImbalances() {
    if (lesser.size() < greater.size() - 1) rotateLeft();
    else if (greater.size() < lesser.size() ) rotateRight();
}

void MedianDataStructure::rotateLeft() {
    auto const greaterFirst = greater.begin();
    lesser.insert(median);
    median = *greaterFirst;
    greater.erase(greaterFirst);
}

void MedianDataStructure::rotateRight() {
    auto const lesserLast = --lesser.end();
    
    greater.insert(median);
    median = *lesserLast;
    lesser.erase(lesserLast);
}
