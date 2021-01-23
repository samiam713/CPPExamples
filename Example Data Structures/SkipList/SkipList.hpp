//
//  SkipList.hpp
//  SkipList
//
//  Created by Samuel Donovan on 4/30/20.
//  Copyright © 2020 Samuel Donovan. All rights reserved.
//

#ifndef SkipList_hpp
#define SkipList_hpp

#include "RandomSource.hpp"
#include <vector>
#include <algorithm>
#include <iostream>

template<class Key, class Value>
class SkipList {
protected:
    struct SkipNode {
        Key key;
        Value value;
        SkipNode** next;
        int height;
        
        SkipNode(Key key, Value value, int height) :
        key(key), value(value), height(height) {
            next = new SkipNode*[height];
        }
        
        ~SkipNode() {
            delete *next;
            delete[] next;
        }
    };
    
public:
    SkipList(int maxHeight, RandomSource randomSource) :
    maxHeight(maxHeight), randomSource(randomSource), head(Key(),Value(),maxHeight) {
        std::fill(head.next, (head.next)+maxHeight, nullptr);
    }
    void insert(Key key, Value value);
    void remove(Key key);
    Value & operator[](Key key);
protected:
    
    void insertHelper(SkipNode* inserting, SkipNode* after, SkipNode** lvlToPred);
    SkipNode* operatorHelper(Key key, SkipNode* checkAfter);
    void removeHelper(Key key, SkipNode* checkAfter, SkipNode** lvlToPred);
    
    int getHeight();
    RandomSource randomSource;
    int maxHeight;
    SkipNode head;
};

template <typename Key, typename Value>
void SkipList<Key,Value>::insertHelper(SkipNode* inserting, SkipNode* after, SkipNode** lvlToPred) {
    int howManyUpdates = std::min(inserting->height,after->height);
    for (int i = 0; i < howManyUpdates; ++i) {
        lvlToPred[i] = after;
    }
//    std::cout << after->next[(after->height-1)] << std::endl;
    for (int i = (after->height)-1; i >= 0; --i) {
        if ((after->next)[i]!=nullptr && (after->next)[i]->key < inserting->key) {
            insertHelper(inserting, (after->next)[i], lvlToPred);
            return;
        }
    }
     // if there's no level of next to insert after, insert where it is
    for (int i = 0; i < inserting->height; ++i) {
        (inserting->next)[i] = ((lvlToPred[i])->next)[i];
        (lvlToPred[i]->next)[i] = inserting;
    }
   
}

template <typename Key, typename Value>
void SkipList<Key,Value>::insert(Key key, Value value) {
    SkipNode* addition = new SkipNode(key,value,getHeight());
    SkipNode** lvlToPred = new SkipNode*[addition->height];
    insertHelper(addition, &head, lvlToPred);
    delete [] lvlToPred;
}

template <typename Key, typename Value>
void SkipList<Key,Value>::removeHelper(Key key, SkipNode* checkAfter, SkipNode** lvlToPred) {
    for (int i = 0; i < checkAfter->height; ++i) {
        lvlToPred[i] = checkAfter;
    }
    for (int i = checkAfter->height - 1; i >= 0; --i) {
        if ((checkAfter->next)[i]!=nullptr && checkAfter->next[i]->key < key) {
            removeHelper(key, checkAfter->next[i], lvlToPred);
            return;
        }
    }
    SkipNode* toRemove = *(checkAfter->next);
    std::cout << toRemove->key << std::endl;
    if (toRemove->key == key) {
        for (int i = 0; i < toRemove->height; ++i) {
            (lvlToPred[i]->next)[i] = (toRemove->next)[i];
        }
        *(toRemove->next) = nullptr;
        delete toRemove;
    } else {
        throw std::out_of_range("Invalid key");
    }
}

template <typename Key, typename Value>
void SkipList<Key,Value>::remove(Key key) {
    SkipNode** lvlToPred = new SkipNode*[maxHeight];
    removeHelper(key, &head, lvlToPred);
    delete [] lvlToPred;
}

template <typename Key, typename Value>
typename SkipList<Key,Value>::SkipNode* SkipList<Key,Value>::operatorHelper(Key key, SkipNode* checkAfter) {
    for (int i = (checkAfter->height)-1; i >= 0; --i) {
        if ((checkAfter->next)[i]==nullptr) continue;
        if ((checkAfter->next)[i]->key < key) {
            return operatorHelper(key, (checkAfter->next)[i]);
        } else if ((checkAfter->next)[i]->key == key) {
            return (checkAfter->next)[i];
        }
    }
    return nullptr;
}

template <typename Key, typename Value>
Value & SkipList<Key,Value>::operator[](Key key) {
    return operatorHelper(key, &head)->value;
}

template <typename Key, typename Value>
int SkipList<Key,Value>::getHeight() {
    for (int i = 1; i < maxHeight; i++) {
        if (randomSource.getBool()) return i;
    }
    return maxHeight;
}


#endif /* SkipList_hpp */
