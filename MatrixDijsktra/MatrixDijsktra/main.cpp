//
//  main.cpp
//  MatrixDijsktra
//
//  Created by Samuel Donovan on 4/24/20.
//  Copyright © 2020 Samuel Donovan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <set>
#include <vector>

using namespace std;

vector<int> getPredecessors(size_t dijsktra[40][40]) {
    vector<int> baby;
    baby.resize(40, -1);
    
    set<int> searched;
    searched.insert(0);
    
    while (searched.size() != 40) {
        
        int min = 100000;
        int where = -1;
        int finder = -1;
        for (const auto& alreadySearched : searched) {
            for (size_t i = 0; i < 40; i++) {
                if (searched.find(i) == searched.end() && dijsktra[alreadySearched][i] != 0 && dijsktra[alreadySearched][i] < min) {
                    min = dijsktra[alreadySearched][i];
                    finder = alreadySearched;
                    where = i;
                }
            }
        }
        baby[where] = finder;
        searched.insert(where);
    }
    return baby;
}

int main(int argc, const char * argv[]) {
    
    ifstream input;
    
    input.open("p107_network.txt");
    
    size_t dijsktra[40][40] = {};
    
    char c;
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {
            input >> noskipws >> c;
            while (c != ',' && c != '\n') {
                if (c == '-') {
                    dijsktra[i][j] = 0;
                } else {
                    dijsktra[i][j]*=10;
                    dijsktra[i][j]+=(c-48);
                }
                input >> noskipws >> c;
            }
        }
    }
    
    auto vec = getPredecessors(dijsktra);
    
    int sum = 0;
    for (int i = 1; i < 40; i++) {
        cout << vec[i] << endl;
        sum += dijsktra[i][vec[i]];
    }
    
    int totalSum = 0;
    for (int i = 0; i < 40; i++) {
        for (int j = i; j < 40; j++) {
            totalSum+=dijsktra[i][j];
        }
    }
    cout << totalSum-sum << endl;
    return 0;
}
