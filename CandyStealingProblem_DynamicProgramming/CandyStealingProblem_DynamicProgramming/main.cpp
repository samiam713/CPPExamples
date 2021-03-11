//
//  main.cpp
//  CandyStealingProblem_DynamicProgramming
//
//  Created by Samuel Donovan on 3/8/21.
//

#include <iostream>
#include <vector>

using namespace std;

int maxCandyStealable(std::vector<int> const & houses) {
    const int n = int(houses.size());
    
    if (n < 2) return (n == 1) ? houses[0] : 0;
    
    int twoAfter = 0; // max candy attainable two after examining
    int oneAfter = houses[n - 1]; // max candy attainable one after examining
    int temp = 0; // garbage initialization
    
    int examining = n - 2;
    // loop invariant...
    // we are storing value for house examining in temp
    while (examining >= 0) {
        temp = std::max(oneAfter, houses[examining] + twoAfter);
        twoAfter = oneAfter;
        oneAfter = temp;
        
        examining--;
    }
    
    return temp;
}

int main(int argc, const char * argv[]) {
    
    cout << maxCandyStealable({10, 20, 30, 10}) << endl;
    
    return 0;
}
