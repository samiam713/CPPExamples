//
//  Vector2.hpp
//  Vector2
//
//  Created by Samuel Donovan on 2/8/21.
//

#ifndef Vector2_h
#define Vector2_h

#include <algorithm>

template <typename T>
class Vector2 {
    size_t capacity;
    size_t count;
    T * elements;
    
public:
    
    size_t size() {return count;}
    
    T & operator[](int i) {
        return elements[i];
    }
    
    void pushLast(T const & value) {
        if (count == capacity) {
            // calculate newCapacity, allocate new array
            T * newElements = new T[capacity << 1];
            
            // traverse through elements and copy all of them into newElements
            T * newElementsTraverser = newElements;
            T * elementsTraverser = elements;
            
            T * const end = elementsTraverser + capacity;
            while (elementsTraverser != end) {
                *newElementsTraverser = *elementsTraverser;
                ++newElementsTraverser; ++elementsTraverser;
            }
            
            // update capacity and elements
            capacity <<= 1;
            delete[] elements;
            elements = newElements;
        }
        
        // copy element to appropriate spot, update count
        elements[count] = value;
        ++count;
    }
    
    void popLast() {
        if (count > 0) --count;
    }
    
    T & getLast() {
        return elements[count-1];
    }
    
    T & getFirst() {
        return *elements;
    }
    
    Vector2() :
    capacity(1), count(0), elements(new T[1]) {}
    
    ~Vector2() {
        delete[] elements;
    }
    
};

#endif /* Vector2_h */
