//
//  main.cpp
//  C++Playground_0
//
//  Created by Samuel Donovan on 4/21/21.
//

#include <iostream>

int main(int argc, const char * argv[]) {
    // insert code here...
    int* x = new int;
    *x = 5;
    int y {0};
    std::cout << x << ' ' << &y << std::endl;;
    return 0;
}
