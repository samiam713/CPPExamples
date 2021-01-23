//
//  SudokuGame.hpp
//  Backtracking Sudoku
//
//  Created by Samuel Donovan on 4/23/20.
//  Copyright © 2020 Samuel Donovan. All rights reserved.
//

#ifndef SudokuGame_hpp
#define SudokuGame_hpp

#include <iostream>
#include <string>
#include <vector>

class SudokuGame {
public:
    std::string name;
    bool solved;
    
    SudokuGame() {};
    
    SudokuGame(std::string * data);
    
    int getThing() {
        return 100*int(board[0][0]-48)+10*int(board[0][1]-48)+int(board[0][2]-48);
    }
    
    void solve();
    
    friend std::ostream& operator<<(std::ostream& os, SudokuGame& game) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                os << game.board[i][j];
            }
            os << std::endl;
        }
        return os;
    }
    
private:
    char board[9][9];
    void solveFrom(int row, int col);
    void keepSolvingFrom(int row, int col);
    bool problematic(int row, int col) {
        return problematicRow(row, col) || problematicCol(row, col) || problematicSec(row, col);
    }
    bool problematicRow(int row, int col);
    bool problematicCol(int row, int col);
    bool problematicSec(int row, int col);
};

#endif /* SudokuGame_hpp */
