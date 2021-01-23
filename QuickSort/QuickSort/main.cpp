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

constexpr int SIZE = 20;

void quickSort(vector<int> & vec) {
    if (vec.size() <= 2) {
        if (vec.size()==2) {
            if (vec[1] < vec[0]) {
                swap(vec[1], vec[0]);
            }
            return;
        } else {
            return;
        }
    } else {
        vector<int> low;
        vector<int> high;
        auto iterator = vec.begin();
        int pivot = *iterator;
        iterator++;
        while (iterator != vec.end()) {
            if (*iterator < pivot) {
                low.push_back(*iterator);
            } else {
                high.push_back(*iterator);
            }
            iterator++;
        }
        // now merge the lists
        quickSort(low);
        quickSort(high);
        size_t i = 0;
        for (const auto& item: low) {
            vec[i] = item;
            i++;
        }
        vec[i] = pivot;
        i++;
        for (const auto& item : high) {
            vec[i] = item;
            i++;
        }
    }
}

int main(int argc, const char * argv[]) {
    
    random_device rd;
    
    vector<int> sortMe(SIZE);
    
    uniform_int_distribution<int> dist(1,100);
    
    for (auto& integer : sortMe) {
        integer = dist(rd);
    }
    
    quickSort(sortMe);
    
    for (const auto& item : sortMe) {
        cout << item << ' ';
    }
    cout << endl;
    
    return 0;
}
