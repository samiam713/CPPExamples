//
//  Trie.cpp
//  Trie
//
//  Created by Samuel Donovan on 5/1/20.
//  Copyright © 2020 Samuel Donovan. All rights reserved.
//

#include "Trie.hpp"

using namespace::std;

typename Trie::LevelNode* Trie::LevelNode::findHelper(std::string::iterator & current, std::string::iterator const end) {
    if (current == end) {
        return this;
    } else {
        auto iterator = children.find(*current);
        if (iterator == children.end()) return nullptr;
        ++current;
        return iterator->second.findHelper(current, end);
    }
}

void Trie::LevelNode::removeHelper(std::string::reverse_iterator & current) { // assumes this is some node on the chain of deletion
    if (children.size()>1||parent == nullptr) {
        children.erase(*current);
    } else {
        ++current;
        parent->removeHelper(current);
    }
}

void Trie::LevelNode::insertHelper(std::string::iterator & current, std::string::iterator const end) {
    if (current==end) {
        inTrie=true;
    } else {
        auto iterator = children.find(*current);
        if (iterator == children.end()) {
            auto addition = children.insert(make_pair(*current, LevelNode(this)));
            ++current;
            addition.first->second.insertHelper(current, end);
        } else {
            ++current;
            iterator->second.insertHelper(current, end);
        }
    }
}

void Trie::insert(std::string str) {
    string::iterator current = str.begin();
    head.insertHelper(current, str.end());
}

void Trie::remove(std::string str) {
    if (str.empty()) {
        head.inTrie = false;
        return;
    } else {
        LevelNode* toRemove = find(str);
        if (toRemove!=nullptr) {
            auto backTracker = str.rbegin();
            toRemove->parent->removeHelper(backTracker);
        } else {
            return;
        }
    }
}

bool Trie::exists(std::string str) {

    std::string::iterator begin = str.begin();
    LevelNode* foundNode = head.findHelper(begin, str.end());
    if (foundNode == nullptr) {
        return false;
    } else {
        return foundNode->inTrie;
    }
}

typename Trie::LevelNode* Trie::find(std::string str) {
    std::string::iterator begin = str.begin();
    return head.findHelper(begin, str.end());
}
