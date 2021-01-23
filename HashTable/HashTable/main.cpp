//
//  main.cpp
//  HashTable
//
//  Created by Samuel Donovan on 4/30/20.
//  Copyright © 2020 Samuel Donovan. All rights reserved.
//

#include <iostream>
#include "HashTable.hpp"

using namespace::std;

int main(int argc, const char * argv[]) {
    HashTable ht(8);
    
    ht.define("Lion", "A lion is a large predator that roars.");
    ht.define("Potato", "A potato is an edible plant. The majority of its mass is underground.");
    ht.define("Predator", "A predator is an animal whose food sources include other animals");
    ht.define("Asdf", "A sequence of letters obtained by pressing your left hand fingers down from left to right from resting position.");
    
    cout << ht["Lion"] << endl;
    ht.remove("Lion");
    
    return 0;
}
