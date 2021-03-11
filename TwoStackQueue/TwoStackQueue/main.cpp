//
//  main.cpp
//  TwoStackQueue
//
//  Created by Samuel Donovan on 2/12/21.
//

#include <iostream>
#include "TwoStackQueue.hpp"

int main(int argc, const char * argv[]) {
    
    TwoStackQueue<int> queue;
    
    for (int i = 0; i < 10; i++) {
        queue.push(i);
    }
    for (int i = 0; i < 10; i++) {
        cout << queue.top() << ' ';
        queue.pop();
    }
    cout << endl;
    
    return 0;
}
