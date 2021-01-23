//
//  main.cpp
//  BubbleSort
//
//  Created by Samuel Donovan on 4/22/20.
//  Copyright © 2020 Samuel Donovan. All rights reserved.
//

#include <iostream>

using namespace std;

int const SIZE = 5;

void print(int* x, int size) {
    for (int i = 0; i < size; i++) {
        cout << x[i] << " ";
    }
    cout << endl;
}

void bsort(int* x, int size) {
    for (size_t j = size - 1; j > 0; j--) {
        // bubble from 0 to j
        for (size_t i = 0; i < j; i++) {
            if (!(x[i] < x[i+1])) {
                swap(x[i], x[i+1]);
            }
        }
        print(x,size);
    }
}

int main(int argc, const char * argv[]) {
    
    int x[SIZE] = {5,4,3,2,1};
    
    bsort(x,SIZE);
    
    return 0;
}
