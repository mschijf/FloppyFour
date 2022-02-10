//
//  move.c
//  FloppyFour
//
//  Created by Martin Schijf on 10/02/2022.
//

#include "move.h"
#include "board.h"
#include "eval.h"

void addColorToTuples(int **tuple, int clr) {
    int clrBit = (clr < 0 ? 1 : 8);
    while (*tuple) {
        eval -= tupleValue[**tuple];
        **tuple += clrBit;
        eval += tupleValue[**tuple];
        tuple++;
    }
}

void removeColorFromTuples(int **tuple, int clr) {
    int clrBit = (clr < 0 ? 1 : 8);
    while (*tuple) {
        eval -= tupleValue[**tuple];
        **tuple -= clrBit;
        eval += tupleValue[**tuple];
        tuple++;
    }
}

void doMove(int col) {
    int row = top[col]++;
    board[col][row] = clr;
    addColorToTuples(field2tuple[col][row], clr);
    clr = -clr;
}

void undoMove(int col) {
    int row = --top[col];
    board[col][row] = 0;
    clr = -clr;
    removeColorFromTuples(field2tuple[col][row], clr);
}
