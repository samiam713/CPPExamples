//
//  main.cpp
//  Vector2
//
//  Created by Samuel Donovan on 2/8/21.
//

#include <iostream>
#include "Vector2.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    Vector2<int> v2;
    
    for (int i = 0; i < 5; ++i) {
        v2.pushLast(i);
    }
    
    for (int i = 4; i >= 0; --i) {
        cout << v2.getLast() << endl;
        v2.popLast();
    }
    
    return 0;
}
