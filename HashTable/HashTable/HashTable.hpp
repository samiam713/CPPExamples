//
//  HashTable.hpp
//  HashTable
//
//  Created by Samuel Donovan on 4/30/20.
//  Copyright © 2020 Samuel Donovan. All rights reserved.
//

#ifndef HashTable_hpp
#define HashTable_hpp

#include <string>
#include <vector>
#include <algorithm>

class HashTable {
private:
    struct HashNode {
        std::string word;
        std::string definition;
        HashNode* next;
        
        HashNode(std::string word,std::string definition) :
        word(word), definition(definition), next(nullptr) {}
        
        ~HashNode() {delete next;}
    };
public:
    HashTable(int size) :
    size(size) {
        array = new HashNode*[size];
        std::fill(array, array+size, nullptr);
    }
    ~HashTable() {
        delete [] array;
    }
    
    std::string & operator[](std::string word);
    void define(std::string word, std::string definition);
    void remove(std::string word);
    
private:
    static void append(HashNode* node, HashNode* & list);
    static void remove(std::string const & word, HashNode* & list);
    static HashNode* searchFor(std::string const & word, HashNode* in);
    static int hash(std::string word);
    inline int getIndex(std::string word) {return hash(word) % size;}
    HashNode** array;
    int size;
};

#endif /* HashTable_hpp */
