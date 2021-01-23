//
//  main.cpp
//  Trie
//
//  Created by Samuel Donovan on 5/1/20.
//  Copyright © 2020 Samuel Donovan. All rights reserved.
//

#include <iostream>
#include "Trie.hpp"

using namespace::std;

int main(int argc, const char * argv[]) {
    
    Trie trie;
    
    trie.insert("at");
    trie.insert("a");
    trie.insert("con");
    trie.insert("cow");
    trie.insert("cat");
    
    cout << boolalpha << trie.exists("cat") << endl;
    
    trie.remove("con");
    
    cout << boolalpha << trie.exists("cat") << endl;
    
    trie.remove("cat");
    
    cout << trie.exists("cat") << endl;
    
    return 0;
}
