//
//  main.cpp
//  PartnerMatchExample
//
//  Created by Samuel Donovan on 1/21/21.
//

#include <iostream>
#include <vector>

using namespace std;

typedef int Man;
typedef int Woman;

// input:
// num is number of men and women
// menPref[num*m + w] == m's rank of w
// womanPref[num*w + m] == w's rank of m

// output:
// a vector v such that v[w] == m and no other w', m' == v[w'] such that
// womanPref[num*w' + m] < womanPref[num*w' + m'] && manPref[num*m + w'] < womanPref[num*m + w]
vector<Man> getPairs(vector<int> const & manPref, vector<int> const & womanPref, int const num) {
    
    // this is a map from a woman to his current partner, -1 means no partner
    vector<Man> womanToPartner(num, -1);
    
    // this is a map from a man to the woman he wants to propose to listed in order
    vector<Woman> manLists(num*num);
    
    for (Man m = 0; m < num; m++) {
        for (Woman w = 0; w < num; w++) {
            manLists[num*m + manPref[num*m + w]] = w;
        }
    }
    
    // this is a map from a man to the woman he proposes to next
    vector<Woman*> manProposesToNext(num);
    for (Man m = 0; m < num; m++) {
        manProposesToNext[m] = &manLists[m*num];
    }
    
    for (Man i = 0; i < num; i++) {
        // at beginning of loop, i has no partner
        Man currentBachelor = i;
        while (true) {
            
            // find next woman up for currentBachelor
            Woman proposeToWoman = *manProposesToNext[currentBachelor];
            ++manProposesToNext[currentBachelor];
            
            Man womanCurrentPartner = womanToPartner[proposeToWoman];
            // if woman isn't taken, get engaged
            if (womanCurrentPartner == -1) {
                womanToPartner[proposeToWoman] = currentBachelor;
                break;
            }
            
            // if woman prefers currentBachelor, pull a switcheroo
            if (womanPref[proposeToWoman*num + womanCurrentPartner] > womanPref[proposeToWoman*num + currentBachelor]) {
                womanToPartner[proposeToWoman] = currentBachelor;
                currentBachelor = womanCurrentPartner;
            }
            // loop again to find match for currentBachelor
        }
        
        // now i has partner
    }
    // now all men have partners
    return womanToPartner;
}

int main(int argc, const char * argv[]) {
    vector<int> manPref {0,1,1,0};
    vector<int> womanPref {1,0,1,0};
    int const n = 2;
    
    auto ans = getPairs(manPref, womanPref, n);
    
    for (Man man : ans) {
        cout << man << ' ';
    }
    cout << endl;
}
