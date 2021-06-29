//
//  Solution.cpp
//  GoogleScratchPaper
//
//  Created by Samuel Donovan on 6/3/21.
//

#include "Solution.hpp"

int Solution::mySqrt(int x) {
    // ah ha... use (x+1)^2-x^2 == 2x+1
    // ah ha... use (x+1)^2-x^2 == 2x+1
    
    if (x >= 2147395600) return 46340;
    
    int ySqrd = 0;
    int y = 0;
    
    // every execution x and xSqrd updated
    while(true) {
        ySqrd += ((y<<1) + 1);
        y++;
        if (ySqrd > x) return y-1;
    }
}

if (x >= 2147395600) return 46340;
