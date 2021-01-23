//
//  main.cpp
//  BjarneTests
//
//  Created by Samuel Donovan on 4/23/20.
//  Copyright © 2020 Samuel Donovan. All rights reserved.
//

#include <iostream>

using namespace std;

void asdf() {
    cout << "ok" << endl;
}

int main(int argc, const char * argv[]) {
    
    void (*test)() = asdf;
    test();
    return 0;
}
