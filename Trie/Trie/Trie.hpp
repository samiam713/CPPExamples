//
//  Trie.hpp
//  Trie
//
//  Created by Samuel Donovan on 5/1/20.
//  Copyright © 2020 Samuel Donovan. All rights reserved.
//

#ifndef Trie_hpp
#define Trie_hpp

#include <string>
#include <map>

// theoretically this could be some sort of map of word to ExecutableFile pointers
// so you can type in a word and run the executable file

class Trie {
protected:
    struct LevelNode {
        LevelNode(LevelNode* parent) :
        parent(parent), children(), inTrie(false) {}
        
        LevelNode* parent;
        std::map<char,LevelNode> children; // corresponds to the potential list of following letters
        bool inTrie;
        
        LevelNode* findHelper(std::string::iterator & current, std::string::iterator const end);
        void removeHelper(std::string::reverse_iterator & current); // only works if the iterator is not the end (watch for "")
        void insertHelper(std::string::iterator & current, std::string::iterator const end);
    };
public:
    
    Trie() : head(nullptr) {}
    
    void insert(std::string str);
    void remove(std::string str);
    bool exists(std::string str);
    
protected:
    LevelNode* find(std::string str);
    LevelNode head; // every level node corresponds to some string (sequence of characters)
};

#endif /* Trie_hpp */
