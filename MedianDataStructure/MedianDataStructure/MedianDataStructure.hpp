//
//  MedianDataStructure.hpp
//  MedianDataStructure
//
//  Created by Samuel Donovan on 2/7/21.
//

#ifndef MedianDataStructure_hpp
#define MedianDataStructure_hpp

#include <set>
#include <vector>

struct MedianDataStructure {
    
    MedianDataStructure(std::vector<int> const & v) :
    median(0), sizeZero(true) {for (int const i : v) insert(i);}
    
    size_t size() {return lesser.size() + greater.size() + 1;}
    
    // inserts i into approprate spot in median data structure
    // precondition:
    // lesser.size() == greater.size() || lesser.size() + 1 == greater.size()
    // size_t c = count();
    // postcondition:
    // (0...1).contains(lesser.size() - greater.size())
    // c + 1 == count()
    void insert(int i);
    
    // removes i from approprate spot in median data structure
    // precondition:
    // (0...1).contains(lesser.size() - greater.size())
    // size_t c = count();
    // bool containsI = contains(i)
    
    // postcondition:
    // returnValue == (c - 1 == count())
    // (0...1).contains(lesser.size() - greater.size())
    // (c == 0 || !containsI) != (c - 1 == count())
    bool remove(int i);
    
    // extracts median while maintaing balance between between left and right
    void extractMedian();
    
    int getMedian() {return median;}
    
// private:
    
    void correctImbalances();
    
    void rotateLeft();
    
    void rotateRight();
    
    bool sizeZero;
    
    int median;
    std::set<int> lesser;
    std::set<int> greater;
};

#endif /* MedianDataStructure_hpp */
