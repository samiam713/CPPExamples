//
//  main.cpp
//  SkipList
//
//  Created by Samuel Donovan on 4/30/20.
//  Copyright © 2020 Samuel Donovan. All rights reserved.
//

#include <iostream>
#include <string>

#include "SkipList.hpp"

using namespace::std;

int main(int argc, const char * argv[]) {
    SkipList<string,string> skipList(5,RandomSource());
    
    skipList.insert("Lion", "A lion is a large predator that roars.");
    skipList.insert("Potato", "A potato is an edible plant. The majority of its mass is underground.");
    skipList.insert("Predator", "A predator is an animal whose food sources include other animals");
    skipList.insert("Asdf", "A sequence of letters obtained by pressing your left hand fingers down from left to right from resting position.");
    
    cout << skipList["Lion"] << endl;
    skipList.remove("Lion");
    skipList.remove("Potato");
    
    return 0;
}
