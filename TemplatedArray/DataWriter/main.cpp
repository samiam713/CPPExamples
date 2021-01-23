//
//  main.cpp
//  DataWriter
//
//  Created by Samuel Donovan on 7/11/20.
//  Copyright © 2020 Samuel Donovan. All rights reserved.
//

#include <iostream>
#include <algorithm>

using namespace std;

template <typename T>
struct Array {
    T* data;
    int count;
    int pwr2;
    
    Array() :
    count(0), pwr2(4), data(new int[4])
    {}
    
    ~Array() {
        delete [] data;
    }
    
    void doubleCapacity() { // coming in, everything accurate
        pwr2 <<= 2;
        T* newData = new T[pwr2];
        std::copy(data, data+count, newData);
        delete [] data;
        data = newData;
    }
    
    void append(int x) {
        if (count == pwr2) doubleCapacity();
        data[count] = x;
        count++;
    }
    
    T & operator[](int i) {
        return data[i];
    }
    
};

int main(int argc, const char * argv[]) {
    
    Array<int> array;
    
    for (int i = 0; i <= 1000; i++) {
        array.append(500 - i);
    }
    
    int sum {0};
    for (int i = 0; i <= 1000; i++) {
        sum += array[i];
    }
    
    cout << boolalpha << (sum == 0) << endl;
    
    return 0;
}
