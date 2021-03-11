//
//  TwoStackQueue.hpp
//  TwoStackQueue
//
//  Created by Samuel Donovan on 2/12/21.
//

#ifndef TwoStackQueue_hpp
#define TwoStackQueue_hpp

#include <stdio.h>
#include <stack>

using namespace std;

template<class T>
class TwoStackQueue {
public:
    
    TwoStackQueue() {}
    
    void push(T const & item);
    
    T const & top();
    
    void pop();
    
private:
    
    stack<T> enter;
    stack<T> exit;
    
    inline void replenishExitIfNecessary() {
        if (!exit.empty()) return;
        while (!enter.empty()) {
            exit.push(enter.top());
            enter.pop();
        }
    }
};

template<class T>
void TwoStackQueue<T>::push(T const & item) {
    enter.push(item);
}

template<class T>
T const & TwoStackQueue<T>::top() {
    replenishExitIfNecessary();
    return exit.top();
}

template<class T>
void TwoStackQueue<T>::pop() {
    replenishExitIfNecessary();
    exit.pop();
}

#endif /* TwoStackQueue_hpp */
