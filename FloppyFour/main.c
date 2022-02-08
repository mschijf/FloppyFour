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
        0, -1, -1, -3, -8,  0,  0,  0,
        1,  0,  0,  0,  0,  0,  0,  0,
        1,  0,  0,  0,  0,  0,  0,  0,
        3,  0,  0,  0,  0,  0,  0,  0,
        8,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0
};

int field2tupleCount[7][6];
int field2tuple[7][6][13];
int tuple[69];

void initFieldToTuple(void) {
    int tupleId = 0;
    int index;

    for (int col=0; col < 7; col++) {
        for (int row=0; row < 6; row++) {
            field2tupleCount[col][row] = 0;
            for (int i=0; i < 13; ++i) {
                field2tuple[col][row][i] = 0;
            }
        }
    }

    //vertical tuples
    for (int col=0; col < 7; col++) {
        for (int row=0; row < 6-3; row++) {

            index = field2tupleCount[col][row]++;
            field2tuple[col][row][index] = tupleId;
            index = field2tupleCount[col][row+1]++;
            field2tuple[col][row+1][index] = tupleId;
            index = field2tupleCount[col][row+2]++;
            field2tuple[col][row+2][index] = tupleId;
            index = field2tupleCount[col][row+3]++;
            field2tuple[col][row+3][index] = tupleId;

            tupleId++;
        }
    }
    //horizontal tuples
    for (int row=0; row < 6; row++) {
        for (int col=0; col < 7-3; col++) {

            index = field2tupleCount[col][row]++;
            field2tuple[col][row][index] = tupleId;
            index = field2tupleCount[col+1][row]++;
            field2tuple[col+1][row][index] = tupleId;
            index = field2tupleCount[col+2][row]++;
            field2tuple[col+2][row][index] = tupleId;
            index = field2tupleCount[col+3][row]++;
            field2tuple[col+3][row][index] = tupleId;

            tupleId++;
        }
    }
    //diagonal tuples
    for (int col=0; col < 7-3; col++) {
        for (int row=0; row < 6-3 ; row++) {
            index = field2tupleCount[col][row]++;
            field2tuple[col][row][index] = tupleId;
            index = field2tupleCount[col+1][row+1]++;
            field2tuple[col+1][row+1][index] = tupleId;
            index = field2tupleCount[col+2][row+2]++;
            field2tuple[col+2][row+2][index] = tupleId;
            index = field2tupleCount[col+3][row+3]++;
            field2tuple[col+3][row+3][index] = tupleId;

            tupleId++;
        }
    }

    //other diagonal tuples
    for (int col=7-4; col < 7; col++) {
        for (int row=0; row < 6-3 ; row++) {

            index = field2tupleCount[col][row]++;
            field2tuple[col][row][index] = tupleId;
            index = field2tupleCount[col-1][row+1]++;
            field2tuple[col-1][row-1][index] = tupleId;
            index = field2tupleCount[col-2][row+2]++;
            field2tuple[col-2][row-2][index] = tupleId;
            index = field2tupleCount[col-3][row+3]++;
            field2tuple[col-3][row-3][index] = tupleId;

            tupleId++;
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


//#define doMove(c)        (board[c][top[c]++] = (clr), (clr) = (-clr))
//#define undoMove(c)    (board[c][--top[c]] = 0, (clr) = (-clr))

long nodeCount;

void doMove(int col) {
    int row = top[col]++;
    board[col][row] = clr;
    int clrBit = 1 << (clr+2);
    for (int i=0; i<field2tupleCount[col][row]; ++i) {
        int tupleIndex = field2tuple[col][row][i];
        tuple[tupleIndex] += clrBit;
        int tf = tuple[tupleIndex];
        eval += tupleValue[tf];
    }
    clr = -clr;

//    int *tuple = field2Tuple[col][row];
//    while (*tuple++) {
//        *tuple += clrBit;
//        eval += tupleValue(*tuple);
//    }
}

void undoMove(int col) {
    int row = --top[col];
    board[col][row] = 0;
    clr = -clr;
    int clrBit = 1 << (clr+2);
    for (int i=0; i<field2tupleCount[col][row]; ++i) {
        int tupleIndex = field2tuple[col][row][i];
        int tf = tuple[tupleIndex];
        tuple[tupleIndex] -= clrBit;
        eval -= tupleValue[tf];
    }
}



int alfabeta(int depth) {
    nodeCount++;
    if (depth <= 0) {
        return clr * eval;
    }

    int best = -9999;
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
