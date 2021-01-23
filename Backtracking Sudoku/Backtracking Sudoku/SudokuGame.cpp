//
//  SudokuGame.cpp
//  Backtracking Sudoku
//
//  Created by Samuel Donovan on 4/23/20.
//  Copyright © 2020 Samuel Donovan. All rights reserved.
//

#include "SudokuGame.hpp"
#include <iostream>

SudokuGame::SudokuGame(std::string * data) :
name(data[0]), solved(false)
{
    for (int i = 1; i < 10; ++i) {
        for (int j = 0; j < 9; j++) {
            board[i-1][j] = data[i][j];
        }
    }
}

void SudokuGame::solve() {
    solveFrom(0, 0);
}

void SudokuGame::solveFrom(int row, int col) {
 
    if (board[row][col]=='0') {
        for (char i = '1'; i <= '9'; i++) {
            board[row][col] = i;
            if (!problematic(row, col)) {
                keepSolvingFrom(row, col);
                if (solved) {
                    return;
                }
            }
        }
        board[row][col] = '0';
    } else {
        keepSolvingFrom(row, col);
    }
}

bool SudokuGame::problematicRow(int row, int col) {
    for (int i = 0; i < 9; i++) {
        if (board[row][i]==board[row][col] && i!=col) {
            return true;
        }
    }
    return false;
}

bool SudokuGame::problematicCol(int row, int col) {
    for (int i = 0; i < 9; i++) {
        if (board[i][col]==board[row][col] && i!=row) {
            return true;
        }
    }
    return false;
}

bool SudokuGame::problematicSec(int row, int col) {
    int rowSec = row/3;
    int colSec = col/3;
    for (int i = rowSec*3; i < 3*(rowSec+1); i++) {
        for (int j = colSec*3; j < 3*(colSec+1); j++) {
            if (board[i][j]==board[row][col] && i!=row && j!=col) {
                return true;
            }
        }
    }
    return false;
}

void SudokuGame::keepSolvingFrom(int row, int col) {
    col++;
    if (col == 9) {
        row++;
        col = 0;
        if (row==9) {
            solved = true;
        }
    }
    solveFrom(row, col);
}
