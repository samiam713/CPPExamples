//
//  HashTable.cpp
//  HashTable
//
//  Created by Samuel Donovan on 4/30/20.
//  Copyright © 2020 Samuel Donovan. All rights reserved.
//

#include "HashTable.hpp"

using namespace std;

std::string & HashTable::operator[](std::string word) {
    HashNode * const node = searchFor(word, array[getIndex(word)]);
    if (node==nullptr) {
        throw out_of_range("Word not in dictionary");
    }
    return node->definition;
}

void HashTable::define(std::string word, std::string definition) {
    HashNode* node = new HashNode(word,definition);
    append(node, array[getIndex(word)]);
}

void HashTable::remove(std::string word) {
    remove(word, array[getIndex(word)]);
}

void HashTable::append(HashNode* node, HashNode* & list) {
    if (list==nullptr) {
        list = node;
    } else {
        append(node, list->next);
    }
}

void HashTable::remove(std::string const & word, HashNode* & list) {
    if (list == nullptr) return;
    if (list->word == word) {
        HashNode* replacement = list->next;
        list->next = nullptr;
        delete list;
        list = replacement;
    } else {
        remove(word, list->next);
    }
}

HashTable::HashNode* HashTable::searchFor(std::string const & word, HashNode* in) {
    if (in == nullptr) {return in;}
    if (in->word == word) {
        return in;
    } else {
        return searchFor(word, in);
    }
}

int HashTable::hash(std::string word) {
    int baby {0};
    
    const size_t end = min((size_t)5,word.size());
    
    for (size_t i = 0; i < end; i++) {
        baby += i*word[i];
    }
    
    return baby;
}
