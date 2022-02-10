//
//  main.c
//  FloppyFour
//
//  Created by Martin Schijf on 07/02/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include "general.h"

int board[7][6];
int top[7];
int clr;
int eval;


const int tupleValue[64] = {
          0, -1, -3, -7, -9999,  0,  0,  0,
          1,  0,  0,  0,     0,  0,  0,  0,
          3,  0,  0,  0,     0,  0,  0,  0,
          7,  0,  0,  0,     0,  0,  0,  0,
       9999,  0,  0,  0,     0,  0,  0,  0,
          0,  0,  0,  0,     0,  0,  0,  0,
          0,  0,  0,  0,     0,  0,  0,  0,
          0,  0,  0,  0,     0,  0,  0,  0
};

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
    for (int col=0; col<7; ++col)
        for (int row=0; row<6; ++row)
            board[col][row]=0;

    for (int i=0; i<7; ++i)
        top[i] = 0;

    for (int i=0; i < 69; ++i) {
        tuple[i] = 0;
    }

    clr = 1;
    eval = 0;
}

long nodeCount;

void addColorToTuples(int **tuple, int clr) {
    int clrBit = (clr < 0 ? 1 : 8);
    while (*tuple) {
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



int alfabeta(int depth) {
    nodeCount++;
    if (eval > 5000 || eval < -5000) {
        return clr * 5000;
    }
    if (depth <= 0) {
        return clr * eval;
    }

    int best = -10000000;
    for (int i=0; i<7; ++i) {
        if (top[i] < 6) {
            doMove(i);
            int v = -alfabeta(depth-1);
            if (v > best)
                best = v;
            undoMove(i);
        }
    }
    return best;
}

int  main(void) {
    char str[16];

    initFieldToTuple();
    initBoard();

    nodeCount = 0;
    timer_t *timer = startTimer();
    printf ("eval = %d, \n", eval);
    int v = alfabeta(9);
    printf ("eval = %d, \n", eval);

    long uSec = stopTimer(timer);
    printf ("value = %d, aantal moves = %ld\n", v, nodeCount);
    printf("%ld nodes visited in: %.6lf seconds, ", nodeCount, uSec/1000000.0);
    printf("average of %s moves per second\n", sprintInt(str, nodeCount*1.0/(uSec/1000000.0), '.'));
    
    return 0;
}
