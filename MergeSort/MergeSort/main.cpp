//
//  main.cpp
//  MergeSort
//
//  Created by Samuel Donovan on 4/23/20.
//  Copyright © 2020 Samuel Donovan. All rights reserved.
//

#include <iostream>
#include <random>

using namespace std;

int const SIZE = 50;

vector<int> sorter(vector<int> const & sortMe) {
    if (sortMe.size() < 2) {
        return sortMe;
    } else {
        auto halfway = sortMe.begin() + sortMe.size()/2;
        
        auto firstHalf = sorter(vector<int>(sortMe.begin(),halfway));
        auto secondHalf = sorter(vector<int>(halfway,sortMe.end()));
        
        auto firstIterator = firstHalf.begin();
        auto secondIterator = secondHalf.begin();
        
        vector<int> baby;
        
        for (size_t i = 0; i < sortMe.size(); i++) {
            if (firstIterator == firstHalf.end()) {
                baby.push_back(*secondIterator);
                secondIterator++;
            } else if (secondIterator == secondHalf.end()) {
                baby.push_back(*firstIterator);
                firstIterator++;
            } else if (*secondIterator < *firstIterator) {
                baby.push_back(*secondIterator);
                secondIterator++;
            } else {
                baby.push_back(*firstIterator);
                firstIterator++;
            }
        }
        return baby;
    }
}

int main(int argc, const char * argv[]) {
    vector<int> v;
    
    random_device randomness;
    uniform_int_distribution<int> distrib(0,100);
    
    for (int i = 0; i < SIZE; i++) {
        v.push_back(distrib(randomness));
    }
    
    auto sorted = sorter(v);
    
    bool checker = true;
    for (int i = 0; i < SIZE - 1; i++) {
        if (sorted[i] > sorted[i+1]) {
            checker = false;
        }
    }
    for (int lol = 0; lol < SIZE; lol++) {
        cout << sorted[lol] << endl;
    }
}
