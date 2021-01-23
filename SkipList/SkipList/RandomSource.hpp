//
//  RandomSource.hpp
//  SkipList
//
//  Created by Samuel Donovan on 4/30/20.
//  Copyright © 2020 Samuel Donovan. All rights reserved.
//

#ifndef RandomSource_hpp
#define RandomSource_hpp

#include <stdlib.h>
#include <time.h>

struct RandomSource {
    
    RandomSource() {
        srand((unsigned int)time(nullptr));
    }
    
    bool getBool() {
        return rand()&1;
    }
};

#endif /* RandomSource_hpp */
