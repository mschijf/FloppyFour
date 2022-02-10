//
//  board.c
//  FloppyFour
//
//  Created by Martin Schijf on 10/02/2022.
//

#include "board.h"

int board[7][6];
int top[7];
int clr;

int *field2tuple[7][6][14];
int tuple[69];

void addTupleReference(int **fieldToTuple, int *tupleReference) {
    int **p = fieldToTuple;
    while (*p) {
        ++p;
    }
    *p = tupleReference;
    *(p+1) = 0;
}

void initFieldToTuple(void) {
    for (int col=0; col < 7; col++) {
        for (int row=0; row < 6; row++) {
            *field2tuple[col][row] = 0;
        }
    }

    int *tupleRef = tuple;
    //vertical tuples
    for (int col=0; col < 7; col++) {
        for (int row=0; row < 6-3; row++) {
            addTupleReference(field2tuple[col][row], tupleRef);
            addTupleReference(field2tuple[col][row+1], tupleRef);
            addTupleReference(field2tuple[col][row+2], tupleRef);
            addTupleReference(field2tuple[col][row+3], tupleRef);
            tupleRef++;
        }
    }
    //horizontal tuples
    for (int row=0; row < 6; row++) {
        for (int col=0; col < 7-3; col++) {
            addTupleReference(field2tuple[col][row], tupleRef);
            addTupleReference(field2tuple[col+1][row], tupleRef);
            addTupleReference(field2tuple[col+2][row], tupleRef);
            addTupleReference(field2tuple[col+3][row], tupleRef);
            tupleRef++;
        }
    }
    //diagonal tuples
    for (int col=0; col < 7-3; col++) {
        for (int row=0; row < 6-3 ; row++) {
            addTupleReference(field2tuple[col][row], tupleRef);
            addTupleReference(field2tuple[col+1][row+1], tupleRef);
            addTupleReference(field2tuple[col+2][row+2], tupleRef);
            addTupleReference(field2tuple[col+3][row+3], tupleRef);
            tupleRef++;
        }
    }

    //other diagonal tuples
    for (int col=7-4; col < 7; col++) {
        for (int row=0; row < 6-3 ; row++) {
            addTupleReference(field2tuple[col][row], tupleRef);
            addTupleReference(field2tuple[col-1][row+1], tupleRef);
            addTupleReference(field2tuple[col-2][row+2], tupleRef);
            addTupleReference(field2tuple[col-3][row+3], tupleRef);
            tupleRef++;
        }
    }
}

void initBoard(void) {
    initFieldToTuple();
    for (int col=0; col<7; ++col)
        for (int row=0; row<6; ++row)
            board[col][row]=0;

    for (int i=0; i<7; ++i)
        top[i] = 0;

    for (int i=0; i < 69; ++i)
        tuple[i] = 0;

    clr = 1;
}


