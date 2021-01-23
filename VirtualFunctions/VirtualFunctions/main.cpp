//
//  main.cpp
//  VirtualFunctions
//
//  Created by Samuel Donovan on 4/23/20.
//  Copyright © 2020 Samuel Donovan. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

class Base {
public:
    virtual string getName() const {
        return "I am an object of type Base";
    }
};

class Derived: public Base {
public:
    string getName() const override {
        return "I am an object of type Derived";
    }
};

int main(int argc, const char * argv[]) {
    const Base & lol = Derived();
    std::cout << lol.getName() << endl;
    return 0;
}
