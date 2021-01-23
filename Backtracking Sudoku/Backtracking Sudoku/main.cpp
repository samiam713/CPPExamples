//
//  main.cpp
//  Backtracking Sudoku
//
//  Created by Samuel Donovan on 4/23/20.
//  Copyright © 2020 Samuel Donovan. All rights reserved.
//

#include "SudokuGame.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, const char * argv[]) {
    ifstream ifs;
    
    ifs.open ("sudokuprobs.txt");
    
    int sum = 0;
    
    for (int i = 0; i < 50; i++) {
        string s[10];
        for (int j = 0; j < 10; j++) {
            getline(ifs,s[j]);
        }
        SudokuGame game(s);
        game.solve();
        if (i == 49) {
            cout << game;
        }
        if (game.solved) {
            sum += game.getThing();
        } else {
            throw logic_error("didn't solve this puzzle");
        }
    }
    
    cout << sum << endl;
    
    ifs.close();
    return 0;
}
